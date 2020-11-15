#include "IndependCascade.h"

int IndependCascade::n = 0;
double IndependCascade::ratio = 0;
Graph* IndependCascade::graph;

IndependCascade::IndependCascade(Graph *g, double rate) {
    graph = g;
    n = graph->getMaxNode();
    ratio = rate;
    srand(time(NULL));
}

double IndependCascade::run(int set[], int size, int iteration) {
    double result = 0;
    int h, t;
    vector<int> selected(n);

    for (int it = 0; it < iteration; it++) {
        h = 0;
        t = size;
        vector<bool> active(n, false);

        for (int i = 0; i < size; i++) {
            selected[i] = set[i];
            active[set[i]] = true;
        }
        result += size;

        while (h < t) {
            int k = graph->getNeighbor(selected[h]);
            for (int i = 0; i < k; i++) {
                Edge e = graph->getEdge(selected[h], i);
                if (active[e.v])
                    continue;
                for (int j = 0; j < e.c; j++)
                    if (((double) rand() / (double) RAND_MAX) < ratio) {
                        selected[t] = e.v;
                        active[e.v] = true;
                        t++;
                        result++;
                        break;
                    }
            }
            h++;
        }
    }
    return result / iteration;
}
