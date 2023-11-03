/*
 * Controller.cc
 *
 *  Created on: 2023Äê11ÔÂ1ÈÕ
 *      Author: Administrator
 */

#include "Controller.h"

Define_Module(Controller);

void Controller::initialize(int stage)
{
    BaseModule::initialize(stage);
    // Initialization code goes here
}

// ToModify
void Controller::handleMessage(cMessage *msg)
{
    if (PoWResult *result = dynamic_cast<PoWResult *>(msg)) {
        // A PoWResult message has been received
        EV << "RSU " << result->getRsuId() << " found a nonce: " << result->getNonce() << "\n";
        // Check if this is the first result
        if (processedHashes.find(result->getHash()) == processedHashes.end()) {
            processedHashes.insert(result->getHash());
            EV << "RSU " << result->getRsuId() << " is the first to find a nonce!\n";
            // Send a PoWPackingPermission message to the Switch
            PoWPackingPermission *permission = new PoWPackingPermission();
            permission->setRsuId(result->getRsuId());
            permission->setHash(result->getHash());
            permission->setNonce(result->getNonce());
            send(permission, "out");
            EV << "New data received. Processing...\n";
        } else {
            // Herein we can see that the PoWResult corresponding to "data" is not the first one.
            EV << "The data has been processed before. Ignoring...\n";
        }
        delete msg;
    } else {
        // Handle other messages
    }
}


