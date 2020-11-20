#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include "../include/Tree.h"
using namespace std;


class Graph{
public:
    Graph();
    Graph(Graph const &t);
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void remove_edge(int i, int j);
    vector<int> getNeighbors(int node) const;
    void set_graph(std::vector<std::vector<int>> matrix);
    const vector<vector<int>> getEdges() const;
    vector<int> getList() const;
    int getGraphSize() const;
    void amputate(int toAmputate);
    void initialize(int node);
    void duplicate(int node);
    bool isHealthy(int node);
    vector<int> getOutput();
    void setlist() ;
private:
    std::vector<std::vector<int>> edges;
    std::vector<int> infected_list;
};

#endif
