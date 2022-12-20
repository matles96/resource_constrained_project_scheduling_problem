#include "P3.h"


void P3::findSollution(ProblemInstance *pi, int epochLimit)
{
    int res_am = 4;
    pyramidLevelAmount = 1;
    Individual* best;
    Individual* in_first = new Individual;
    Random::generate_ran(pi, in_first);
    FIHC::fihc(pi, in_first);
    vector<Individual> level0;
    best = in_first;
    level0.push_back(*in_first);
    pyramid.push_back(level0);

    do{
        Individual* in = new Individual;
        Random::generate_ran(pi, in);
        FIHC::fihc(pi, in);
        bool individualAlreadyExists = false;
        for (int i=0; i<pyramidLevelAmount; i++){
            for ( auto it = pyramid[i].begin(); it != pyramid[i].end(); it++)
                if (checkIfAreTheSame(&(*it), in)){
                    individualAlreadyExists = true;
                    goto endCheckingExistance;
                }
        }
    endCheckingExistance:
        if(!individualAlreadyExists){
            pyramid[0].push_back(*in);
            if(in->cost < best->cost)
                best = in;
        }
    }while(epochLimit--!=0);

    cout << best->cost << endl;
    //best->create_by_priority_lists(pi);
}

bool P3::checkIfAreTheSame(Individual* in1, Individual* in2){
    int res_am = 4;
    for (int i=0; i<res_am; i++){
        auto it2 = in2->priority[i].begin();
        for ( auto it1 = in1->priority[i].begin(); it1 != in1->priority[i].end(); it1++, it2++)
            if (*it1!=*it2)
                return false;
    }
    return true;
}