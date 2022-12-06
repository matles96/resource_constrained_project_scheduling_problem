#include "ProblemInstance.h"

vector<int> ProblemInstance::split(const string& s)
{
	vector<int> tokens;
	regex numberRegex("\\d+");

	smatch wynik;
	regex_search(s, wynik, numberRegex);
	
	auto words_begin = sregex_iterator(s.begin(), s.end(), numberRegex);
	auto words_end = sregex_iterator();
	for (sregex_iterator i = words_begin; i != words_end; ++i) {
		smatch match = *i;
		string match_str = match.str();
		tokens.push_back(stoi(match_str));
	}
	return tokens;
}

void ProblemInstance::redFromFile(string fileName)
{
	string myText;
	ifstream File(fileName, std::ifstream::in);
	int jobs=0;
	while (getline(File, myText)) {
		if (myText == "pronr.  #jobs rel.date duedate tardcost  MPM-Time") {
			getline(File, myText);

			auto tokens = this->split(myText);
			jobs = tokens.at(1);
			this->lastJob = tokens.at(1)+2;
			this->relDate = tokens.at(2);
			this->duedate = tokens.at(3);
			this->tarcost = tokens.at(4);
			this->MPMTime = tokens.at(5);
			amountOfAncestors.resize(lastJob);
			std::fill(amountOfAncestors.begin(), amountOfAncestors.end(), 0);
		}
		if (myText == "  R 1  R 2  R 3  R 4") {
			getline(File, myText);

			auto tokens = this->split(myText);
			this->R1 = tokens.at(0);
			this->R2 = tokens.at(1);
			this->R3 = tokens.at(2);
			this->R4 = tokens.at(3);
		}
		if (myText == "jobnr.    #modes  #successors   successors") {
			for (int i = 0; i < lastJob; i++) {
				getline(File, myText);
				auto tokens = this->split(myText);
				seccessors.push_back(vector<int>(tokens.begin() + 3, tokens.end()));
				for ( auto it = tokens.begin() + 3; it != tokens.end(); it++)
					amountOfAncestors[*it-1]++;
			}
		}
		if (myText == "jobnr. mode duration  R 1  R 2  R 3  R 4") {
			getline(File, myText);
			usingResources.push_back(pair<int, int>(0,0));
			for (int i = 0; i < jobs + 1; i++) {
				getline(File, myText);
				auto tokens = this->split(myText);
				for (int j = 0; j < 4; j++) {
					if (tokens.at(3 + j) != 0) {
						usingResources.push_back(pair<int, int>(j, tokens.at(3 + j)));
						break;
					}
				}
				duration.push_back(tokens.at(2));

			}
		}
	}
	File.close();
}
