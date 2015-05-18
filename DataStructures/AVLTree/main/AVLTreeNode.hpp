#pragma once

template <typename T>
struct AVLTreeNode {
    T data;
    int height;
    struct AVLTreeNode<T> *lchild;
    struct AVLTreeNode<T> *rchild;
    struct AVLTreeNode<T> *parent;
};
