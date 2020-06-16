#pragma once

#include "List.h"

template<typename ElemType>
class Queue : public List<ElemType> {
public:
    void enqueue(ElemType const &elem) {
        this->insertAsLast(elem);
    }

    ElemType dequeue() {
        return this->remove(this->first());
    }

    ElemType &front() {
        return this->first()->_data;
    }
};