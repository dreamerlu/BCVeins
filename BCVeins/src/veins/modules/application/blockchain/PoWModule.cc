/*
 * PoWModule.cc
 *
 *  Created on: 2023.11.1
 *      Author: Administrator
 *      In the version@2023.11.6, multiple PoWRequests are supported.
 */

// PoWModule.cc
#include "PoWModule.h"
#include "SHA256.h"
#include "PoWRequest_m.h"
#include "PoWResponse_m.h"
#include "PoWPackingPermission_m.h"

Define_Module(PoWModule);
using namespace veins;

void PoWModule::initialize()
{
    isProcessing = false;
    nonce = 0;
//    startSignal=new cMessage("start");
    continueSignal = new cMessage("continue");
//    scheduleAt(simTime() + par("PoWInterval").doubleValue(), startSignal);
}

void PoWModule::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        //For handling the scheduleAt-type PoW calculating request, i.e., mainly for con
        startPoW();
    } else if (PoWRequest* req = dynamic_cast<PoWRequest*>(msg)) {
        EV << "receving PoWRequest"<<std::endl;
        requestQueue.push(req);
        if (!isProcessing) {
            startNextPoW();
        }
    }
}

void PoWModule::startNextPoW()
{
    // Start the PoW for the request at the front of the queue
    if (!requestQueue.empty()) {
        isProcessing = true;
        PoWRequest* req = requestQueue.front();
        requestQueue.pop();
        data = req->getData();
        nonce = 0;
        startPoW();
    } else {
        isProcessing = false;
    }
}

void PoWModule::startPoW()
{
    SHA256 sha;
    sha.update(data + std::to_string(nonce));
    std::array<uint8_t, 32> digest = sha.digest();
    std::string hash = SHA256::toString(digest);
    if (isHashValid(hash)) {
        PoWResponse* resp = new PoWResponse();
        resp->setData(data.c_str());
        resp->setHash(hash.c_str());
        resp->setNonce(nonce);
        send(resp, "outToAppl");
        startNextPoW();
    } else {
        nonce=intuniform(0,INT32_MAX);
//      continueSignal = new cMessage("continue");
        if (continueSignal->isScheduled()) {
            cancelEvent(continueSignal);
        }
        scheduleAt(simTime() + par("PoWInterval").doubleValue(), continueSignal);
    }
}

bool PoWModule::isHashValid(const std::string& hash)
{
    // Get the PoW difficulty from the model parameter
    int difficulty = par("PoWDifficulty").intValue();
    // Convert the hash to string
    std::string hashString = hash;
    // Create a string of '0's with the length equal to the difficulty
    std::string prefix(difficulty, '0');
    // Check if the first few characters of the hash are '0's
    return hashString.substr(0, difficulty) == prefix;
}

PoWModule::~PoWModule()
{
//    cancelAndDelete(startSignal);
    cancelAndDelete(continueSignal);
}


