// STL
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
// C-Standard
#include <cstdio>
#include <cassert>

template <typename T>
struct Node {
    T data;
    Node *left;
    Node *right;

    Node() :
        data(),
        left(nullptr),
        right(nullptr)
    {}
};

template <typename T>
std::size_t pre_mid_create_tree(Node<T> ** ppnode, const T *pre, const T *mid, std::size_t len) {
    if (len == 0)
        return 0;

    Node<T> * node = new Node<T>;
    const T & root_data = *pre;
    const std::size_t root_mid_idx = std::find(mid, mid+len, root_data) - mid;

    node->data = root_data;

    std::size_t left_consumed = pre_mid_create_tree(
            &(node->left), pre+1, mid, root_mid_idx);
    std::size_t right_consumed = pre_mid_create_tree(
            &(node->right), pre+left_consumed+1, mid+root_mid_idx+1,
            len-root_mid_idx-1);

    assert(left_consumed + right_consumed + 1 == len);

    (*ppnode) = node;
    return (left_consumed + right_consumed + 1);
}

template <typename T>
std::size_t post_mid_create_tree(Node<T> **ppnode, const T *post, const T *mid, std::size_t len) {
    if (len == 0)
        return 0;

    Node<T> * node = new Node<T>;
    const T &root_data = *(post + len - 1);
    const std::size_t root_mid_idx = std::find(mid, mid+len, root_data) - mid;

    node->data = root_data;

    std::size_t right_consumed = post_mid_create_tree(
            &(node->right), post+root_mid_idx, mid+root_mid_idx+1, len-root_mid_idx-1);
    std::size_t left_consumed = post_mid_create_tree(
            &(node->left), post, mid, len-1-right_consumed);
    
    assert(left_consumed + right_consumed + 1 == len);

    (*ppnode) = node;
    return (left_consumed + right_consumed + 1);
}

template <typename T, typename UnaryFunc>
void preorder_traverse(Node<T> *node, UnaryFunc unary) {
    if (node == nullptr)
        return;

    unary(node);
    preorder_traverse(node->left, unary);
    preorder_traverse(node->right, unary);
}

int main(int argc, char *argv[]) {
    std::string pre ("ABDHLEKCFG");
    std::string mid ("HLDBEKAFCG");
    std::string post("LHDKEBFGCA");

    {
        Node<char> *root = nullptr;
        std::size_t consume = pre_mid_create_tree(&root, pre.data(), mid.data(), pre.size());
        assert(consume == pre.size());

        std::string testpre;
        preorder_traverse(root, [&](auto node) { testpre.push_back(node->data); printf("%c ", node->data); });
        putchar('\n');
        preorder_traverse(root, [](auto node) { delete node; });
        assert(pre == testpre);
    }

    {
        Node<char> *root = nullptr;
        std::size_t consume = post_mid_create_tree(&root, post.data(), mid.data(), pre.size());
        assert(consume == pre.size());

        std::string testpre;
        preorder_traverse(root, [&](auto node) { testpre.push_back(node->data); printf("%c ", node->data); });
        putchar('\n');
        preorder_traverse(root, [](auto node) { delete node; });
    }

    return 0;
}

