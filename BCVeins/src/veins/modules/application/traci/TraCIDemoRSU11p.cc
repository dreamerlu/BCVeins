//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include <veins/modules/application/blockchain/SHA256.h>
#include "veins/modules/application/traci/TraCIDemoRSU11p.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"
#include "veins/modules/application/blockchain/Block_m.h"
#include "veins/modules/application/blockchain/PoWRequest_m.h"
#include "veins/modules/application/blockchain/PoWModule.h"
#include "veins/modules/application/blockchain/PoWResult_m.h"
#include "veins/modules/application/blockchain/PoWPackingPermission_m.h"
#include "veins/base/modules/UnicastMessage_m.h"
#include "veins/base/modules/BroadcastMessage_m.h"
#include <string>

using namespace veins;

Define_Module(veins::TraCIDemoRSU11p);

void TraCIDemoRSU11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        //initial setting for sadistically counting
        senderAddresses.setName("senderAddresses");
        i2vDelayVector.setName("I2VDelay");
        processDelay= getModuleByPath("rsu[0]")->par("processDelay");

        //test PoW
        powModule = getParentModule()->getSubmodule("powModule");
        if (!powModule) {
            EV << "Error: No PoWModule found";
        } else {
            PoWRequest* req = new PoWRequest();
            req->setData("hello");
            send(req, "outToBC");
            req = new PoWRequest();
            req->setData("aloha");
            sendDelayed(req, 0.00001, "outToBC");
            req = new PoWRequest();
            req->setData("hahaha");
            sendDelayed(req, 0.00002, "outToBC");
        }
    }
}

void TraCIDemoRSU11p::onWSA(DemoServiceAdvertisment* wsa)
{
    // if this RSU receives a WSA for service 42, it will tune to the chan
}

void TraCIDemoRSU11p::onWSM(BaseFrame1609_4* frame)
{
    //message from vehicle
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(frame)) {
        //for statistic
        simtime_t delay = simTime() - wsm->getTimestamp();
        i2vDelayVector.record(delay);
        EV << "Get sender id: " <<wsm->getSenderAddress()<<std::endl;
        senderAddresses.record(wsm->getSenderAddress());
        //triggering unicast to the sender vehicle
        RSUBasicMessage *rsuMsg =new RSUBasicMessage();
        populateWSM(rsuMsg);
        rsuMsg->setRecipientAddress(wsm->getSenderAddress());
        rsuMsg->setTimestamp(simTime());
        sendDelayedDown(rsuMsg,processDelay);
    }

}

void TraCIDemoRSU11p::handleMessage(cMessage *msg)
{
    if (Block *blockMsg= dynamic_cast<Block *>(msg)) {
        EV <<"Arriving! From gate: "<< blockMsg->getArrivalGate() << ", miner message: " << blockMsg->getMiner() << std::endl;
        delete msg;
    } else if (PoWResponse* resp = dynamic_cast<PoWResponse*>(msg)) {
        // Herein RSU receives the valid nonce from its PoWModule, so it can send the encapsulated unicast message to the controller.
        EV <<"Current time: "<< simTime() << ", Received PoWResponse: data=" << resp->getData() <<", nonce=" << resp->getNonce() << std::endl;
        PoWResult *res= new PoWResult();
        res->setRsuId(this->getParentModule()->getIndex());
        res->setBlockData(resp->getData());
        res->setHash(resp->getHash());
        res->setNonce(resp->getNonce());
        UnicastMessage *umsg= new UnicastMessage();
        umsg->setTargetRSUId(-1);
        umsg->setData(res);
        send(umsg,"gateOut",0);
        delete msg;
    } else if (PoWPackingPermission * ppp = dynamic_cast<PoWPackingPermission *>(msg)) {
        // Herein RSU receives the "valid" block
        EV << "I am receiving the PoWPackingPermission message" <<std::endl;
        send(ppp,"outToBC");
    }
    else {
        //do nothing currently
    }
}

void TraCIDemoRSU11p::handleSelfMsg(cMessage* msg)
{
    DemoBaseApplLayer::handleSelfMsg(msg);
}

int TraCIDemoRSU11p::getRSUNum()
{
    cModule* parentModule = getParentModule()->getParentModule();  // Get the grandparent module
    int numberOfRSUs = 0;
    for (cModule::SubmoduleIterator it(parentModule); !it.end(); ++it) {
        cModule* submodule = *it;
        std::string name = submodule->getName();  // Get the name of the submodule
        if (name.compare(0, 3, "rsu") == 0 ) {  // Check if the name starts with "rsu" and exclude self
            numberOfRSUs++;
        }
    }
    return numberOfRSUs;
}

/*
 * This method is only used for testing my design.
 * My notes:
 * 1. Unicast/Broadcast communications have been tested.
 * */
void TraCIDemoRSU11p::testMethods() {
    // just for SHA256 testing
    SHA256 sha;
    sha.update("hello world");
    std::array<uint8_t, 32> digest = sha.digest();
    EV << "SHA information:"<<SHA256::toString(digest)<<std::endl;
    // end
    // just for direct communications between RSUs
    // Sending direct message to all other RSUs
    /*Block *blockMsg= new Block();
    blockMsg->setMiner("test miner");
    int numOutGates = gateSize("gateOut");
    for (int i = 0; i < numOutGates; ++i) {
        // create a copy of the message for each gate
        EV << "Transmitting "<< i <<std::endl;
        Block *copy = blockMsg->dup();
        send(copy, "gateOut", i);
    }
    // delete the original message
    delete blockMsg;*/
    BroadcastMessage *broadMsg = new BroadcastMessage();
    send(broadMsg,"gateOut",0);
    Block *blockMsg= new Block();
    blockMsg->setMiner("test miner");
    UnicastMessage *uniMsg = new UnicastMessage();
    uniMsg->setTargetRSUId(1);
    uniMsg->setData(blockMsg);
    send(uniMsg,"gateOut",0);
    //test PoW
    powModule = getParentModule()->getSubmodule("powModule");
    if (!powModule) {
        EV << "Error: No PoWModule found";
    } else {
        PoWRequest* req = new PoWRequest();
        req->setData("hello");
        send(req, "outToBC");
    }
}

void TraCIDemoRSU11p::finish() {
    DemoBaseApplLayer::finish();
}
