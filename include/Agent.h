#ifndef AGENT_H_
#define AGENT_H_

#include "../include/Session.h"
#include "../include/Tree.h"
#include <vector>

class Agent{
public:
    Agent();
    virtual Agent* clone() const=0;
    virtual void act(Session& session)=0;
    virtual ~Agent();
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session& session);
    virtual ContactTracer* clone() const;
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    Virus(Virus const &virus);
    virtual void act(Session& session);
    virtual Virus* clone() const;
    int getInd() const;
private:
    const int nodeInd;
};

#endif