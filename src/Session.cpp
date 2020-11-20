
#include "../include/Session.h"
#include <fstream>
#include <iostream>
#include "../include/Agent.h"
using json = nlohmann::json;
using namespace std;

//debugging constructor
//Session::Session(Graph g, vector<Agent*> v, TreeType t) : g(g), agents(v), treeType(t), infectedList(), cycleCounter(0), virusSpread(true){}
//constructor
Session::Session(const std::string& path): infectedList(0), g(), treeType(), agents(), cycleCounter(0), virusSpread(true){
    ifstream i(path);
    json j;
    i >> j;
    vector<vector<int>> v = j["graph"];
    g.set_graph(v);
    g.setlist();
    if (j["tree"] == "M") {
        treeType = MaxRank;
    } else if (j["tree"] == "C") {
        treeType = Cycle;
    }
    else{
        treeType = Root;
    }
    for(auto& elem: j["agents"]){
        if(elem[0] == "C"){
            addAgent(ContactTracer());
        }
        else{
            int k = elem[1];
            addAgent(Virus(k));
            g.initialize(k);
        }
    }
}

//copy constructor

Session::Session(const Session& session):infectedList(session.infectedList), g(session.getGraph()), treeType(session.getTreeType()),agents(),
                                                        cycleCounter(session.cycleCounter), virusSpread(session.virusSpread){
    for (unsigned int i = 0; i < session.agents.size(); ++i) {
        agents.push_back(agents[i]->clone());
    }
}

//destructor
Session::~Session() {clear();}

//assignment operator
const Session& Session::operator=(const Session &other) {
    if(this == &other){
        return *this;
    }
    clear();
    cycleCounter = other.cycleCounter;
    infectedList = other.infectedList;
    g = other.g;
    treeType = other.getTreeType();
    for(auto& elem: other.agents){
        addAgent(elem->clone());
    }
    return *this;
}


//move constructor

Session::Session(Session &&other): infectedList(other.infectedList), g(other.g), treeType(other.treeType), agents(other.agents), cycleCounter(other.cycleCounter), virusSpread(other.virusSpread){
    other.agents.clear();
}

//move assignment operator
const Session &Session::operator=(Session &&other) {
    if(this == &other){
        return *this;
    }
    clear();
    cycleCounter = other.cycleCounter;
    infectedList = other.infectedList;
    g = other.g;
    treeType = other.getTreeType();
    agents = other.agents;
    other.agents.clear();
    return *this;
}


const Graph& Session::getGraph() const {
    return g;
}

int Session::getCycle() const {
    return cycleCounter;
}


void Session::setGraph(const Graph &graph) {
    vector<vector<int>> k(graph.getEdges());
    g.set_graph(graph.getEdges());
}

void Session::virusHasSpread() {
    virusSpread=true;
}

void Session::simulate() {
    cycleCounter = 0;
    while(virusSpread){
        virusSpread = false;
        int k = agents.size();
        for (int i = 0; i < k; ++i) {
            agents[i]->act(*this);
        }
        cycleCounter++;
    }
    json output;
    output["graph"] = g.getEdges();
    output["infected"] = g.getOutput();
    ofstream i("./output.json");
    i << output;
}


TreeType Session::getTreeType() const {return treeType;}

void Session::enqueueInfected(int a) {
    infectedList.push_back(a);
    g.infectNode(a);
}

int Session::dequeueInfected() {
    int k = infectedList[0];
    infectedList.erase(infectedList.begin());
    return k;
}

void Session::addAgent(const Agent &agent) {
    Agent* clone = agent.clone();
    agents.push_back(clone);
}

int Session::getListSize() const {
    return infectedList.size();
}

void Session::clear() {
    for(auto& elem: agents){
        delete elem;
    }
    agents.clear();
}

void Session::addAgent(Agent *agent) {
    agents.push_back(agent);
}

bool Session::isInfectedListEmpty() {
    return infectedList.empty();
}

void Session::duplicate(int node) {
    g.duplicate(node);
}














