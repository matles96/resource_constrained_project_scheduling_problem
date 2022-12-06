#include "Individual.h"

void Individual::print(){
    for (int j = 0; j < whole_sol.size(); j++) {
        for (int i = 0; i < whole_sol[j].size(); i++) {
            cout << "R" << whole_sol[j][i].first << ": " << whole_sol[j][i].second << "\t";
        }
        cout << endl;
    }
}

Individual::Individual(int res) {
    stages_am = 0;
    resources_am = res;
}