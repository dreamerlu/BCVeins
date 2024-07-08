/*
 * PoWRequestQueue.cc
 *
 *  Created on: 2024.07.07
 *      Author: weilu
 */

#include "PoWRequestQueue.h"

PoWRequestQueue::PoWRequestQueue() : currentBlockSize(0) {

}

PoWRequestQueue::~PoWRequestQueue() {
    clear();
}

void PoWRequestQueue::push(PoWRequest* req) {
    queue.push(req);
    currentBlockSize += req->getByteLength(); // 更新currentBlockSize
}

PoWRequest* PoWRequestQueue::pop() {
    if (queue.empty()) {
        return nullptr;
    }
    PoWRequest* req = queue.front();
    queue.pop();
    currentBlockSize -= req->getByteLength(); // 更新currentBlockSize
    return req;
}

PoWRequest* PoWRequestQueue::front() const {
    if (queue.empty()) {
        return nullptr;
    }
    return queue.front();
}

bool PoWRequestQueue::empty() const {
    return queue.empty();
}

size_t PoWRequestQueue::size() const {
    return queue.size();
}

int PoWRequestQueue::getCurrentBlockSize() const {
    return currentBlockSize;
}

void PoWRequestQueue::clear() {
    while (!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
    currentBlockSize = 0;
}
