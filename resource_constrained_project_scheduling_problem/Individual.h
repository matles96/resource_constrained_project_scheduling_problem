#pragma once
#include<vector>
#include<utility>
#include<string>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
class Individual
{
private:
    // whole_sol = stage * resource * task beeing done by resource;
    int stages_am, resources_am;
public:
    vector<vector<pair<int, int> > >  whole_sol;
    void print();
    Individual(int res);
};
