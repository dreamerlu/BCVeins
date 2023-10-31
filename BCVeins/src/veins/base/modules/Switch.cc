/*
 * Switch.cc
 *
 *  Created on: 2023Äê10ÔÂ30ÈÕ
 *      Author: Administrator
 */
#include <veins/base/modules/BaseModule.h>

using veins::BaseModule;
//using veins::cGateToEvent;
//using veins::cMessage;

class Switch : public BaseModule
{
    public:
        virtual void initialize(int stage) override;
        virtual void handleMessage(cMessage *msg) override;
    protected:
        int getRSUNum();
};

Define_Module(Switch);

void Switch::initialize(int stage)
{
    BaseModule::initialize(stage);
    // Initialization code goes here
}

void Switch::handleMessage(cMessage *msg)
{
    cGate* arrivalGate = msg->getArrivalGate();
    int gateSize = getRSUNum();
    EV << "The current RSU number is :"<<getRSUNum()<<std::endl;

    for (int i = 0; i < gateSize; ++i)
    {
        cGate* gateOut = gate("gateOut", i);
        if (gateOut && gateOut->getPathEndGate()->getOwnerModule() != arrivalGate->getOwnerModule())
        {
            send(msg->dup(), gateOut);
        }
    }
    EV << "Switching!" << std::endl;
    delete msg;
}

int Switch::getRSUNum()
{
    int count = 0;
    for (cModule::SubmoduleIterator iter(this->getParentModule()); !iter.end(); iter++)
    {
        cModule* submod = *iter;
        if (strcmp(submod->getModuleType()->getName(), "RSU") == 0)
        {
            count++;
        }
    }
    return count;
}

/*void Switch::handleMessage(cMessage *msg)
{
    cGate* arrivalGate = msg->getArrivalGate();

    for (cModule::GateIterator i(getParentModule()); !i.end(); i++)
    {
        cGate* gate = *i;
        if (gate->getType() == cGate::Type::OUTPUT && gate != arrivalGate)
        {
            send(msg->dup(), gate->getName());
        }
    }
    EV << "Switching!"<<std::endl;
    delete msg;
}*/

