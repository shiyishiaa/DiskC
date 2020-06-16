#pragma once

#define DEFAULT_CAPACITY 3
typedef int Rank;

template<typename ELEMTYPE>
struct Vector {
    ELEMTYPE *_elem;
    int _size;
    int _capacity;

    ELEMTYPE &operator[](int index) const {
        return _elem[index];
    }

    explicit Vector(int capacity = DEFAULT_CAPACITY, int size = 0) {
        _capacity = capacity;
        _elem = new ELEMTYPE[_capacity];  // also _elem = malloc(sizeof(TYPE) * capacity);
        _size = size;

        for (int iElem = 0; iElem < _capacity; iElem++) {
            _elem[iElem] = 0;
        }
    }

    // 扩容
    void expand() {
        // 尚未满员时，不必扩容
        if (_size < _capacity) {
            return;
        }

        // 限制当前的容量不能低于最小容量
        if (_capacity < DEFAULT_CAPACITY) {
            _capacity = DEFAULT_CAPACITY;
        }

        // 备份数据区的指针
        ELEMTYPE *oldElem = _elem;

        // 向操作系统申请新两倍于之前的内存空间
        // cout << "[expand() info]: ori. capacity " << _capacity << "_elem = " << _elem << endl;
        _capacity += _capacity; // 容量加倍
        _elem = new ELEMTYPE[_capacity]; // 申请空间
        // cout << "Curr. capacity " << _capacity << "_elem = " << _elem << endl;

        // 复制原向量内容
        for (int iElem = 0; iElem < _size; iElem++) {
            // FIXME: 如果_elem是非原始类型，则"="必须重载，实现值的复制
            _elem[iElem] = oldElem[iElem];
        }

        // 释放原空间
        delete[] oldElem;


    }

    // 返回元素的位置（下标）
    int insert(int index, ELEMTYPE const &elem) {
        // 若有必要，扩容
        expand();

        // 自后向前，后继元素顺次后移一个单元
        for (int iElem = _size; iElem > index; iElem--) {
            _elem[iElem] = _elem[iElem - 1];
        }

        // 置入新元素并更新容量
        _elem[index] = elem;
        _size++;

        // 返回秩
        return index;
    }

    int append(ELEMTYPE const &elem) {
        return insert(size(), elem);
    }

    // 删除元素
    ELEMTYPE remove(int index) {
        ELEMTYPE Record2Del = _elem[index];

        for (int iElem = index; iElem < this->_size - 1; iElem++) {
            _elem[iElem] = _elem[iElem + 1];
        }

        this->_size--;

        // cout << "addr of Record2Del: " << &Record2Del << endl;
        return Record2Del;
    }

    // 遍历
    void traverse(void(*visit)(ELEMTYPE &record)) {
        for (int iElem = 0; iElem < _size; iElem++) {
            visit(_elem[iElem]);
        }
    }

    // 冒泡排序
    void sort(bool Ascent) {
        /*
            Ascent: to sort in ascent order if true, desent if false
        */
        bool sorted = true;
        if (Ascent) {
            for (int IndexMax = _size; IndexMax > 0; IndexMax--) {
                for (int iElem = 0; iElem <= IndexMax - 1; iElem++) {
                    if (_elem[iElem] > _elem[iElem + 1]) {
                        sorted = false;
                        swap(_elem[iElem], _elem[iElem + 1]);
                    }
                }
                if (sorted) {
                    return;
                }
            }
        }

        if (!Ascent) {
            for (int IndexMax = _size; IndexMax > 0; IndexMax--) {
                for (int iElem = 0; iElem <= IndexMax - 1; iElem++) {
                    if (_elem[iElem] < _elem[iElem + 1]) {
                        sorted = false;
                        swap(_elem[iElem], _elem[iElem + 1]);
                    }
                }
                if (sorted) {
                    return;
                }
            }
        }
    }

    Rank size() {
        return _size;
    }

};
