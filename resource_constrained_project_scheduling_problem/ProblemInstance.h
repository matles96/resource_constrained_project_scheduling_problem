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
	int R1, R2, R3, R4, relDate, duedate, tarcost, MPMTime, lastJob;
	vector<vector<int>>  seccessors;
	vector<pair<int, int>>  usingResources;
	vector<int>  duration;
	vector<int> split(const string& s);
public:
	void redFromFile(string fileName);
};


