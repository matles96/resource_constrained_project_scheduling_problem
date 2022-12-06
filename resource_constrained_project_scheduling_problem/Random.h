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
	static void generate_ran(ProblemInstance* data, Individual* ind);
};
