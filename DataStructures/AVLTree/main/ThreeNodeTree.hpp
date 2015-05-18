#pragma once
// Current Project
#include "AVLTreeNode.hpp"
// C-Standard
#include <cassert>

enum class ThreeNodeTreeTag : int {
    Balanced,
    LeftRightTag,
    LeftLeftTag,
    RightLeftTag,
    RightRightTag
};

template <typename T>
class ThreeNodeTree {
private:
    AVLTreeNode<T> *m_level1Node;
    AVLTreeNode<T> *m_level2Node;
    AVLTreeNode<T> *m_level3Node;
    AVLTreeNode<T> *m_root;
    ThreeNodeTreeTag m_tag;
public:
    ThreeNodeTree(AVLTreeNode<T> *level1, AVLTreeNode<T> *level2, AVLTreeNode<T> *level3,
                  ThreeNodeTreeTag tag) :
        m_level1Node(level1),
        m_level2Node(level2),
        m_level3Node(level3),
        m_root(nullptr),
        m_tag(tag)
    {
        assert(m_tag != ThreeNodeTreeTag::Balanced && "ThreeNodeTree must not constructed to be balanced!");
        
        auto level1bf = AVLTree<T>::balanceFactor(m_level1Node);
        auto level2bf = AVLTree<T>::balanceFactor(m_level2Node);
        if (m_tag == ThreeNodeTreeTag::LeftRightTag) {
            assert(level1bf == 2 &&
                   level2bf == -1 &&
                   "ThreeNodeTreeTag badly constructed!");
        } else if (m_tag == ThreeNodeTreeTag::LeftLeftTag) {
            assert(level1bf == 2 &&
                   (level2bf == 1 || level2bf == 0) &&
                   "ThreeNodeTreeTag badly constructed!");
        } else if (m_tag == ThreeNodeTreeTag::RightLeftTag) {
            assert(level1bf == -2 &&
                   level2bf == 1 &&
                   "ThreeNodeTreeTag badly constructed!");
        } else if (m_tag == ThreeNodeTreeTag::RightRightTag) {
            assert(level1bf == -2 &&
                   (level2bf == -1 || level2bf == 0) &&
                   "ThreeNodeTreeTag badly constructed!");
        }
    }
    
    ~ThreeNodeTree() {}
    
    void balance() {
        if (m_tag == ThreeNodeTreeTag::LeftLeftTag) {
            this->leftLeftBalance();
        } else if (m_tag == ThreeNodeTreeTag::LeftRightTag) {
            this->leftRightBalance();
        } else if (m_tag == ThreeNodeTreeTag::RightLeftTag) {
            this->rightLeftBalance();
        } else {
            this->rightRightBalance();
        }
        m_tag = ThreeNodeTreeTag::Balanced;
    }
    
    AVLTreeNode<T> *balancedRoot() {
        if (m_tag != ThreeNodeTreeTag::Balanced)
            this->balance();
        return m_root;
    }
private:
    void leftRightBalance() {
        AVLTreeNode<T> *a = m_level2Node->lchild;
        AVLTreeNode<T> *b = m_level3Node->lchild;
        AVLTreeNode<T> *c = m_level3Node->rchild;
        AVLTreeNode<T> *d = m_level1Node->rchild;
        
        m_root = m_level3Node;
        m_root->lchild = m_level2Node; AVLTree<T>::setParent(m_level2Node, m_root);
        m_root->rchild = m_level1Node; AVLTree<T>::setParent(m_level1Node, m_root);
        AVLTree<T>::setParent(m_root, nullptr);
        
        AVLTreeNode<T> *left = m_root->lchild;
        left->lchild = a; AVLTree<T>::setParent(a, left);
        left->rchild = b; AVLTree<T>::setParent(b, left);
        AVLTree<T>::setParent(left, m_root);
        
        AVLTreeNode<T> *right = m_root->rchild;
        right->lchild = c; AVLTree<T>::setParent(c, right);
        right->rchild = d; AVLTree<T>::setParent(d, right);
        AVLTree<T>::setParent(right, m_root);
        
        // update height
        AVLTree<T>::recalcHeight(left);
        AVLTree<T>::recalcHeight(right);
        AVLTree<T>::recalcHeight(m_root);
    }
    
