#include "BinTree.h"
#include "Stack.h"
#include <iostream>
#include <io.h>

using namespace std;

static void visitAlongLeftBranch(BinNodePosi(_finddatai64_t)x,
                                 Stack<BinNodePosi(_finddatai64_t)> &S, unsigned long long &sizeFile);

void travPre(BinNodePosi(_finddatai64_t)x, unsigned long long &sizeFile);  //二叉树先序遍历算法（迭代版#2）

void sizeAdd(unsigned long long &sizeFile, unsigned size);

void traverse(string inPath, const string &fileType, BinTree<_finddatai64_t> *ptrTree);

bool fileReadable(const string &folderPath);

//Begin只有一次，该文件为树的根节点
static bool isBegin = true;

int main(int argc, char *argv[]) {
    //目标文件夹路径
    string inPath = "C:\\DRIVERS";
    //树
    static BinTree<_finddatai64_t> fileTree;
    //编辑树用的指针
    static BinTree<_finddatai64_t> *ptrTree = &fileTree;
    //每次使用遍历前，isBegin都重设为True
    isBegin = true;
    traverse(inPath, "*.*", ptrTree);
    unsigned long long sizeFile = 0;
    //sizeSumPre(fileTree.root(), sizeFile);
    travPre(fileTree.root(), sizeFile);
    cout << "Size of \"" << inPath << "\" is: " << sizeFile << endl;
    system("Pause");
    return 0;
}

void sizeAdd(unsigned long long &sizeFile, unsigned size) {
    sizeFile += size;
}

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
static void visitAlongLeftBranch(BinNodePosi(_finddatai64_t)x, Stack<BinNodePosi(_finddatai64_t)> &S,
                                 unsigned long long &sizeFile) {
    while (x) {
        sizeAdd(sizeFile, x->data.size); //访问当前节点
        S.push(x->rc); //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
        x = x->lc;  //沿左分支深入一层
    }
}

void travPre(BinNodePosi(_finddatai64_t)x, unsigned long long &sizeFile) { //二叉树先序遍历算法（迭代版#2）
    Stack<BinNodePosi(_finddatai64_t)> S; //辅助栈
    while (true) {
        visitAlongLeftBranch(x, S, sizeFile); //从当前节点出发，逐批访问
        if (S.empty()) break; //直到栈空
        x = S.pop(); //弹出下一批的起点
    }
}

void traverse(string inPath, const string &fileType, BinTree<_finddatai64_t> *ptrTree) {
    //路径搭建
    string folderName = std::move(inPath);
    folderName.append("\\");
    string temp = folderName + fileType;
    //用于查找的句柄
    intptr_t handle;
    _finddatai64_t fileInfo{};
    //第一次查找
    bool isFirst = false;
    handle = _findfirsti64(temp.c_str(), &fileInfo);
    do {
        //跳过开头的.和..，并且下一个文件必定是左孩子
        if (strcmp(fileInfo.name, ".") == 0 || strcmp(fileInfo.name, "..") == 0) {
            isFirst = true;
            continue;
        }
            //是不可读取的文件夹
        else if (!fileReadable(temp)) {
            if (isBegin) {
                isBegin = false;
                ptrTree->insertAsRoot(fileInfo);
            } else if (isFirst) {
                ptrTree->insertAsLC(ptrTree->root(), fileInfo);
                new BinTree<_finddatai64_t>(ptrTree->root()->lc);
            } else {
                ptrTree->insertAsRC(ptrTree->root(), fileInfo);
                new BinTree<_finddatai64_t>(ptrTree->root()->rc);
            }
            return;
        }
            //是可读取文件夹
        else if (fileInfo.attrib & _A_SUBDIR) {
            //cout << "<dir>     " << folderName << fileInfo.name << endl;
            if (isBegin) {
                isBegin = false;
                isFirst = false;
                ptrTree->insertAsRoot(fileInfo);
            } else if (isFirst) {
                isFirst = false;
                ptrTree->insertAsLC(ptrTree->root(), fileInfo);
                ptrTree = new BinTree<_finddatai64_t>(ptrTree->root()->lc);
            } else {
                ptrTree->insertAsRC(ptrTree->root(), fileInfo);
                ptrTree = new BinTree<_finddatai64_t>(ptrTree->root()->rc);
            }
            //新的文件夹
            string tempPath = folderName + fileInfo.name;
            //递归调用自身
            traverse(tempPath, fileType, ptrTree);
        }
            //是文件
        else {
            //cout << "     " << folderName << fileInfo.name << endl;
            if (isBegin) {
                isBegin = false;
                isFirst = false;
                ptrTree->insertAsRoot(fileInfo);
            } else if (isFirst) {
                isFirst = false;
                ptrTree->insertAsLC(ptrTree->root(), fileInfo);
                ptrTree = new BinTree<_finddatai64_t>(ptrTree->root()->lc);
            } else {
                ptrTree->insertAsRC(ptrTree->root(), fileInfo);
                ptrTree = new BinTree<_finddatai64_t>(ptrTree->root()->rc);
            }
        }
    } while (_findnexti64(handle, &fileInfo) == 0);
    _close(handle);
}

//文件夹是否可读取
bool fileReadable(const string &folderPath) {
    _finddatai64_t testFileInfo{};
    long testHandle = _findfirsti64(folderPath.c_str(), &testFileInfo);
    return testHandle != -1;
}