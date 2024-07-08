/*
 * PoWModule.h
 *
 *  Created on: 2023��11��1��
 *      Author: Administrator
 */

#ifndef SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWMODULE_H_
#define SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWMODULE_H_

#include <omnetpp.h>
#include "PoWRequest_m.h"
#include "PoWResponse_m.h"
#include "Block_m.h"
#include "PoWRequestQueue.h"
#include <vector>
#include <fstream>
#include "SHA256.h"
#include "PoWPackingPermission_m.h"

using namespace omnetpp;
using namespace veins;

class PoWModule : public cSimpleModule
{
  private:
    std::string data;
    uint64_t nonce;
    cMessage * startSignal;
    cMessage * continueSignal;
    uint16_t maxBytesPerBlock;
    bool isProcessing;
    uint16_t currentBlockSize;
    // Queue for PoW requests
    PoWRequestQueue requestQueue;
    //Vector for storing the chain of all blocks
    std::vector<Block *> blockchain;
    uint16_t realBlockByteSize;

  public:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual ~PoWModule() override;

    void startPoW();
    void startNextPoW();
    bool isHashValid(const std::string& hash);
};




#endif /* SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWMODULE_H_ */
