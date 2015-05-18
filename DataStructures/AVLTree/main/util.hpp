#pragma once
// STL
#include <string>
#include <vector>

namespace std {
    template <typename T>
    std::string to_string(const std::vector<T> &vec) {
        std::string ret;
        ret += '{';
        for(const auto &item : vec) {
            ret += std::to_string(item);
            ret += ',';
        }
        if(ret.back() == ',') {
            ret.back() = '}';
        } else {
            ret += '}';
        }
        
        return ret;
    }
}

template <typename T>
std::vector<T> to_vector(const AVLTree<T> &tree) {
    std::vector<T> ret;
    tree.preorder([&ret](const auto &data) { ret.push_back(data); });
    return ret;
}
