/*
 * Controller.cc
 *
 *  Created on: 2023��11��1��
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
        EV << "The hash is: "<< result->getHash()<< "\n";
        // Check if this is the first result
        if (processedHashes.find(result->getBlockData()) == processedHashes.end()) {
            processedHashes.insert(result->getBlockData());
            EV << "RSU " << result->getRsuId() << " is the first to find a nonce!\n";
            // Send a PoWPackingPermission message to the Switch
            PoWPackingPermission *permission = new PoWPackingPermission();
            permission->setRsuId(result->getRsuId());
            permission->setHash(result->getHash());
            permission->setNonce(result->getNonce());
            permission->setBlockData(result->getBlockData());
            permission->setTimestamp(result->getTimestamp());
            BroadcastMessage *broadcastMsg= new BroadcastMessage();
            broadcastMsg->setData(permission);
            send(broadcastMsg, "out");
            EV << "New valid block will be recorded into the chain. Processing...\n";
        } else {
            // Herein we can see that the PoWResult corresponding to "data" is not the first one.
            EV << "The block for the data has generated before. Ignoring...\n";
        }
        delete msg;
    } else {
        // Handle other messages
    }
}


