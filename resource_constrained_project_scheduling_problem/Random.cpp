#include "Random.h"

void Random::generate_ran(ProblemInstance* data, Individual* ind){
    int res_am = 4;
    vector<vector<int> > priority;
    for (int i=0; i <res_am; i++){
        vector<int> r1;
        priority.push_back(r1); 
    }
    vector<int> draw;
    for (int i=1; i<data->lastJob-1; i++)
        draw.push_back(i);
    for (int i=1; i<data->lastJob-1; i++){
        int r = rand()%draw.size();
        r = draw[r];
        priority[data->usingResources[r].first].push_back(r);
        remove(draw.begin(), draw.end(), r);
        draw.pop_back();
    }
    ind->priority = priority;
    return;
}




