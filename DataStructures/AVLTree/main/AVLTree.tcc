#pragma once

#include "AVLTree.hpp"
// Current Project
#include "ThreeNodeTree.hpp"
// STL
#include <functional>
#include <stdexcept>
#include <string>

template <typename T>
AVLTree<T>::AVLTree() :
    m_root(nullptr)
{}

template <typename T>
AVLTree<T>::AVLTree(const std::initializer_list<T> &data) :
    m_root(nullptr)
{
    for (const auto &item : data)
        this->insert(item);
}

template <typename T>
void AVLTree<T>::insert(const T &data) {
    // insert at root
    if (m_root == nullptr) {
        m_root = new AVLTreeNode<T>({data, 0, nullptr, nullptr, nullptr});
        return;
    }
    
    if (this->find(data) != nullptr) {
        std::string errMessage = "AVLTree: data '" + std::to_string(data) + "' is duplicated!";
        throw std::runtime_error(errMessage);
    }

    auto newnode = this->tryInsert(m_root, data);
    
    // search for the unbalanced node
    AVLTreeNode<T> *level1 = (newnode->parent == nullptr) ? nullptr : (newnode->parent->parent);
    AVLTreeNode<T> *level2 = newnode->parent;
    AVLTreeNode<T> *level3 = newnode;
    while (level1 != nullptr) {
        int bf = AVLTree::balanceFactor(level1);
        assert(bf >= -2 && bf <= 2 && "balanced factor error!");
        if (bf == -2 || bf == 2)
            break;
        
        level3 = level2;
        level2 = level1;
        level1 = level1->parent;
    }
    
    // no unbalanced node, return
    if (level1 == nullptr)
        return;
        
    this->balance(level1, level2, level3);
}

template <typename T>
void AVLTree<T>::erase(AVLTreeNode<T> *node) {
    // nothing to erase, return
    if (node == nullptr)
        return;
    
    auto nodeParent = this->tryEraseReturnParent(node);
    
    // search for the unbalanced node
    AVLTreeNode<T> *level1 = nodeParent;
    int level1BF = 0;
    while (level1 != nullptr) {
        this->recalcHeight(level1);
        level1BF = AVLTree<T>::balanceFactor(level1);
        assert(level1BF >= -2 && level1BF <= 2 && "balanced factor error!");
        if (level1BF == -2 || level1BF == 2)
            break;
        
        level1 = level1->parent;
    }
    
    // no unbalanced node, return
    if (level1 == nullptr)
        return;
    
    AVLTreeNode<T> *level2 = nullptr;
    AVLTreeNode<T> *level3 = nullptr;
    if (level1BF == 2) {
        level2 = level1->lchild;
        int level2BF = AVLTree<T>::balanceFactor(level2);
        if (level2 == nullptr)
            return;
        
        if (level2BF >= 0) {
            level3 = level2->lchild;
        } else {
            level3 = level2->rchild;
        }
    } else {
        level2 = level1->rchild;
        int level2BF = AVLTree<T>::balanceFactor(level2);
        if (level2 == nullptr)
            return;
        
        if (level2BF > 0) {
            level3 = level2->lchild;
        } else {
            level3 = level2->rchild;
        }
    }
    this->balance(level1, level2, level3);
}

template <typename T>
const AVLTreeNode<T> *AVLTree<T>::find(const T &data) const {
    return this->find_impl(m_root, data);
}

template <typename T>
AVLTreeNode<T> *AVLTree<T>::find(const T &data) {
    return const_cast<AVLTreeNode<T> *>(this->find_impl(m_root, data));
}

template <typename T>
template <typename UnaryFunc>
void AVLTree<T>::preorder(UnaryFunc unary) const {
    if (m_root == nullptr)
        return;
    this->preorder_impl(m_root, unary);
}

