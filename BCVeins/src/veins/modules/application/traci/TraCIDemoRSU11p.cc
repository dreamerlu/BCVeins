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

#include "veins/modules/application/traci/TraCIDemoRSU11p.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"
#include "veins/modules/application/traci/Block_m.h"
#include "SHA256.h"
#include <string>

using namespace veins;

Define_Module(veins::TraCIDemoRSU11p);

void TraCIDemoRSU11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        senderAddresses.setName("senderAddresses");
        i2vDelayVector.setName("I2VDelay");
        processDelay= getModuleByPath("rsu[0]")->par("processDelay");
        // just for SHA256 testing
        SHA256 sha;
        sha.update("hello world");
        std::array<uint8_t, 32> digest = sha.digest();
        EV << "SHA information:"<<SHA256::toString(digest)<<std::endl;
        // end
        // just for direct communications between RSUs
        // Sending direct message to all other RSUs
        Block *blockMsg= new Block();
        blockMsg->setMiner("test miner");
        int numOutGates = gateSize("gateOut");
        for (int i = 0; i < numOutGates; ++i) {
            // create a copy of the message for each gate
            EV << "Transmitting "<< i <<std::endl;
            Block *copy = blockMsg->dup();
            send(copy, "gateOut", i);
        }
        // delete the original message
        delete blockMsg;
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
    Block *blockMsg= dynamic_cast<Block *>(msg);
    if (blockMsg) {
        EV <<"Arriving! From gate: "<< blockMsg->getArrivalGate()<<", miner message: " << blockMsg->getMiner() <<std::endl;
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
