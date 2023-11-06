/*
 * Switch.cc
 *
 *  Created on: 2023��10��30��
 *      Author: Administrator
 */
#include "veins/base/modules/BaseModule.h"
#include "veins/base/modules/UnicastMessage_m.h"
#include "veins/base/modules/BroadcastMessage_m.h"
#include <unordered_map>

using namespace veins;
//using veins::cGateToEvent;
//using veins::cMessage;

class Switch : public BaseModule
{
    public:
        virtual void initialize(int stage) override;
        virtual void handleMessage(cMessage *msg) override;
    protected:
        int getRSUNum();
        // Add a map from RSU identifiers to gate indices, so that unicast can be achieved.
        std::unordered_map<int, int> rsuIdToGateIndex;
    private:
        int gateSize;
};

Define_Module(Switch);

void Switch::initialize(int stage)
{
    BaseModule::initialize(stage);
    // Initialize the map from RSU identifiers to gate indices
    // According to the Network topology, rsu[0].gateIO <--> switch[0].gateIO. So the topology design should be ordered, i.e., from rsu 0->n.
    gateSize = getRSUNum();
    for (int i = 0; i < gateSize; ++i)
    {
        cGate* gateOut = gate("gateOut", i);
        if (gateOut)
        {
            // Assume that the RSU identifier is the index of the gate
            rsuIdToGateIndex[i] = i;
        }
    }
}

void Switch::handleMessage(cMessage *msg)
{
    //Determine whether the message is unicast or broadcast message
    if (UnicastMessage *unicastMsg= dynamic_cast<UnicastMessage *>(msg))
    {
        EV << "Unicast message coming!!!\n";
        //Perform the unicast communication
        int RSUId = unicastMsg->getTargetRSUId();
        //Get the data form UnicastMessage
        const cMessage *data=unicastMsg->getData();
        if (data == nullptr) {
            EV_ERROR << "Data is nullptr." << std::endl;
            return;
        }
        //If RSUId=-1, then it unicast message will be sent to the controller!
        if (RSUId == -1) {
            send(data->dup(),"gateOut",gateSize);
        } else
        {
            auto it = rsuIdToGateIndex.find(RSUId);
            if (it != rsuIdToGateIndex.end())
            {
                cGate* gateOut = gate("gateOut", it->second);
                if (gateOut)
                {
                    EV << "Sending to RSU "<<RSUId<<std::endl;
                    send(msg->dup(), gateOut);
                }
            }
            else
            {
                EV_ERROR << "RSU " << RSUId << " not found!" << std::endl;
            }
        }

    } else if(BroadcastMessage *broadcastMsg=dynamic_cast<BroadcastMessage *>(msg))
    {
        EV << "Broadcast message coming!!!\n";
        cGate* arrivalGate = msg->getArrivalGate();
        const cMessage *data=broadcastMsg->getData();
        for (int i = 0; i < gateSize; ++i)
        {
            cGate* gateOut = gate("gateOut", i);
            if (gateOut && gateOut->getPathEndGate()->getOwnerModule() != arrivalGate->getOwnerModule())
            {
                send(data->dup(), gateOut);
            }
        }
        EV << "Switching!" << std::endl;
    } else
    {
        //Maybe other types
    }
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

