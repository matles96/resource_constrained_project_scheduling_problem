#include "Individual.h"

void Individual::print(){
    for (int j = 0; j < whole_sol.size(); j++) {
        for (int i = 0; i < whole_sol[j].size(); i++) {
            cout << "R" << whole_sol[j][i].first << ": " << whole_sol[j][i].second << "\t";
        }
        cout << endl;
    }
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
    vector<int> task4stage = {-1, -1, -1, -1};
    while(jobsToDo>1){
        cost++;
        vector<pair<int, int> > row;
        vector<int> newAvaible;
        for(int i=0; i<res_am; i++ ){
            if(!available[i].empty()){
                for ( auto it = priority[i].begin(); it != priority[i].end() && task4stage[i]==-1; it++)
                    if  (contains(available[i], *it)){
                        task4stage[i] = *it;
                        break;
                    }
                if(!fitnessOnly)
                    row.push_back(pair<int, int>(data->usingResources[task4stage[i]].first, task4stage[i]));
                durat[task4stage[i]]--;
                if(durat[task4stage[i]]==0){
                    for(int j=0; j<available[i].size(); j++){
                        if(available[i][j]==task4stage[i]){
                            remove(available[i].begin(),available[i].end(),task4stage[i]);
                            available[i].pop_back();
                            jobsToDo--;
                            for ( auto it = data->seccessors[task4stage[i]].begin(); it != data->seccessors[task4stage[i]].end(); it++){ 
                                if(--stillRequiedTaskToStart[*it-1]==0)
                                    newAvaible.push_back(*it-1);
                            }
                            task4stage[i] = -1;
                            break;
                        }
                    }
                }
            }
        }
        for ( auto it = newAvaible.begin(); it != newAvaible.end(); it++)
            // dodanie_nowych_dostępnych_taskow[id_resource][id_task]
            available[data->usingResources[*it].first].push_back(*it);
        if(!fitnessOnly)
            whole_sol.push_back(row);
        for (int i = 0; i < whole_sol[poglodowaZmiennaDoWydruku].size() && !fitnessOnly; i++) {
            cout << "R" << whole_sol[poglodowaZmiennaDoWydruku][i].first << ": " << whole_sol[poglodowaZmiennaDoWydruku][i].second << "\t";
        }
        cout << endl;
        poglodowaZmiennaDoWydruku++;
    }
    cout << "Koszt rozwiazania to: " << cost << endl;
    return;
}

bool Individual::contains(vector<int> vec, int val){
    for ( auto it2 = vec.begin(); it2 != vec.end(); it2++)
        if (val==*it2)
            return true;
    return false;
}

