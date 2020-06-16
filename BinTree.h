#pragma once

#include "BinNode.h"

template<typename ElemType>
class BinTree {
protected:
    int _size;
    BinNodePosi(ElemType)_root;

    virtual int updateHeight(BinNodePosi(ElemType)x) {
        x->height = 1 + (stature(x->lc) > stature(x->rc) ? stature(x->lc) : stature(x->rc));
        return x->height;
    }

    void updateHeightAbove(BinNodePosi(ElemType)x) {
        while (x) {
            updateHeight(x);
            x = x->parent;
        }
    }

public:
    BinTree() {
        _size = 0;
        _root = NULL;
    }

    //使用已经存在的节点创造一棵树
    explicit BinTree(BinNodePosi(ElemType)node) {
        _size = node->size();
        _root = node;
    }

    //int remove(BinNodePosi(ElemType) x)
    //{
    //	FromParentTo(*x) = NULL; // �ж����Ը��ڵ��ָ��
    //	updateHeightAbove(x->parent); // �������ȸ߶�
    //	int n = removeAt(x);
    //	_size = _size - n;
    //	return n;
    //}

    ~BinTree();
//    {
    //if (_size > 0)
    //{
    //	remove(_root);
    //}
//    }

    int size() const {
        return _size;
    }

    bool isEmpty() const {
        return !_root;
    }

    BinNodePosi(ElemType)root() const {
        return _root;
    }

    BinNodePosi(ElemType)insertAsRoot(ElemType const &elem) {
        _size = 1;
        _root = new BinNode<ElemType>(elem);
        return _root;
    }

    BinNodePosi(ElemType)insertAsLC(BinNodePosi(ElemType)x, ElemType const &elem) // elem��Ϊx�����Ӳ���
    {
        _size++;
        x->insertAsLC(elem);
        //updateHeightAbove(x);
        return x->lc;
    }

    BinNodePosi(ElemType)insertAsRC(BinNodePosi(ElemType)x, ElemType const &elem) // elem��Ϊx���Һ��Ӳ���
    {
        _size++;
        x->insertAsRC(elem);
        //updateHeightAbove(x);
        return x->rc;
    }

    BinNodePosi(ElemType)attachAsLC(BinNodePosi(ElemType)x, BinTree<ElemType> *&tree) // T��Ϊx������������
    {
        x->lc = tree->root();
        if (x->lc) {
            x->lc->parent = x;
        }
        _size += tree->_size;
        //updateHeightAbove(x);
        tree->_root = NULL;
        tree->_size = 0;
        tree = NULL;
        return x;
    }

    BinNodePosi(ElemType)attachAsRC(BinNodePosi(ElemType)x, BinTree<ElemType> *&tree) // T��Ϊx������������
    {
        x->rc = tree->root();
        if (x->rc) {
            x->rc->parent = x;
        }
        _size += tree->_size;
        //updateHeightAbove(x);
        tree->_root = NULL;
        tree->_size = 0;
        tree = NULL;
        return x;
    }

    BinTree<ElemType> *secede(BinNodePosi(ElemType)x) {

    }

    // ��α���
    template<typename VST>
    void travLevel(VST &visit) {
        if (_root) {
            _root->travLevel(visit);
        }
    }

    // �������
    template<typename VST>
    void travPre(VST &visit) {
        if (_root) {
            _root->travPre(visit);
        }
    }

    // �������
    template<typename VST>
    void travIn(VST &visit) {
        if (_root) {
            _root->travIn(visit);
        }
    }

    template<typename VST>
    void travPost(VST &visit) {
        if (_root) {
            _root->travPost(visit);
        }
    }

    bool operator==(BinTree<ElemType> const &tree) {
        return _root && tree._root && (_root == tree._root);
    }


    static BinNode<ElemType> *build(Vector<char> travPrev, Vector<char> travIn) {
        int nNode = travPrev.size();

        if (nNode == 0)
            return NULL;

        Vector<char> leftpre, leftmid, rightpre, rightmid;

        auto *root = new BinNode<char>(travPrev[0]);   //�����
        int rootPos = 0;
        for (int i = 0; i < nNode; i++) {
            if (travIn[i] == travPrev[0]) {
                rootPos = i;
                break;
            }
        }
        for (int i = 0; i < nNode; i++) {
            if (i < rootPos) {
                leftmid.insert(leftmid.size(), travIn[i]);
                leftpre.insert(leftpre.size(), travPrev[i + 1]);
            } else if (i > rootPos) {
                rightmid.insert(rightmid.size(), travIn[i]);
                rightpre.insert(rightpre.size(), travPrev[i]);
            }
        }
        root->lc = build(leftpre, leftmid);
        root->rc = build(rightpre, rightmid);
        root->height = 1 + (stature(root->lc) > stature(root->rc) ? stature(root->lc) : stature(root->rc));
        return root;
    }

    static BinTree<ElemType> *buildT(Vector<char> travPrev, Vector<char> travIn) {
        auto *tree = new BinTree<ElemType>();
        tree->_root = build(travPrev, travIn);
        tree->_root->parent = NULL;
        tree->_size = tree->_root->size();

        return tree;
    }
};

template<typename ElemType>
BinTree<ElemType>::~BinTree() = default;
