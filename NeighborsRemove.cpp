#include <stdio.h>
#include <queue>
#include <string.h>
#include "NeighborsRemove.h"
#include "Graph.h"

void NeighborsRemove::run(Graph *g, double rate, int level) {
    sprintf(file, "NeighborsRemove_%s_p=%.2f_L=%degree.txt",
            g->getDataset().c_str(), rate, level);
    outputList = new int[setSize];
    FILE *out= fopen(file, "w");
    n = g->getMaxNode();
    degrees = g->getOutDegrees();
    bool *used = new bool[n]();
    int *levels = new int[n];
    for (int i = 0; i < setSize; i++) {
        memset(levels, -1, sizeof(int) * n);
        double max = -1;
        int seed = -1;
        for (int j = 0; j < n; j++)
            if (!used[j])
                if (degrees[j] > max) {
                    max = degrees[j];
                    seed = j;
                }

        outputList[i] = seed;
        fprintf(out, "%d %f\n", seed, degrees[seed]);
        queue<int> neighborhood;
        neighborhood.push(seed);
        levels[seed] = 0;
        while (!neighborhood.empty()) {
            int currentNode = neighborhood.front();
            if (levels[currentNode] > level)
                break;
            for (int j = 0; j < g->getNeighbor(currentNode); j++) {
                Edge e = g->getEdge(currentNode, j);
                if (levels[e.v] == -1) {
                    levels[e.v] = levels[currentNode] + 1;
                    neighborhood.push(e.v);
                }
            }
            used[currentNode] = true;
            neighborhood.pop();
        }
    }
    delete[] levels;
    delete[] used;
    fclose(out);
}

int *NeighborsRemove::getSet() {
    return outputList;
}
