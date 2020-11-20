
#include "../include/Graph.h"
#include "../include/Tree.h"
#include <iostream>
using namespace std;

Graph::Graph():edges(std::vector<std::vector<int>>()), infected_list(std::vector<int>(edges.size())) {
    for (unsigned int i = 0; i < infected_list.size(); ++i) {
        infected_list[i] = 0;
    }
}
Graph::Graph(std::vector<std::vector<int>> matrix): edges(matrix), infected_list() {
    for (unsigned int i = 0; i < matrix.size(); ++i) {
        infected_list.push_back(0);
    }
}
Graph::Graph(Graph const &t): edges(t.edges), infected_list(t.infected_list){}

void Graph::set_graph(std::vector<std::vector<int>> matrix) {
    edges = matrix;
}
bool Graph::isInfected(int nodeInd) {
    return (infected_list[nodeInd] == 2);
}

void Graph::infectNode(int nodeInd) {
    infected_list[nodeInd] = 2;
}



    const vector<vector<int>> Graph::getEdges() const {
    return edges;
}

int Graph::getGraphSize() const {
    return edges.size();
}

vector<int> Graph::getNeighbors(int node) const {
    vector<int> neighbors;
    for (unsigned int i = 0; i < edges.size(); ++i) {
        if(edges[node][i] == 1){
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

vector<int> Graph::getList() const{
    return infected_list;
}

void Graph::remove_edge(int i, int j) {
    edges[i][j] = 0;
    edges[j][i] = 0;
}

void Graph::amputate(int toAmputate) {
    for (unsigned int i = 0; i<edges[toAmputate].size(); i++){
        if (edges[toAmputate][i]==1) remove_edge(toAmputate, (int)i);
    }
}

void Graph::duplicate(int node) {
    infected_list[node] = 1;
}

vector<int> Graph::getOutput(){
    vector<int> output;
    for (unsigned int i = 0; i < infected_list.size(); ++i) {
        if(infected_list[i] == 2) {
            output.push_back(i);
        }
    }
    return output;
}

bool Graph::isHealthy(int node) {
    return (infected_list[node] == 0);
}

void Graph::setlist() {
    for (unsigned int i = 0; i < edges.size(); ++i) {
        infected_list.push_back(0);
    }
}

void Graph::initialize(int node) {
    infected_list[node] = 1;
}

