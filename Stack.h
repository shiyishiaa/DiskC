#pragma once

#include "Vector.h"

template<typename ElemType>
class Stack : public Vector<ElemType> {
public:
    void push(ElemType const &elem) {
        this->insert(this->size(), elem);
    }

    ElemType pop() {
        return this->remove(this->size() - 1);
    }

    ElemType &top() {
        return (*this)[this->size() - 1];
    }

    bool empty() {
        return (this->size() == 0);
    }
};