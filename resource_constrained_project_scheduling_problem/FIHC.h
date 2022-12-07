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
class FIHC
{
public:
	static void fihc(ProblemInstance* data, Individual* ind);
};
