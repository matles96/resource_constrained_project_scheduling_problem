#pragma once
#include<vector>
#include<utility>
#include<string>
#include <iostream>
#include <fstream>

using namespace std;
class ProblemInstance
{
	int R1, R2, R3, R4, relDate, duedate, tarcost, MPMTime;
	vector<vector<int>>  seccessors;
	vector<pair<int, int>>  usingResources;
	vector<int>  duration;
public:
	void redFromFile(string fileName);
};


