#include "AVLTree.hpp"
// gtest
#include <gtest/gtest.h>
// STL
#include <string>
#include <vector>
// Current Project
#include "util.hpp"

TEST(AVLTreeTest, InsertCase1) {
    AVLTree<int> tree({5,4,3});
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({4,3,5}), to_vector(tree));
}

TEST(AVLTreeTest, InsertCase2) {
    AVLTree<int> tree({50,40,60,30,45,20});
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({40,30,20,50,45,60}), to_vector(tree));
}

TEST(AVLTreeTest, InsertCase3) {
    AVLTree<int> tree({5,6,7});
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({6,5,7}), to_vector(tree));
}

TEST(AVLTreeTest, InsertCase4) {
    AVLTree<int> tree({50,40,60,55,70,80});
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({60,50,40,55,70,80}), to_vector(tree));
}

TEST(AVLTreeTest, InsertCase5) {
    AVLTree<int> tree({50,40,45});
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({45,40,50}), to_vector(tree));
}

TEST(AVLTreeTest, InsertCase6) {
    AVLTree<int> tree({50,40,60,30,45,47});
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({45,40,30,50,47,60}), to_vector(tree));
}

TEST(AVLTreeTest, InsertCase7) {
    AVLTree<int> tree({50,60,55});
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({55,50,60}), to_vector(tree));
}

TEST(AVLTreeTest, InsertCase8) {
    AVLTree<int> tree({50,40,60,55,70,53});
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({55,50,40,53,60,70}), to_vector(tree));
}

TEST(AVLTreeTest, InsertTest1) {
    AVLTree<int> tree;
    
    tree.insert(6);
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({6}), to_vector(tree));
    
    tree.insert(1);
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({6,1}), to_vector(tree));
    
    tree.insert(3);
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({3,1,6}), to_vector(tree));
    
    tree.insert(4);
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({3,1,6,4}), to_vector(tree));
    
    tree.insert(5);
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({3,1,5,4,6}), to_vector(tree));
    
    tree.insert(7);
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({5,3,1,4,6,7}), to_vector(tree));
    
    tree.insert(8);
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({5,3,1,4,7,6,8}), to_vector(tree));
    
    tree.insert(9);
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({5,3,1,4,7,6,8,9}), to_vector(tree));
}

TEST(AVLTreeTest, EraseCase1) {
    AVLTree<int> tree({1});
    std::cerr << std::to_string(tree) << '\n';
    tree.erase(tree.find(1));
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({}), to_vector(tree));
}

TEST(AVLTreeTest, EraseCase2) {
    AVLTree<int> tree({3,1,5,0,2,4,6});
    std::cerr << std::to_string(tree) << '\n';
    tree.erase(tree.find(2));
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({3,1,0,5,4,6}), to_vector(tree));
}

TEST(AVLTreeTest, EraseCase3) {
    AVLTree<int> tree({30,10,50,0,20,40,60,15});
    std::cerr << std::to_string(tree) << '\n';
    tree.erase(tree.find(15));
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({30,10,0,20,50,40,60}), to_vector(tree));
}

TEST(AVLTreeTest, EraseCase4) {
    AVLTree<int> tree({30,10,50,9,12,40,7,8,11,13});
    std::cerr << std::to_string(tree) << '\n';
    tree.erase(tree.find(40));
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({10,8,7,9,30,12,11,13,50}), to_vector(tree));
}

TEST(AVLTreeTest, EraseCase5) {
    AVLTree<int> tree({30,10,50,8,12,40,7,9});
    std::cerr << std::to_string(tree) << '\n';
    tree.erase(tree.find(40));
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({10,8,7,9,30,12,50}), to_vector(tree));
}

TEST(AVLTreeTest, EraseCase6) {
    AVLTree<int> tree({30,10,50,8,20,40,60,7,9,18,21,55,17,19});
    std::cerr << std::to_string(tree) << '\n';
    tree.erase(tree.find(55));
    std::cerr << std::to_string(tree) << '\n';
    EXPECT_EQ(std::vector<int>({20,10,8,7,9,18,17,19,30,21,50,40,60}), to_vector(tree));
}

TEST(AVLTreeTest, EraseTest1) {
    AVLTree<int> tree({30,10,50,8,20,40,60,7,9,18,21,55,17,19});
    std::cerr << std::to_string(tree) << '\n';
    
    tree.erase(tree.find(10));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({30,9,8,7,20,18,17,19,21,50,40,60,55}), to_vector(tree));
    tree.erase(tree.find(8));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({30,18,9,7,17,20,19,21,50,40,60,55}), to_vector(tree));
    tree.erase(tree.find(30));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({21,18,9,7,17,20,19,50,40,60,55}), to_vector(tree));
    tree.erase(tree.find(18));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({21,17,9,7,20,19,50,40,60,55}), to_vector(tree));
    tree.erase(tree.find(50));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({21,17,9,7,20,19,55,40,60}), to_vector(tree));
    tree.erase(tree.find(21));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({20,17,9,7,19,55,40,60}), to_vector(tree));
    tree.erase(tree.find(55));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({20,17,9,7,19,40,60}), to_vector(tree));
    tree.erase(tree.find(40));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({17,9,7,20,19,60}), to_vector(tree));
    tree.erase(tree.find(17));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({9,7,20,19,60}), to_vector(tree));
    tree.erase(tree.find(9));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({20,7,19,60}), to_vector(tree));
    tree.erase(tree.find(20));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({19,7,60}), to_vector(tree));
    tree.erase(tree.find(19));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({7,60}), to_vector(tree));
    tree.erase(tree.find(7));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({60}), to_vector(tree));
    tree.erase(tree.find(60));
    std::cerr << std::to_string(tree) << '\n';
    ASSERT_EQ(std::vector<int>({}), to_vector(tree));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}