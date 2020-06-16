#pragma once

typedef int Rank;    // ��

#define Posi(ElemType) ListNode<ElemType>*    // �б�ڵ�λ�ã�ָ�룩

template<typename ElemType>
class ListNode {
public:
    ElemType _data;                 // ����
    Posi(ElemType)_pred;         // ǰ��
    Posi(ElemType)_succ;        // ���

    // Constructor
    ListNode() = default;    // ���header��tailer�Ĺ���

    explicit ListNode(ElemType elem, Posi(ElemType)pred = nullptr, Posi(ElemType)succ = nullptr) :
            _data(elem), _pred(pred), _succ(succ) {}

    // ������ǰ�ڵ�֮ǰ�����½ڵ�
    Posi(ElemType)insertAsPred(ElemType const &elem);

    // ������ǰ�ڵ�֮������½ڵ�
    Posi(ElemType)insertAsSucc(ElemType const &elem);
};


// ������ǰ�ڵ�֮ǰ�����½ڵ� @ P.73
template<typename ElemType>
Posi(ElemType)ListNode<ElemType>::insertAsPred(ElemType const &elem) {
    Posi(ElemType)curr = new ListNode(elem, _pred, this);
    _pred->_succ = curr;
    _pred = curr;
    return curr;
}

// ������ǰ�ڵ�֮������½ڵ� @ P.74
template<typename ElemType>
Posi(ElemType)ListNode<ElemType>::insertAsSucc(ElemType const &elem) {
    Posi(ElemType)curr = new ListNode(elem, this, _succ);
    _succ->_pred = curr;
    _succ = curr;
    return curr;
}
