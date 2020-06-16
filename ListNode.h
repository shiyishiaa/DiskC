#pragma once

typedef int Rank;    // 秩

#define Posi(ElemType) ListNode<ElemType>*    // 列表节点位置（指针）

template<typename ElemType>
class ListNode {
public:
    ElemType _data;                 // 数据
    Posi(ElemType)_pred;         // 前驱
    Posi(ElemType)_succ;        // 后继

    // Constructor
    ListNode() = default;    // 针对header和tailer的构造

    explicit ListNode(ElemType elem, Posi(ElemType)pred = nullptr, Posi(ElemType)succ = nullptr) :
            _data(elem), _pred(pred), _succ(succ) {}

    // 紧靠当前节点之前插入新节点
    Posi(ElemType)insertAsPred(ElemType const &elem);

    // 紧靠当前节点之后插入新节点
    Posi(ElemType)insertAsSucc(ElemType const &elem);
};


// 紧靠当前节点之前插入新节点 @ P.73
template<typename ElemType>
Posi(ElemType)ListNode<ElemType>::insertAsPred(ElemType const &elem) {
    Posi(ElemType)curr = new ListNode(elem, _pred, this);
    _pred->_succ = curr;
    _pred = curr;
    return curr;
}

// 紧靠当前节点之后插入新节点 @ P.74
template<typename ElemType>
Posi(ElemType)ListNode<ElemType>::insertAsSucc(ElemType const &elem) {
    Posi(ElemType)curr = new ListNode(elem, this, _succ);
    _succ->_pred = curr;
    _succ = curr;
    return curr;
}
