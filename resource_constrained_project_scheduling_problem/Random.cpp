#include "Random.h"

Individual Random::generate_ran(ProblemInstance data){
    int res_am = 4;
    vector<vector<int> > priority;
    for (int i=0; i <res_am; i++){
        vector<int> r1;
        priority.push_back(r1); 
    }
    vector<int> draw;
    for (int i=1; i<data.lastJob-1; i++)
        draw.push_back(i);

    for (int i=1; i<data.lastJob-1; i++){
        int r = rand()%draw.size();
        r = draw[r];
        priority[data.usingResources[r].first].push_back(r);
        remove(draw.begin(), draw.end(), r);
        draw.pop_back();
    }
    
    return create_by_priority_lists(data, priority);
}



Individual Random::create_by_priority_lists(ProblemInstance data, vector<vector<int> > priority){
    int res_am = 4;
    int jobsToDo = data.lastJob;
    vector<int>  durat = data.duration; 
    Individual ind(res_am);
    vector<vector<int> > available;
    for (int i=0; i <res_am; i++){
        vector<int> r1;
        available.push_back(r1);
    }
    if (durat[0]!=0){
        for (; durat[0]>0; durat[0]--){
            pair<int,int> task4stage = (data.usingResources[0]);
            vector<pair<int, int> > row;
            row.push_back(task4stage);
            ind.whole_sol.push_back(row);
        }
    }
    
    for ( auto it = data.seccessors[0].begin(); it != data.seccessors[0].end(); it++){
        //dostępne_taski_do_wykonania[id_resource].push_back(id_taska);
        available[data.usingResources[*it].first].push_back(*it);
    }
    jobsToDo--;
    while(jobsToDo>0){
        for(int i=0; i<res_am; i++ ){
            vector<pair<int, int> > row;
            vector<int> newAvaible;
            if(!available[i].empty()){
                int r = rand()%available[i].size();
                auto task4stage = available[i][r];
                row.push_back(data.usingResources[task4stage]);
                durat[task4stage]--;
                if(durat[task4stage]==0){
                    for(int j=0; j<available[i].size(); j++){
                        if(available[i][j]==task4stage){
                            remove(available[i].begin(),available[i].end(),task4stage);
                            jobsToDo--;
                            for(int k=0; k<data.seccessors[task4stage].size();k++)    
                                newAvaible.push_back(k);
                            break;
                        }
                    }
                }
            }
            for ( auto it = newAvaible.begin(); it != newAvaible.end(); it++)
                available[data.usingResources[*it].first][*it];
                // dodanie_nowych_dostępnych_taskow[id_resource][id_task]
            ind.whole_sol.push_back(row);
        }
    }
    return ind;
}