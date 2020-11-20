#ifndef SESSION_H_
#define SESSION_H_
#include "../include/json.hpp"
#include <vector>
#include <string>
#include "../include/Graph.h"
#include "../include/Agent.h"

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(Graph g, vector<Agent*> v, TreeType t);
    Session(const std::string& path);
    //rule of 5
    Session(const Session& session);
    virtual ~Session();

    const Session& operator=(const Session &other);
    Session(Session&& other);
    const Session& operator=(Session&& other);
    //rule of 5
    void simulate();
    void clear();
    void addAgent(const Agent& agent);
    void addAgent(Agent* agent);
    void setGraph(const Graph& graph);
    const Graph& getGraph() const;
    void enqueueInfected(int a);
    int dequeueInfected();
    int getListSize() const;
    TreeType getTreeType() const;
    void virusHasSpread();
    bool isInfectedListEmpty();
    int getCycle() const;
    void duplicate(int node);

private:
    vector<int> infectedList;
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycleCounter;
    bool virusSpread;
};

#endif