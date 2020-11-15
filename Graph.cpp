#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

void Graph::qsort_edges(int firstEdge, int lastEdge, vector<Edge> &edges) {
    if (firstEdge < lastEdge) {
        int i = firstEdge, j = lastEdge;
        Edge mid = edges[(i + j) / 2];
        edges[(i + j) / 2] = edges[i];

        while (i < j) {
            while ((i < j) && ((edges[j].u > mid.u) || ((edges[j].u == mid.u) && (edges[j].v > mid.v))))
                j--;
            if (i < j) {
                edges[i] = edges[j];
                i++;
            }
            while ((i < j) && ((edges[i].u < mid.u) || ((edges[i].u == mid.u) && (edges[i].v < mid.v))))
                i++;
            if (i < j) {

                edges[j] = edges[i];
                j--;
            }
        }

        edges[i] = mid;
        qsort_edges(firstEdge, i - 1, edges);
        qsort_edges(i + 1, lastEdge, edges);
    }
}

bool Graph::build(string data, bool directed) {
    dataset = remove_extension(data);
    ifstream input(data.c_str());
    if(!input.is_open())
        return false;
    cout << data.c_str();

    int source, target;
    maxNode = -1;
    input >> n >> m;
    for (int i = 0; i < m; i++) {
        input >> source >> target;
        if (maxNode < source)
            maxNode = source;
        if (maxNode < target)
            maxNode = target;
    }
    maxNode++;
    input.close();

    index.resize(maxNode);
    outdegree.resize(maxNode);
    indegree.resize(maxNode);

    cout << "Building graph of: " << dataset.c_str() << " started" << endl;
    input.open(data.c_str());
    input >> n >> m;
    if (!directed) {
        edges.resize(m * 2);
        for (int i = 0; i < m; i++) {
            input >> edges[i].u >> edges[i].v;
            edges[i + m].u = edges[i].v;
            edges[i + m].v = edges[i].u;
            edges[i].c = 1;
            edges[i + m].c = 1;
            outdegree[edges[i].u]++;
            outdegree[edges[i].v]++;
            indegree[edges[i].u]++;
            indegree[edges[i].v]++;
        }
        m = 2 * m;
        edges.resize(m);
    } else {
        edges.resize(m + 1);
        for (int i = 0; i < m; i++) {
            input >> edges[i].u >> edges[i].v;
            edges[i].c = 1;
            outdegree[edges[i].u]++;
            indegree[edges[i].v]++;
        }
    }
    input.close();

    qsort_edges(0, m - 1, edges);

    int m1 = 0;
    for (int i = 1; i < m; i++) {
        if (edges[i].u != edges[i].v)
            if ((edges[i].u != edges[m1].u) || (edges[i].v != edges[m1].v)) {
                m1++;
                edges[m1] = edges[i];
            } else {
                edges[m1].c++;
            }
    }

    if (m != 0)
        m = m1 + 1;
    edges.resize(m);
    for (int i = 0; i < maxNode; i++)
        index[i] = -1;
    for (int i = 0; i < m; i++)
        index[edges[i].u] = i;

    for (int i = 1; i < maxNode; i++)
        if (index[i] < index[i - 1])
            index[i] = index[i - 1];

    return true;
}


int Graph::getN() {
    return n;
}

int Graph::getM() {
    return m;
}

int Graph::getMaxNode() {
    return maxNode;
}

void Graph::removeMultiplicity() {
    for (int i = 0; i < m; i++)
        this->edges[i].c = 1;
}

double Graph::getOutDegree(int node) {
    return outdegree[node];
}

double Graph::getInDegree(int node) {
    return indegree[node];
}

vector<double> Graph::getInDegrees() {
    return indegree;
}

vector<double> Graph::getOutDegrees() {
    return outdegree;
}

int Graph::getNeighbor(int node) {
    if (node == 0)
        return index[node] + 1;
    else
        return index[node] - index[node - 1];
}

Edge Graph::getEdge(int node, int idx) {
    if (node == 0)
        return edges[idx];
    else
        return edges[index[node - 1] + 1 + idx];
}

string Graph::getDataset() {
    return dataset;
}

string Graph::remove_extension(const string& filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == string::npos) return filename;
    return filename.substr(0, lastdot);
}