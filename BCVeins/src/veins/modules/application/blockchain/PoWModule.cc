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
    continueSignal = new cMessage("continue");
}

void PoWModule::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        //For handling the scheduleAt-type PoW calculating request, i.e., mainly for con
        startPoW();
    } else if (PoWPackingPermission * ppp = dynamic_cast<PoWPackingPermission *>(msg)) {
        // Herein the PoWPackingPermission message has received.
        Block *block = new Block();
        block->setTimestamp(ppp->getTimestamp());
        block->setDifficultyLevel(ppp->getDifficultyLevel());
        block->setMiner(std::string("rsu["+std::to_string(ppp->getRsuId())+"]").c_str());
        block->setNonce(ppp->getNonce());
        block->setTransactionData(ppp->getBlockData());
        block->setHash(ppp->getHash());
        if (blockchain.empty()) {
            //This is the genesis block
            block->setPreviousBlockHash(std::string("").c_str());
        } else {
            block->setPreviousBlockHash(blockchain.back()->getHash());
        }
        blockchain.push_back(block);
        EV << "The current blockchain size:"<<blockchain.size()<<std::endl;
        EV << "The current inserted block hash" << block->getHash();
    }
    else if (PoWRequest* req = dynamic_cast<PoWRequest*>(msg)) {
        EV << "receving PoWRequest"<<std::endl;
        requestQueue.push(req);
        if (!isProcessing) {
            startNextPoW();
        }
    }
}

//startNextPow() and startPow() will call each other, which is actually the recursion idea.
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
    std::string hash = SHA256::HexToBinary(SHA256::toString(digest));
    if (isHashValid(hash)) {
        PoWResponse* resp = new PoWResponse();
        resp->setData(data.c_str());
        resp->setHash(hash.c_str());
        resp->setNonce(nonce);
        resp->setTimestamp(simTime());
        resp->setDifficultyLevel(par("PoWDifficulty").intValue());
        send(resp, "outToAppl");
        startNextPoW();
    } else {
        nonce=intuniform(0,INT32_MAX);
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
    cancelAndDelete(continueSignal);
    // print my interest of info
    try {
        std::string filePath = "./results/blockchain"+std::to_string(this->getParentModule()->getIndex())+".log";
        std::ofstream file(filePath);
        for (int i=0; i<blockchain.size();i++) {
            file << "Block: " << i << '\n';
            file << "Data: " << blockchain[i]->getTransactionData() << '\n';
            file << "Nonce: " << blockchain[i]->getNonce() << '\n';
            file << "Previous Hash: " << blockchain[i]->getPreviousBlockHash() << '\n';
            file << "Current Hash: " << blockchain[i]->getHash()<< '\n';
            file << "Miner: " << blockchain[i]->getMiner() << '\n';
            file << '\n';
        }
        file.close();
    } catch (const std::exception& e) {
        // 输出错误信息并安全地结束程序
        std::cerr << "Error writing blockchain to file: " << e.what() << std::endl;
    }
}


