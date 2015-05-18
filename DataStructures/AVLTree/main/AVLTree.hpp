#pragma once
// Current Project
#include "AVLTreeNode.hpp"
// STL
#include <initializer_list>
#include <utility>
#include <string>

template <typename T>
class AVLTree {
public:
    AVLTree();
    AVLTree(const std::initializer_list<T> &data);
    
    static int balanceFactor(const AVLTreeNode<T> *node) {
        return (AVLTree<T>::height(node->lchild) - AVLTree<T>::height(node->rchild));
    }
    
    static int height(const AVLTreeNode<T> *node) {
        return (node == nullptr) ? 0 : node->height;
    }
    
    static void recalcHeight(AVLTreeNode<T> *node);
    
    static void setParent(AVLTreeNode<T> *node, AVLTreeNode<T> *parent);
    
    static void replaceChildOfItsParent(AVLTreeNode<T> *child, AVLTreeNode<T> *replace);
    
    void insert(const T &data);
    
    void erase(AVLTreeNode<T> *node);
    
    const AVLTreeNode<T> *find(const T &data) const;
    AVLTreeNode<T> *find(const T &data);
    
    template <typename UnaryFunc>
    void preorder(UnaryFunc unary) const;
    
    std::string str() const;
private:
    void balance(AVLTreeNode<T> *level1, AVLTreeNode<T> *level2, AVLTreeNode<T> *level3);

    AVLTreeNode<T> *tryInsert(AVLTreeNode<T> *node, const T &data);
    
    // return the erased node's parent
    AVLTreeNode<T> *tryEraseReturnParent(AVLTreeNode<T> *node);
    
    static void unlink(AVLTreeNode<T> *node);
    
    static void replaceWith_erase(AVLTreeNode<T> *node, AVLTreeNode<T> *replace);

    const AVLTreeNode<T> *find_impl(const AVLTreeNode<T> *node, const T &data) const;
    
    template <typename UnaryFunc>
    void preorder_impl(const AVLTreeNode<T> *node, UnaryFunc unary) const;
    
    std::string str_impl(AVLTreeNode<T> *node) const;
private:
    AVLTreeNode<T> *m_root;
};

namespace std {
    template <typename T>
    std::string to_string(const AVLTree<T> &tree);
}

#include "AVLTree.tcc"
