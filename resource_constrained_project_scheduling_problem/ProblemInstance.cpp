#include "ProblemInstance.h"

void ProblemInstance::redFromFile(string fileName)
{
	string myText;
	ifstream File(fileName);
	while (getline(File, myText)) {
		cout << myText;
	}
	File.close();
}
