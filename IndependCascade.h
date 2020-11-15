#ifndef PUBLIC_INFLUENCEMAXIMIZATION_INDEPENDCASCADE_H
#define PUBLIC_INFLUENCEMAXIMIZATION_INDEPENDCASCADE_H

#include "Graph.h"

class IndependCascade {
private:
    static int n;
    static Graph *graph;
    static double ratio;
public:
    IndependCascade(Graph *g, double ratio);
    static double run(int set[], int size, int iteration);
};


#endif //PUBLIC_INFLUENCEMAXIMIZATION_INDEPENDCASCADE_H
