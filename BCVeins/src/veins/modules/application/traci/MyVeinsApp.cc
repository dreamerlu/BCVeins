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

#include "veins/modules/application/traci/MyVeinsApp.h"

using namespace veins;

Define_Module(veins::MyVeinsApp);

void MyVeinsApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sendPeriodicMsgEventByVehicle = new cMessage("sendPeriodicMsgEventByVehicle");
        scheduleAt(simTime(), sendPeriodicMsgEventByVehicle);
        //for statistic
        v2vDelayVector.setName("V2VDelay");
        v2iDelayVector.setName("V2IDelay");
        processDelay= findModuleByPath("node[0]")->par("processDelay");
    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here
    }
}

void MyVeinsApp::finish()
{
    DemoBaseApplLayer::finish();
    // statistics recording goes here
}

void MyVeinsApp::onBSM(DemoSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
}

void MyVeinsApp::onWSM(BaseFrame1609_4* frame)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
    //message from vehicle or RSU
    if (TraCIDemo11pMessage* wsm = dynamic_cast<TraCIDemo11pMessage*>(frame)) {
        simtime_t delay = simTime() - wsm->getTimestamp();
        v2vDelayVector.record(delay);
    } else if (RSUBasicMessage* wsm = dynamic_cast<RSUBasicMessage*>(frame)) {
        //simtime_t delay = simTime() - wsm->getTimestamp();
        simtime_t delay = simTime() - msgGenTime;
        // discuss the potential correct implementation for v2i, i.e., v->i->v
        v2iDelayVector.record(delay+processDelay);
    }

}

void MyVeinsApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void MyVeinsApp::handleSelfMsg(cMessage* msg)
{
    if (msg == sendPeriodicMsgEventByVehicle) {
        TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage();
        populateWSM(wsm);
        // So the demodata field is used for storing the vehicle index.
        wsm->setDemoData(std::to_string(this->getParentModule()->getIndex()).c_str());
        wsm->setTimestamp(simTime());
        wsm->setByteLength(par("beaconLengthBits").intValue()/8);

        int schChannels[] = {174, 176, 178, 180};
        int randomIndex = intuniform(0, sizeof(schChannels)/sizeof(schChannels[0]) - 1);
        int selectedChannel = schChannels[randomIndex];
        wsm->setChannelNumber(selectedChannel);
        EV << "Sending message on Service Channel: " << selectedChannel << endl;
//        sendDown(wsm);
        sendDelayedDown(wsm, uniform(0.001, 0.005));
        // schedule new message
        simtime_t randInterval = uniform(0.001, 0.002);
//        simtime_t randInterval = 0;
        scheduleAt(simTime() + par("beaconInterval").doubleValue()+ randInterval, sendPeriodicMsgEventByVehicle);
    }
    else {
        //DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

/*void MyVeinsApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class
}*/
