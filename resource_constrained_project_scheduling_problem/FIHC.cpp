#include "FIHC.h"

void FIHC::fihc(ProblemInstance* data, Individual* ind){
    ind->create_by_priority_lists(data, true);
    int res_am = 4;
    Individual* copy_ind_to_test = new Individual;
    bool wasImproved;
    copy_ind_to_test->priority = ind->priority;
    do{
        wasImproved = false;
        for (int i=0; i<res_am && !wasImproved; i++){
            if(copy_ind_to_test->priority[i].size()>1){
                for(int j=0; j<copy_ind_to_test->priority[i].size() && !wasImproved; j++){
                    for(int k=j+1; k<copy_ind_to_test->priority[i].size() && !wasImproved; k++){
                        swap(copy_ind_to_test->priority[i][j], copy_ind_to_test->priority[i][k]);
                        copy_ind_to_test->create_by_priority_lists(data, true);
                        if(copy_ind_to_test->cost < ind->cost){
                            wasImproved=true;
                            ind->priority = copy_ind_to_test->priority;
                            ind->cost = copy_ind_to_test->cost;
                            //cout<< "Nowe rozw ma koszt: " << ind->cost << endl;
                        }else{
                            copy_ind_to_test->priority = ind->priority;
                        }
                    }   
                }
            }
        }
    }while(wasImproved);

    return;
}




