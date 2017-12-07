#include "testLibrary.h"
#include <memory>

using namespace std;

// Empty Tree

TEST(AVLTreeTest, Test_EmptyTree) {
    AVLTree t;
    cout << t << endl;
    EXPECT_TRUE(t.balanced());
    EXPECT_FALSE(t.search(1));
}

// Create and Search Tree

TEST(AVLTreeTest, Test_CreateTree_Search_Found) {
    AVLTree t;
    t.insert(1);
    cout << t << endl;
    EXPECT_TRUE(t.search(1));
}

TEST(AVLTreeTest, Test_CreateTree_Search_Not_Found) {
    AVLTree t;
    t.insert(1);
    cout << t << endl;
    EXPECT_FALSE(t.search(2));
}

TEST(AVLTreeTest, Test_CreateTree_Search_Empty_Tree) {
    AVLTree t;
    cout << t << endl;
    EXPECT_FALSE(t.search(1));
}

// Tree Rotation

TEST(AVLTreeTest, Test_CreateTree_Left_Rotation) {
    AVLTree t;
    for (int i = 0; i < 10; i++) {
        t.insert(i);
    }
    cout << t << endl;
    EXPECT_TRUE(t.balanced());
}

TEST(AVLTreeTest, Test_CreateTree_Double_Left_Rotation) {
    AVLTree t;
    for (int i = 0; i < 10; i++) {
        t.insert(i);
        for (int k = 20; k >= 11; k--) {
            t.insert(k);
        }
    }
    cout << t << endl;
    EXPECT_TRUE(t.search(11));
    EXPECT_TRUE(t.balanced());
}

TEST(AVLTreeTest, Test_CreateTree_Right_Rotation) {
    AVLTree t;
    for (int i = 10; i > 0; i--) {
        t.insert(i);
    }
    cout << t << endl;
    EXPECT_TRUE(t.search(5));
    EXPECT_FALSE(t.search(31));
    EXPECT_TRUE(t.balanced());
}

TEST(AVLTreeTest, Test_CreateTree_Double_Right_Rotation) {
    AVLTree t;
    for (int i = 10; i > 0; i--) {
        t.insert(i);
        for (int k = 0; k < 10; k++) {
            t.insert(k);
        }
    }
    cout << t << endl;
    EXPECT_TRUE(t.search(5));
    EXPECT_FALSE(t.search(31));
    EXPECT_TRUE(t.balanced());
}

// Remove

TEST(AVLTreeTest, Test_CreateTree_Remove_Not_Exists) {
    AVLTree t;
    EXPECT_FALSE(t.remove(1));
}

TEST(AVLTreeTest, Test_CreateTree_Remove_Exists) {
    AVLTree t;
    t.insert(1);
    t.insert(2);
    cout << t << endl;
    EXPECT_TRUE(t.remove(1));
    cout << t << endl;
    EXPECT_FALSE(t.remove(3));
}




