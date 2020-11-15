#ifndef DEGREEDECREASE_H
#define DEGREEDECREASE_H

#include <vector>
#include "limit.h"
#include "Graph.h"

class DegreeDecrease {
private:
    int n;
    char file[STR_LEN];
    int *outputList;
    vector<double> degrees;
    int *seeds;
public:
    int* getSet();
    void run(Graph *g,double p, double alpha, double beta, double epsilon);
};


#endif //DEGREEDECREASE_H