    void leftLeftBalance() {
        AVLTreeNode<T> *a = m_level3Node->lchild;
        AVLTreeNode<T> *b = m_level3Node->rchild;
        AVLTreeNode<T> *c = m_level2Node->rchild;
        AVLTreeNode<T> *d = m_level1Node->rchild;
        
        m_root = m_level2Node;
        m_root->lchild = m_level3Node; AVLTree<T>::setParent(m_level3Node, m_root);
        m_root->rchild = m_level1Node; AVLTree<T>::setParent(m_level1Node, m_root);
        AVLTree<T>::setParent(m_root, nullptr);
        
        AVLTreeNode<T> *left = m_root->lchild;
        left->lchild = a; AVLTree<T>::setParent(a, left);
        left->rchild = b; AVLTree<T>::setParent(b, left);
        AVLTree<T>::setParent(left, m_root);
        
        AVLTreeNode<T> *right = m_root->rchild;
        right->lchild = c; AVLTree<T>::setParent(c, right);
        right->rchild = d; AVLTree<T>::setParent(d, right);
        AVLTree<T>::setParent(right, m_root);
        
        // update height
        AVLTree<T>::recalcHeight(left);
        AVLTree<T>::recalcHeight(right);
        AVLTree<T>::recalcHeight(m_root);
    }
    
    void rightLeftBalance() {
        AVLTreeNode<T> *a = m_level1Node->lchild;
        AVLTreeNode<T> *b = m_level3Node->lchild;
        AVLTreeNode<T> *c = m_level3Node->rchild;
        AVLTreeNode<T> *d = m_level2Node->rchild;
        
        m_root = m_level3Node;
        m_root->lchild = m_level1Node; AVLTree<T>::setParent(m_level1Node, m_root);
        m_root->rchild = m_level2Node; AVLTree<T>::setParent(m_level2Node, m_root);
        AVLTree<T>::setParent(m_root, nullptr);
        
        AVLTreeNode<T> *left = m_root->lchild;
        left->lchild = a; AVLTree<T>::setParent(a, left);
        left->rchild = b; AVLTree<T>::setParent(b, left);
        AVLTree<T>::setParent(left, m_root);
        
        AVLTreeNode<T> *right = m_root->rchild;
        right->lchild = c; AVLTree<T>::setParent(c, right);
        right->rchild = d; AVLTree<T>::setParent(d, right);
        AVLTree<T>::setParent(right, m_root);
        
        // update height
        AVLTree<T>::recalcHeight(left);
        AVLTree<T>::recalcHeight(right);
        AVLTree<T>::recalcHeight(m_root);
    }
    
    void rightRightBalance() {
        AVLTreeNode<T> *a = m_level1Node->lchild;
        AVLTreeNode<T> *b = m_level2Node->lchild;
        AVLTreeNode<T> *c = m_level3Node->lchild;
        AVLTreeNode<T> *d = m_level3Node->rchild;
        
        m_root = m_level2Node;
        m_root->lchild = m_level1Node; AVLTree<T>::setParent(m_level1Node, m_root);
        m_root->rchild = m_level3Node; AVLTree<T>::setParent(m_level3Node, m_root);
        AVLTree<T>::setParent(m_root, nullptr);
        
        AVLTreeNode<T> *left = m_root->lchild;
        left->lchild = a; AVLTree<T>::setParent(a, left);
        left->rchild = b; AVLTree<T>::setParent(b, left);
        AVLTree<T>::setParent(left, m_root);
        
        AVLTreeNode<T> *right = m_root->rchild;
        right->lchild = c; AVLTree<T>::setParent(c, right);
        right->rchild = d; AVLTree<T>::setParent(d, right);
        AVLTree<T>::setParent(right, m_root);
        
        // update height
        AVLTree<T>::recalcHeight(left);
        AVLTree<T>::recalcHeight(right);
        AVLTree<T>::recalcHeight(m_root);
    }
};
