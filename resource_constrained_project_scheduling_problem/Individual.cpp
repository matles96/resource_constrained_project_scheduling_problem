#include "Individual.h"

void Individual::print(){
    for (int i=0; i<stages_am; i++){
        cout << endl << i << ".\t";
        for (int j=0; j<resources_am; j++){
            cout << "R" << j << ": " << whole_sol[i][j].second << "\t";
        }
    }
    cout << endl;
}

Individual::Individual(int res) {
    stages_am = 0;
    resources_am = res;
}