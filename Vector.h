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

    // ����
    void expand() {
        // ��δ��Աʱ����������
        if (_size < _capacity) {
            return;
        }

        // ���Ƶ�ǰ���������ܵ�����С����
        if (_capacity < DEFAULT_CAPACITY) {
            _capacity = DEFAULT_CAPACITY;
        }

        // ������������ָ��
        ELEMTYPE *oldElem = _elem;

        // �����ϵͳ������������֮ǰ���ڴ�ռ�
        // cout << "[expand() info]: ori. capacity " << _capacity << "_elem = " << _elem << endl;
        _capacity += _capacity; // �����ӱ�
        _elem = new ELEMTYPE[_capacity]; // ����ռ�
        // cout << "Curr. capacity " << _capacity << "_elem = " << _elem << endl;

        // ����ԭ��������
        for (int iElem = 0; iElem < _size; iElem++) {
            // FIXME: ���_elem�Ƿ�ԭʼ���ͣ���"="�������أ�ʵ��ֵ�ĸ���
            _elem[iElem] = oldElem[iElem];
        }

        // �ͷ�ԭ�ռ�
        delete[] oldElem;


    }

    // ����Ԫ�ص�λ�ã��±꣩
    int insert(int index, ELEMTYPE const &elem) {
        // ���б�Ҫ������
        expand();

        // �Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
        for (int iElem = _size; iElem > index; iElem--) {
            _elem[iElem] = _elem[iElem - 1];
        }

        // ������Ԫ�ز���������
        _elem[index] = elem;
        _size++;

        // ������
        return index;
    }

    int append(ELEMTYPE const &elem) {
        return insert(size(), elem);
    }

    // ɾ��Ԫ��
    ELEMTYPE remove(int index) {
        ELEMTYPE Record2Del = _elem[index];

        for (int iElem = index; iElem < this->_size - 1; iElem++) {
            _elem[iElem] = _elem[iElem + 1];
        }

        this->_size--;

        // cout << "addr of Record2Del: " << &Record2Del << endl;
        return Record2Del;
    }

    // ����
    void traverse(void(*visit)(ELEMTYPE &record)) {
        for (int iElem = 0; iElem < _size; iElem++) {
            visit(_elem[iElem]);
        }
    }

    // ð������
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
