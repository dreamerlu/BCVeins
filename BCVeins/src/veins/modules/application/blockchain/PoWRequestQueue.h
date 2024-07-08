/*
 * PoWRequestQueue.h
 *
 *  Created on: 2024.07.07
 *      Author: weilu
 */

#ifndef SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWREQUESTQUEUE_H_
#define SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWREQUESTQUEUE_H_

#include <queue>
#include "PoWRequest_m.h"

using namespace veins;

class PoWRequestQueue {
private:
    std::queue<PoWRequest*> queue;
    int currentBlockSize;

public:
    PoWRequestQueue();
    ~PoWRequestQueue();

    void push(PoWRequest* req);
    PoWRequest* pop();
    PoWRequest* front() const;
    bool empty() const;
    size_t size() const;
    int getCurrentBlockSize() const;
    void clear();
};



#endif /* SRC_VEINS_MODULES_APPLICATION_BLOCKCHAIN_POWREQUESTQUEUE_H_ */