template <typename T>
void AVLTree<T>::balance(AVLTreeNode<T> *level1, AVLTreeNode<T> *level2, AVLTreeNode<T> *level3) {
    auto level1bf = AVLTree::balanceFactor(level1);
    auto level2bf = AVLTree::balanceFactor(level2);
    auto tag = ThreeNodeTreeTag::Balanced;
    if (level1bf > -2 && level1bf < 2)
        return;
    if (level1bf == 2) {
        if (level2bf == -1)
            tag = ThreeNodeTreeTag::LeftRightTag;
        if (level2bf == 1 || level2bf == 0)
            tag = ThreeNodeTreeTag::LeftLeftTag;
    } else {
        if (level2bf == 1)
            tag = ThreeNodeTreeTag::RightLeftTag;
        if (level2bf == -1 || level2bf == 0)
            tag = ThreeNodeTreeTag::RightRightTag;
    }
    
    if (level1->parent == nullptr) {
        ThreeNodeTree<T> tnt(level1, level2, level3, tag);
        this->m_root = tnt.balancedRoot();
        return;
    }
    
    AVLTreeNode<T> *parent = level1->parent;
    bool isLeftChild = (level1 == parent->lchild);
    if (isLeftChild) {
        ThreeNodeTree<T> tnt(level1, level2, level3, tag);
        AVLTreeNode<T> *balancedRoot = tnt.balancedRoot();
        parent->lchild = balancedRoot; AVLTree<T>::setParent(balancedRoot, parent);
    } else {
        ThreeNodeTree<T> tnt(level1, level2, level3, tag);
        AVLTreeNode<T> *balancedRoot = tnt.balancedRoot();
        parent->rchild = balancedRoot; AVLTree<T>::setParent(balancedRoot, parent);
    }
}

template <typename T>
AVLTreeNode<T> *AVLTree<T>::tryInsert(AVLTreeNode<T> *node, const T &data) {
    bool lessOrNot = (data < node->data);
    bool greaterOrNot = (node->data < data);
    AVLTreeNode<T> *ret = nullptr;
    
    if (lessOrNot == true) {
        if (node->lchild == nullptr) {
            auto newnode = new AVLTreeNode<T>({data, 1, nullptr, nullptr, node});
            node->lchild = newnode;
            node->height = 2;
            return newnode;
        }
        
        ret = this->tryInsert(node->lchild, data);
    }
    
    if (greaterOrNot == true) {
        if (node->rchild == nullptr) {
            auto newnode = new AVLTreeNode<T>({data, 1, nullptr, nullptr, node});
            node->rchild = newnode;
            node->height = 2;
            return newnode;
        }
        
        ret = this->tryInsert(node->rchild, data);
    }
    
    this->recalcHeight(node);
    return ret;
}

template <typename T>
AVLTreeNode<T> *AVLTree<T>::tryEraseReturnParent(AVLTreeNode<T> *node) {
    AVLTreeNode<T> *nodeParent = node->parent;
    
    // case 1: leaf
    if (node->lchild == nullptr && node->rchild == nullptr) {
        if (node == m_root) {
            delete m_root;
            m_root = nullptr;
            return nullptr;
        }
        AVLTree<T>::unlink(node);
        delete node;
        nodeParent->height -= 1;
        return nodeParent;
    }
    
    // case 2: node with an only child
    if (node->lchild != nullptr && node->rchild == nullptr) {
        if (node == m_root) {
            m_root = node->lchild;
            AVLTree<T>::setParent(node->lchild, nullptr);
            delete node;
            return m_root;
        }
        
        if (nodeParent->lchild == node) {
            nodeParent->lchild = node->lchild; AVLTree<T>::setParent(node->lchild, nodeParent);
            delete node;
            return nodeParent;
        } else {
            nodeParent->rchild = node->lchild; AVLTree<T>::setParent(node->lchild, nodeParent);
            delete node;
            return nodeParent;
        }
    } else if (node->lchild == nullptr && node->rchild != nullptr) {
        if (node == m_root) {
            m_root = node->rchild;
            AVLTree<T>::setParent(node->rchild, nullptr);
            delete node;
            return m_root;
        }
        
        if (nodeParent->lchild == node) {
            nodeParent->lchild = node->rchild;
            AVLTree<T>::setParent(node->rchild, nodeParent);
            delete node;
            return nodeParent;
        } else {
            nodeParent->rchild = node->rchild;
            AVLTree<T>::setParent(node->rchild, nodeParent);
            delete node;
            return nodeParent;
        }
    }
    
    // case 3: node with 2 children
    // use the left subtree's largest node to replace the node to be erased
    AVLTreeNode<T> *replaceNode = node->lchild;
    while (replaceNode->rchild != nullptr)
        replaceNode = replaceNode->rchild;
    
    auto replaceParent = replaceNode->parent;
    AVLTree<T>::replaceWith_erase(node, replaceNode);
    if (node == m_root) {
        m_root = replaceNode;
        delete node;
        AVLTree<T>::recalcHeight(m_root);
        return m_root;
    }
    // special case when replaceParent is the node to be deleted itself
    if (replaceParent == node) {
        delete node;
        AVLTree<T>::recalcHeight(replaceNode);
        return replaceNode;
    }
    delete node;
    AVLTree<T>::recalcHeight(replaceParent);
    return replaceParent;
}

