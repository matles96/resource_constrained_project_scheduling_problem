#include<vector>
#include "Individual.h"
#include "Random.h"
#include "FIHC.h"

using namespace std;
class P3
{
private:
    int pyramidLevelAmount;

public:
    vector<vector<Individual> > pyramid;

    int bestCost;
    bool checkIfAreTheSame(Individual* in1, Individual* in2);
    void findSollution(ProblemInstance* pi, int epochLimit);

};