
#include "../include/Session.h"
#include "../include/Tree.h"
#include "../include/Graph.h"
#include <vector>
#include "iostream"

using namespace std;

//constructor
Tree::Tree(int rootLabel) : node(rootLabel), children(0){};

//destructor
Tree::~Tree() {clear();}

void Tree::clear() {
    for (auto & i : children) {
        delete i;
    }
    children.clear();
}
//copy constructor
Tree::Tree(const Tree &likeThis): node(likeThis.node), children(0){
    for(auto& elem: likeThis.children){
        addChild(elem->clone());
    }
}
//copy assignment operator
const Tree& Tree::operator=(const Tree &other) {
    if(this != &other) {
        clear();
        node = other.getNode();
        for (auto &i :other.getChildren()) {
            addChild(i->clone());
        }
    }
    return *this;
}

//move constructor
Tree::Tree(Tree &&other): node(other.getNode()), children(other.getChildren()) {
    other.children.clear();
}

//move assignment operator
const Tree& Tree::operator=(Tree &&other) {
    if( this != &other) {
        clear();
        node = other.getNode();
        children = other.children;
        other.children.clear();
    }
    return *this;
}

Tree * Tree::BFS(const Session &session, int rootLabel) {
    vector<bool> visited(session.getGraph().getGraphSize());
    queue<Tree*> *q = new queue<Tree*>;
    visited[rootLabel] = true;
    Tree *t = createTree(session, rootLabel);
    q->push(t);
    q->front()->BFS(session, *q, visited);
    delete q;
    return t;
}


void Tree::BFS(const Session &session, queue<Tree*>& q, vector<bool>& visited) {

    int TreeRoot = q.front()->getNode();
    for (unsigned int i = 0; i < session.getGraph().getEdges()[TreeRoot].size(); i++) {
        if (session.getGraph().getEdges()[TreeRoot][(int)i] == 1 && !visited[(int)i]) {
            visited[(int)i] = true;
            Tree *child = createTree(session, (int)i);
            addChild(child);
            q.push(child);
        }
    }
    q.pop();
    if(!q.empty()) q.front()->BFS(session, q, visited);

}


Tree * Tree::createTree(const Session &session, int rootLabel) {
    TreeType t = session.getTreeType();
    if (t==Root){
        RootTree *RT = new RootTree(rootLabel);
        return RT;
    }
    if(t==Cycle){
        CycleTree *CT = new CycleTree(rootLabel, session.getCycle());
        return CT;
    }
    else{
        MaxRankTree *MRT = new MaxRankTree(rootLabel);
        return MRT;
    }
}
void Tree::addChild(Tree *child) {
    if(child != nullptr){
        children.push_back(child);
    }
}

void Tree::addChild(const Tree &child) {
    Tree* clone = child.clone();
    children.push_back(clone);
}

int Tree::getNode() const {
    return node;
}

vector<Tree *> Tree::getChildren() const{
    return children;
}


//MaxRankTree

//constructor
MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}

MaxRankTree * MaxRankTree::clone() const{
    MaxRankTree *ct = new MaxRankTree(getNode());
    if (getChildren().size()==0) return ct;
    for (unsigned int i = 0; i<getChildren().size(); i++){
        ct->addChild(this->getChildren()[i]->clone());
    }
    return ct;
}

int MaxRankTree::traceTree() {
   std::pair<int,int> pair = trace();
    return pair.first;
}

std::pair<int, int> MaxRankTree::trace() {
    std::pair<int,int> output(getNode(), getChildren().size());
    for (unsigned int i = 0; i < getChildren().size(); ++i) {
        std::pair<int,int> toCompare =((MaxRankTree *)(getChildren()[i]))->trace();
        if(toCompare.second > output.second){
            output.first = toCompare.first;
            output.second = toCompare.second;
        }
    }
    return output;
}

//CycleTree
//constructor
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle){};

CycleTree * CycleTree::clone() const {
    CycleTree *ct = new CycleTree(getNode(),currCycle);
    if (getChildren().size()==0) return ct;
    for (unsigned int i = 0; i<getChildren().size(); i++){
        ct->addChild(this->getChildren()[i]->clone());
    }
    return ct;
}

int CycleTree::traceTree() {
    vector <Tree*> children = getChildren();
    Tree *tree = this;
    for (int i = 0; i < currCycle && children.size() > 0; ++i) {
        tree = children[0];
        children = tree->getChildren();
    }
    return tree->getNode();
}

//RootTree
RootTree * RootTree::clone() const {
    return new RootTree(this->getNode());
}
//constructor
RootTree::RootTree(int rootLabel) : Tree(rootLabel){}

int RootTree::traceTree() {
    return getNode();
}

