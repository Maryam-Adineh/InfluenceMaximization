#ifndef NEIGHBORSREMOVE_H
#define NEIGHBORSREMOVE_H

#include "limit.h"
#include "Graph.h"

class NeighborsRemove {
private:
    int n;
    vector<double> degrees;
    int * outputList;
    char file[STR_LEN];

public:
    void run(Graph *g, double p, int level);
    int * getSet();
};


#endif //NEIGHBORSREMOVE_H
