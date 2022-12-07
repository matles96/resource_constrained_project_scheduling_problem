#pragma once
#include<vector>
#include<utility>
#include<string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
class ProblemInstance
{
	vector<int> split(const string& s);
public:
	vector<int>  duration;
	int R1, R2, R3, R4, relDate, duedate, tarcost, MPMTime, lastJob;
	vector<vector<int> >  seccessors;
	vector<int> amountOfAncestors;
	vector<pair<int, int> >  usingResources;
	void redFromFile(string fileName);
};


