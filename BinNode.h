#pragma once

#include "Vector.h"
#include "Queue.h"

// ���ں��������ɫ����
typedef enum RBColor {
    RB_RED, RB_BLACK
};

#define BinNodePosi(ElemType) BinNode<ElemType>*

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

// ���Ըýڵ�Ϊ�������ĸ߶�
#define stature(p) (p ? (p)->height : -1)

// ���Ը��׵����ã������֪���ǵ�ǰ�ڵ������ӻ����Һ��ӵ����⣩
#define FromParentTo(x) (IsRoot(x) ? _root: (IsLChild(x) ? (x).parent->lc : (x).parent->rc) )

template<typename ElemType>
struct BinNode {
    ElemType data;
    BinNodePosi(ElemType)parent;
    BinNodePosi(ElemType)lc;
    BinNodePosi(ElemType)rc;

    int height;
    int npl;
    RBColor color;

    BinNode() {
        parent = NULL;
        lc = NULL;
        rc = NULL;
        height = 0;
        npl = 1;
        color = RBColor::RB_RED;
    }

    explicit BinNode(ElemType elem, BinNodePosi(ElemType)parent = NULL, BinNodePosi(ElemType)lc = NULL, \
        BinNodePosi(ElemType)rc = NULL, int h = 0, int l = 1, RBColor c = RBColor::RB_RED) {
        data = elem;
        this->parent = parent;
        this->lc = lc;
        this->rc = rc;
        height = h;
        npl = l;
        color = c;
    }

    // �Ե�ǰ�ڵ�Ϊ���Ķ������Ĺ�ģ
    int size() {
        int s = 1; //���뱾��
        if (lc) s += lc->size(); //�ݹ������������ģ
        if (rc) s += rc->size(); //�ݹ������������ģ
        return s;
    }


    // ��elem��Ϊ��ǰ�ڵ�����Ӳ��뵽������
    BinNodePosi(ElemType)insertAsLC(ElemType const &elem) {
        /*
        Step 1. �����½ڵ�
        Step 2. �ѵ�ǰ�ڵ���Ϊ�Ľ��ĸ���
        Step 3. ���½ڵ���Ϊ��ǰ�ڵ������
        */
        lc = new BinNode(elem, this);
        return lc;
    }

    // ��elem��Ϊ��ǰ�ڵ���Һ��Ӳ��뵽������
    BinNodePosi(ElemType)insertAsRC(ElemType const &elem) {
        rc = new BinNode(elem, this);
        return rc;
    }

    // ��α���
    template<typename VST>
    void travLevel(VST &visit) {
        Queue<BinNodePosi(ElemType)> queue;
        queue.enqueue(this);    // �����ڵ����
        while (!queue.isEmpty()) {
            BinNodePosi(ElemType)x = queue.dequeue();
            visit(x->data);
            if (x->lc) {
                queue.enqueue(x->lc);
            }
            if (x->rc) {
                queue.enqueue(x->rc);
            }
        }
    }

    // �������
    template<typename VST>
    void travPre(VST &visit) {
        travPre_R(this, visit);
    }

    template<typename VST>
    void travPre_R(BinNodePosi(ElemType)x, VST &visit) {
        if (!x) {
            return;
        }
        visit(x->data);
        travPre_R(x->lc, visit);
        travPre_R(x->rc, visit);
    }

    // �������
    template<typename VST>
    void travIn(VST &visit) {
        travIn_R(this, visit);
    }

    template<typename VST>
    void travIn_R(BinNodePosi(ElemType)x, VST &visit) {
        if (!x) {
            return;
        }

        travIn_R(x->lc, visit);
        visit(x->data);
        travIn_R(x->rc, visit);
    }

    // �������
    template<typename VST>
    void travPost(VST &visit) {
        travPost_R(this, visit);
    }

    template<typename VST>
    void travPost_R(BinNodePosi(ElemType)x, VST &visit) {
        if (!x) {
            return;
        }

        travPost_R(x->lc, visit);
        travPost_R(x->rc, visit);
        visit(x->data);
    }
};