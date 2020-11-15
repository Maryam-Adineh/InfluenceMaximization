#include <stdio.h>
#include <queue>
#include <string.h>
#include "DegreeDecrease.h"
#include "Graph.h"

using namespace std;

void DegreeDecrease::run(Graph *g, double rate, double alpha, double beta,
                         double epsilon) {
    sprintf(file, "DecreaseDegree_%s_p=%.2f_alpha=%.1f_beta=%.1f_e=%.2f.txt",
            g->getDataset().c_str(), rate, alpha, beta, epsilon);
    n = g->getMaxNode();
    outputList = new int[setSize];
    degrees.resize(n);
    degrees = g->getOutDegrees();
    vector<bool> used(n);
    FILE *out = fopen(file, "w");
    for (int i = 0; i < setSize; i++) {
        vector<double> dec(n);
        double max = -1000000.0;
        int seed = -1;
        for (int j = 0; j < n; j++)
            if (!used[j])
                if (degrees[j] > max) {
                    max = degrees[j];
                    seed = j;
                }
        outputList[i] = seed;
        used[seed] = true;
        dec[seed] = alpha;
        fprintf(out, "%d %f\n", seed, degrees[seed]);
        queue<int> neighborhood;
        neighborhood.push(seed);
        while (!neighborhood.empty()) {
            int currentNode = neighborhood.front();
            for (int j = 0; j < g->getNeighbor(currentNode); j++) {
                Edge e = g->getEdge(currentNode, j);
                if (dec[e.v] == 0) {
                    dec[e.v] = dec[e.u] * (e.c) * beta * rate;
                    if (dec[e.v] >= epsilon) {
                        neighborhood.push(e.v);
                        degrees[e.v] -= dec[e.v];
                    }
                }
            }
            neighborhood.pop();
        }
    }
    fclose(out);
}

int *DegreeDecrease::getSet() {
    return outputList;
}

