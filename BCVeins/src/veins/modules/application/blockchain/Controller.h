/*
 * Controller.h
 *
 *  Created on: 2023��11��1��
 *      Author: Administrator
 */

#ifndef SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_CONTROLLER_H_
#define SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_CONTROLLER_H_

#include <omnetpp.h>
#include <veins/base/modules/BaseModule.h>
#include "PoWResult_m.h"
#include "PoWPackingPermission_m.h"
#include "veins/base/modules/BroadcastMessage_m.h"

using namespace omnetpp;
using namespace veins;

class Controller : public BaseModule
{
protected:
    // Add a member variable to record the hashes of the processed data
    std::unordered_set<std::string> processedHashes;
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
};


#endif /* SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_CONTROLLER_H_ */
