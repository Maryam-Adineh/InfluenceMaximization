#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include <vector>

using namespace std;

struct Edge {
    int u, v, c;
};

class Graph {
private:
    string dataset;
    int n;
    int m;
    int maxNode;
    vector<double> outdegree;
    vector<double> indegree;
    vector<int> index;
    vector <Edge> edges;

public:
    Graph() {n = 0; m = 0;};
    void qsort_edges(int h, int lastEdge, vector <Edge> &edgeVec);
    bool build(string dataset, bool directed);
    int getN(void);
    int getM(void);
    int getMaxNode(void);
    void removeMultiplicity(void);
    double getOutDegree(int node);
    double getInDegree(int node);
    vector<double> getInDegrees(void);
    vector<double> getOutDegrees(void);
    int getNeighbor(int node);
    Edge getEdge(int node, int idx);
    string getDataset();
    string remove_extension(const string& filename);
};

#endif //GRAPH_H
