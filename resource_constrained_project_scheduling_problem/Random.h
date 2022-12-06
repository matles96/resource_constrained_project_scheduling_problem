#pragma once
#include<vector>
#include<utility>
#include<string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Individual.h"
#include "ProblemInstance.h"

using namespace std;
class Random
{
public:
	Individual generate_ran(ProblemInstance data);
	Individual create_by_priority_lists(ProblemInstance data, vector<vector<int> > priority);
	bool contains(vector<int> vec, int val);
};
