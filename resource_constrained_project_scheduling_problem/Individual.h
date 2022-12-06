#pragma once
#include<vector>
#include<utility>
#include<string>
#include <iostream>
#include <fstream>
#include <regex>
#include "ProblemInstance.h"

using namespace std;
class Individual
{
private:
    // whole_sol = stage * resource * task beeing done by resource;
    int stages_am, resources_am;
public:
    vector<vector<int> > priority;
    vector<vector<pair<int, int> > >  whole_sol;
    int cost;
    void print();
    Individual(int res, vector<vector<int> > p);
    Individual();
    bool contains(vector<int> vec, int val);
    void create_by_priority_lists(ProblemInstance* dataw, bool fitnessOnly = false);
};
