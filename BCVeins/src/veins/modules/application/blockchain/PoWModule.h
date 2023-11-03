/*
 * PoWModule.h
 *
 *  Created on: 2023Äê11ÔÂ1ÈÕ
 *      Author: Administrator
 */

#ifndef SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWMODULE_H_
#define SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWMODULE_H_

#include <omnetpp.h>
#include "PoWRequest_m.h"
#include "PoWResponse_m.h"

using namespace omnetpp;

class PoWModule : public cSimpleModule
{
  private:
    std::string data;
    uint64_t nonce;
    cMessage * startSignal;
    cMessage * continueSignal;

  public:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual ~PoWModule() override;

    void startPoW();
    bool isHashValid(const std::string& hash);
};




#endif /* SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWMODULE_H_ */