template <typename T>
void AVLTree<T>::recalcHeight(AVLTreeNode<T> *node) {
    if (node == nullptr)
        return;
    node->height = std::max(AVLTree<T>::height(node->lchild), AVLTree<T>::height(node->rchild)) + 1;
}

template <typename T>
void AVLTree<T>::unlink(AVLTreeNode<T> *node) {
    auto parent = node->parent;
    if (node == parent->lchild) {
        parent->lchild = nullptr;
    } else {
        parent->rchild = nullptr;
    }
    AVLTree<T>::setParent(node, nullptr);
}

template <typename T>
void AVLTree<T>::replaceWith_erase(AVLTreeNode<T> *node, AVLTreeNode<T> *replace) {
    // special case:
    if (node->lchild == replace) {
        replace->rchild = node->rchild; AVLTree<T>::setParent(node->rchild, replace);
        
        AVLTree<T>::setParent(replace, node->parent);
        if (node->parent != nullptr) {
            if (node->parent->lchild == node) {
                node->parent->lchild = replace;
            } else {
                node->parent->rchild = replace;
            }
        }
        return;
    } else if (node->rchild == replace) {
        replace->lchild = node->lchild; AVLTree<T>::setParent(node->lchild, replace);
        
        AVLTree<T>::setParent(replace, node->parent);
        if (node->parent != nullptr) {
            if (node->parent->lchild == node) {
                node->parent->lchild = replace;
            } else {
                node->parent->rchild = replace;
            }
        }
        return;
    }
    
    auto nodeParent = node->parent;
    auto nodeLChild = node->lchild;
    auto nodeRChild = node->rchild;
    auto rpParent = replace->parent;
    
    if (rpParent->lchild == replace) {
        rpParent->lchild = replace->rchild; AVLTree<T>::setParent(replace->rchild, rpParent);
    } else {
        rpParent->rchild = replace->lchild; AVLTree<T>::setParent(replace->lchild, rpParent);
    }
    
    if (nodeParent != nullptr) {
        if (nodeParent->lchild == node) {
            nodeParent->lchild = replace;
        } else {
            nodeParent->rchild = replace;
        }
    }
    AVLTree<T>::setParent(replace, nodeParent);
    
    replace->lchild = nodeLChild; AVLTree<T>::setParent(nodeLChild, replace);
    replace->rchild = nodeRChild; AVLTree<T>::setParent(nodeRChild, replace);
}

template <typename T>
const AVLTreeNode<T> *AVLTree<T>::find_impl(const AVLTreeNode<T> *node, const T &data) const {
    if (node == nullptr)
        return nullptr;
    
    bool lessOrNot = (data < node->data);
    bool greaterOrNot = (node->data < data);
    
    if (lessOrNot == true)
        return this->find_impl(node->lchild, data);
    if (greaterOrNot == true)
        return this->find_impl(node->rchild, data);
    return node;
}

template <typename T>
template <typename UnaryFunc>
void AVLTree<T>::preorder_impl(const AVLTreeNode<T> *node, UnaryFunc unary) const {
    unary(node->data);
    if (node->lchild != nullptr)
        this->preorder_impl(node->lchild, unary);
    if (node->rchild != nullptr)
        this->preorder_impl(node->rchild, unary);
}

template <typename T>
std::string AVLTree<T>::str() const {
    if (m_root == nullptr)
        return "()";
    return str_impl(m_root);
}

template <typename T>
std::string AVLTree<T>::str_impl(AVLTreeNode<T> *node) const {
    std::string ret;
    ret += '(';
    if (node != nullptr) {
        ret += std::to_string(node->data);
        ret += ' ';
        ret += this->str_impl(node->lchild);
        ret += ' ';
        ret += this->str_impl(node->rchild);
    }
    ret += ')';
    return ret;
}

template <typename T>
void AVLTree<T>::setParent(AVLTreeNode<T> *node, AVLTreeNode<T> *parent) {
    if (node != nullptr)
        node->parent = parent;
}

namespace std {
    template <typename T>
    std::string to_string(const AVLTree<T> &tree) {
        return tree.str();
    }
}
