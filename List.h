#pragma once

#include "ListNode.h" //�����б�ڵ���
#include <iostream>

template<typename ElemType>

class List { //�б�ģ����

private:
    int _size{}; //��ģ��ͷ�ڱ���β�ڱ�
    Posi(ElemType)header;
    Posi(ElemType)trailer; //ͷ�ڱ���β�ڱ�

protected:
    void init() { //�б��ʼ���������б����ʱͳһ����
        header = new ListNode<ElemType>; //����ͷ�ڱ��ڵ�
        trailer = new ListNode<ElemType>; //����β�ڱ��ڵ�
        header->_succ = trailer;
        header->_pred = NULL; //����
        trailer->_pred = header;
        trailer->_succ = NULL; //����

        _size = 0; //��¼��ģ
    }

    int clear() {  //����б�
        int oldSize = _size;
        while (0 < _size) {
            remove(header->_succ); //����ɾ���׽ڵ�
        }
        return oldSize; //ֱ���б���
    }

    ElemType remove(Posi(ElemType)p) {  //O(1)
        ElemType e = p->_data; //���ݴ�ɾ���ڵ���ֵ��������T��ֱ�Ӹ�ֵ��
        p->_pred->_succ = p->_succ;
        p->_succ->_pred = p->_pred;
        delete p;

        _size--;
        return e; //���ر�����ֵ
    }


    Posi(ElemType)first() {
        return header->_succ;
    }

public:
    /* ... ���캯��������������ֻ���ӿڡ���д�ӿڡ������ӿ� */
    List() {
        init();
    }

    ~List() {
        clear();
        delete header;
        delete trailer;
    }

    Rank size() {
        return _size;
    }

    ElemType &operator[](int rank) const {
        Posi(ElemType)curr = first(); // curr short for current
        while (0 < rank--) {
            curr = curr->_succ;
        }
        return curr->_data;
    }

    Posi(ElemType)find(ElemType const &elem) {
        return find(elem, _size, trailer);
    }

    Posi(ElemType)find(ElemType const &elem, int n, Posi(ElemType)p) {
        while (0 < n--) {
            p = p->_pred;
            if (elem == p->_data) {
                return p;
            }
        }

        return nullptr;
    }

    Posi(ElemType)insertBefore(Posi(ElemType)p, ElemType const &e) {
        _size++;
        return p->insertAsPred(e);
    } //e����p��ǰ������

    Posi(ElemType)insert(Rank rank, ElemType elem) {
        Posi(ElemType)p = header->_succ;
        while (0 < rank--) {
            p = p->_succ;
        }
        return insertBefore(p, elem);
    } //e����p��ǰ������

    void traverse(void (*visit)(ElemType &)) { //����ָ��
        Posi(ElemType)p = header;
        while ((p = p->_succ) != trailer) {
            visit(p->_data);
        }
    }

    // ð������
    void sort(bool Ascent) {
        /*
            Ascent: to sort in ascent order if true, desent if false
        */
        bool sorted = true;
        Posi(ElemType)curr;

        if (Ascent) {
            for (int IndexMax = _size; IndexMax > 0; IndexMax--) {
                curr = header->_succ;
                for (int iElem = 0; iElem <= IndexMax - 1; iElem++) {
                    if (curr->_data > curr->_succ->_data) {
                        sorted = false;
                        insertBefore(curr, curr->_succ->_data);
                        remove(curr->_succ);
                    } else {
                        curr = curr->_succ;
                    }
                }
                if (sorted) {
                    return;
                }
            }
        }

        if (!Ascent) {
            for (int IndexMax = _size; IndexMax > 0; IndexMax--) {
                curr = header->_succ;
                for (int iElem = 0; iElem <= IndexMax - 1; iElem++) {
                    if (curr->_data < curr->_succ->_data) {
                        sorted = false;
                        insertBefore(curr, curr->_succ->_data);
                        remove(curr->_succ);
                    } else {
                        curr = curr->_succ;
                    }
                }
                if (sorted) {
                    return;
                }
            }
        }
    }
};
