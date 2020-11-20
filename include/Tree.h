

#ifndef TREE_H_
#define TREE_H_
#include "../include/Graph.h"
#include <vector>
#include <queue>
using namespace std;

class Session;

class Tree{
public:
    Tree(int rootLabel);
    //rule of 5
    Tree(const Tree& likeThis);
    virtual ~Tree();
    const Tree& operator=(const Tree &other);
    Tree(Tree&& other);
    const Tree& operator=(Tree&& other);
    //rule of 5//
    void addChild(const Tree& child);
    void clear();
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    virtual Tree* clone() const=0;
    vector<Tree*> getChildren() const;
    void addChild(Tree* child);
    int getNode() const;
    static Tree* BFS(const Session& session, int rootLabel);
    //debugging
    void print();
private:
    int node;
    std::vector<Tree*> children;
    void BFS(const Session& session, queue<Tree*>& q, vector<bool>& visited);
};

class CycleTree: public Tree{
public:
    //rule of 5
    CycleTree(int rootLabel, int currCycle);
    //rule of 5

    virtual int traceTree();
    virtual CycleTree* clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    //rule of 5
    explicit MaxRankTree(int rootLabel);//constructor
    //rule of 5

    virtual int traceTree();
    virtual MaxRankTree* clone() const;
private:
    std::pair<int,int> trace();
};

class RootTree: public Tree{
public:
    //rule of 5
    RootTree(int rootLabel);
    //rule of 5
    virtual RootTree* clone() const;
    virtual int traceTree();
};

#endif
