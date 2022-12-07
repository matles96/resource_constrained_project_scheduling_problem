#include "Individual.h"

void Individual::print(){
    for (int j = 0; j < whole_sol.size(); j++) {
        for (int i = 0; i < whole_sol[j].size(); i++) {
            cout << "R" << whole_sol[j][i].first +1<< ": " << whole_sol[j][i].second +1<< "\t";
        }
        cout << endl;
    }
    cout << "Koszt rozwiazania to: " << cost << endl;
}

Individual::Individual(int res, vector<vector<int> > p) {
    stages_am = 0;
    resources_am = res;
    priority = p;
    cost=0;
}

Individual::Individual() {
    stages_am = 0;
    resources_am = 4;
    cost = 0;
}



void Individual::create_by_priority_lists(ProblemInstance* data, bool fitnessOnly){
    if(priority.empty()){
        cout << "Brak wektorow priorytetow!\n";
        return;
    }
    whole_sol.clear();    
    cost=0;

    int res_am = 4;
    int jobsToDo = data->lastJob;
    vector<int>  durat = data->duration;
    vector<vector<int> > available;
    vector<int> stillRequiedTaskToStart = data->amountOfAncestors;

    for (int i=0; i <res_am; i++){
        vector<int> r1;
        available.push_back(r1);
    }
    if (durat[0]!=0){
        for (; durat[0]>0; durat[0]--){
            pair<int,int> task4stage = (data->usingResources[0]);
            vector<pair<int, int> > row;
            row.push_back(task4stage);
            whole_sol.push_back(row);
        }
    }
    
    for ( auto it = data->seccessors[0].begin(); it != data->seccessors[0].end(); it++){
        //dostępne_taski_do_wykonania[id_resource].push_back(id_taska);
        available[data->usingResources[*it-1].first].push_back(*it-1);
        --stillRequiedTaskToStart[*it-1];
    }
    jobsToDo--;
    int poglodowaZmiennaDoWydruku=0;
    vector< vector<int> > task4stage;
    for (int i=0; i <res_am; i++){
        vector<int> r1;
        task4stage.push_back(r1);
    }
    vector<int> resourceAvibilities;
    resourceAvibilities.push_back(data->R1);
    resourceAvibilities.push_back(data->R2);
    resourceAvibilities.push_back(data->R3);
    resourceAvibilities.push_back(data->R4);
    while(jobsToDo>1){
        cost++;
        vector<pair<int, int> > row;
        vector<int> newAvaible;
        for(int i=0; i<res_am; i++ ){
            if(!available[i].empty()){
                //wybranie taskow
                for ( auto it = priority[i].begin(); it != priority[i].end(); it++)
                    if  ( contains(available[i], *it) && !contains(task4stage[i], *it) && resourceAvibilities[i] - data->usingResources[*it].second >= 0 ){
                        task4stage[i].push_back(*it);
                        resourceAvibilities[i] -= data->usingResources[*it].second;
                    }
                //-------------

                vector<int> toRemove; 
                for ( auto task = task4stage[i].begin(); task != task4stage[i].end(); task++){
                    if(!fitnessOnly)
                        row.push_back(pair<int, int>(data->usingResources[*task].first, *task));
                    durat[*task]--;
                    //task zakonczony
                    if(durat[*task]==0){
                        for(int j=0; j<available[i].size(); j++){
                            if(available[i][j]==*task){
                                remove(available[i].begin(),available[i].end(),*task);
                                available[i].pop_back();
                                resourceAvibilities[i] += data->usingResources[*task].second;
                                jobsToDo--;
                                for ( auto it = data->seccessors[*task].begin(); it != data->seccessors[*task].end(); it++){ 
                                    if(--stillRequiedTaskToStart[*it-1]==0)
                                        newAvaible.push_back(*it-1);
                                }
                                toRemove.push_back(*task);
                                break;
                            }
                        }
                    }
                }
                for ( auto it = toRemove.begin(); it != toRemove.end(); it++){ 
                    remove(task4stage[i].begin(), task4stage[i].end(), *it);
                    task4stage[i].pop_back();
                }
                
            }
        }
        for ( auto it = newAvaible.begin(); it != newAvaible.end(); it++)
            if(*it!=data->lastJob-1)
                // dodanie_nowych_dostępnych_taskow[id_resource][id_task]
                available[data->usingResources[*it].first].push_back(*it);
        if(!fitnessOnly){
            whole_sol.push_back(row);
            for (int i = 0; i < whole_sol[poglodowaZmiennaDoWydruku].size() && !fitnessOnly; i++) {
                cout << "R" << whole_sol[poglodowaZmiennaDoWydruku][i].first +1<< ": " << whole_sol[poglodowaZmiennaDoWydruku][i].second +1 << "\t";
            }
            cout << endl;
            poglodowaZmiennaDoWydruku++;
        }
    }
    if(!fitnessOnly)
        cout << "Koszt rozwiazania to: " << cost << endl;
    return;
}

bool Individual::contains(vector<int> vec, int val){
    for ( auto it2 = vec.begin(); it2 != vec.end(); it2++)
        if (val==*it2)
            return true;
    return false;
}

