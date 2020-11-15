#include <iostream>
#include <cstring>
#include <cmath>
#include "limit.h"
#include "Graph.h"
#include "IndependCascade.h"
#include "DegreeDecrease.h"
#include "NeighborsRemove.h"

using namespace std;
double timer;
clock_t start;

int setSize = 0;

void toSimulate(char *file, int *sett, double (*Run)(int set[], int size, int iter),
        int iteration) {
    FILE *out = fopen(file, "w");
    int *set = new int[setSize];
    for (int t = 0; t < setSize; t++) {
        set[t] = sett[t];
        fprintf(out, "%02d \t %10lg\n", t + 1, Run(set, t + 1, iteration));
    }
    fclose(out);
    delete set;
}

int main(int argc, char **argv) {
    Graph graph;
    string dataset;
    char timeFile[STR_LEN], infFile[STR_LEN];
    FILE *timeFile_p;
    double rate, alpha, beta, epsilon;
    int iteration;
    bool direction = true;
    if (argc != 7) {
        cout << "USAGE:\n"
             << "./InfluenceMaximization <remove|decrease> <dataset> <d|u> <p> <k> <R>";
        return 1;
    }

    if (!strncmp(argv[3], "u", 1))
        direction = false;
    rate = atof(argv[4]);
    setSize = atoi(argv[5]);
    iteration = atoi(argv[6]);

    if (!graph.build(argv[2], direction)) {
        cerr << "Failed to build graph" << endl;
        return 1;
    }

    time_t time1 = time(NULL);
    cout << "*************************************************\n";
    cout << "current time: " << ctime(&time1);
    cout << "dataset: " << graph.getDataset().c_str() << "\trate: " << rate << endl;
    cout << "*************************************************\n";
    IndependCascade ic(&graph, rate);

    if (!strncmp(argv[1],"decrease",strlen(argv[1]))) {
        DegreeDecrease decDeg;
        epsilon = 0.1;
        alpha = 50;
        beta = 10;
        start = clock();
        decDeg.run(&graph, rate, alpha, beta, epsilon);
        timer = (double) (clock() - start) / CLOCKS_PER_SEC;
        sprintf(timeFile, "DegreeDecrease_time_%s_p=%.2f_alpha=%.1f_beta=%.1f_e="
                          "%.2f.txt", graph.getDataset().c_str(), rate, alpha,
                          beta, epsilon);
        timeFile_p = fopen(timeFile, "w");
        fprintf(timeFile_p, "%f", timer);
        fclose(timeFile_p);
        sprintf(infFile, "DecreaseDegree_IC_%s_p=%.2f_alpha=%.1f_beta=%.1f_e="
                         "%.2f.txt", graph.getDataset().c_str(), rate, alpha,
                         beta, epsilon);
        toSimulate(infFile, decDeg.getSet(), IndependCascade::run, iteration);
    } else if (!strncmp(argv[1], "remove", strlen(argv[1]))) {
        NeighborsRemove remove;
        int level = round(sqrt(rate) * 12);
        start = clock();
        remove.run(&graph, rate, level);
        timer = (double) (clock() - start) / CLOCKS_PER_SEC;
        sprintf(timeFile, "NeighborsRemove_time_%s_p=%.2f_level=%d.txt",
                graph.getDataset().c_str(), rate, level);
        timeFile_p = fopen(timeFile, "w");
        fprintf(timeFile_p, "%f", timer);
        fclose(timeFile_p);
        sprintf(infFile, "NeighborsRemove_IC_%s_p=%.2f_level=%d.txt",
                graph.getDataset().c_str(), rate, level);
        toSimulate(infFile, remove.getSet(), IndependCascade::run, iteration);
    } else {
        cout << "Error: Unknown algorithm\n";
        return 1;
    }

    cout << "Finished successfully\n";
    return 0;
}