#include "testLibrary.h"
#include <memory>

using namespace std;

// Empty Tree

TEST(TestAVLTree , Test_EmptyTree) {
    AVLTree t;
    //cout << t << endl;
    EXPECT_TRUE(t.balanced());
    EXPECT_FALSE(t.search(1));
}

// Create and Search Tree

TEST(TestAVLTree , Test_CreateTree_Search_Found) {
    AVLTree t;
    t.insert(1);
    //cout << t << endl;
    EXPECT_TRUE(t.search(1));
}

TEST(TestAVLTree , Test_CreateTree_Search_Not_Found) {
    AVLTree t;
    t.insert(1);
    //cout << t << endl;
    EXPECT_FALSE(t.search(2));
}

TEST(TestAVLTree , Test_CreateTree_Search_Empty_Tree) {
    AVLTree t;
    //cout << t << endl;
    EXPECT_FALSE(t.search(1));
}

// Tree Rotation

TEST(TestAVLTree , Test_CreateTree_Left_Rotation) {
    AVLTree t;
    for (int i = 0; i < 10; i++) {
        t.insert(i);
    }
    //cout << t << endl;
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_CreateTree_Double_Left_Rotation) {
    AVLTree t;
    for (int i = 0; i < 10; i++) {
        t.insert(i);
        for (int k = 20; k >= 11; k--) {
            t.insert(k);
        }
    }
    //cout << t << endl;
    EXPECT_TRUE(t.search(11));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_CreateTree_Right_Rotation) {
    AVLTree t;
    for (int i = 10; i > 0; i--) {
        t.insert(i);
    }
    //cout << t << endl;
    EXPECT_TRUE(t.search(5));
    EXPECT_FALSE(t.search(31));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_CreateTree_Double_Right_Rotation) {
    AVLTree t;
    for (int i = 10; i > 0; i--) {
        t.insert(i);
        for (int k = 0; k < 10; k++) {
            t.insert(k);
        }
    }
    //cout << t << endl;
    EXPECT_TRUE(t.search(5));
    EXPECT_FALSE(t.search(31));
    EXPECT_TRUE(t.balanced());
}

// Remove

TEST(TestAVLTree , Test_CreateTree_Remove_Not_Exists) {
    AVLTree t;
    EXPECT_FALSE(t.remove(1));
}

TEST(TestAVLTree , Test_CreateTree_Remove_Exists) {
    AVLTree t;
    t.insert(1);
    t.insert(2);
    //cout << t << endl;
    EXPECT_TRUE(t.remove(1));
}

TEST(TestAVLTree , Test_CreateTree_Remove_Exists_And_Not_Found) {
    AVLTree t;
    t.insert(1);
    t.insert(2);
    //cout << t << endl;
    EXPECT_FALSE(t.remove(3));
}

TEST(TestAVLTree , Test_Remove_Root_With_No_Nodes) {
    AVLTree t;
    t.insert(1);
    t.remove(1);
    //cout << t << endl;
    EXPECT_FALSE(t.search(1));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Root_With_Left_Node) {
    AVLTree t;
    t.insert(2);
    t.insert(1);
    t.remove(2);
    //cout << t << endl;
    EXPECT_FALSE(t.search(2));
    EXPECT_TRUE(t.search(1));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Root_With_Right_Node) {
    AVLTree t;
    t.insert(2);
    t.insert(3);
    t.remove(2);
    //cout << t << endl;
    EXPECT_FALSE(t.search(2));
    EXPECT_TRUE(t.search(3));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Root_With_Two_Nodes) {
    AVLTree t;
    t.insert(2);
    t.insert(1);
    t.insert(3);
    t.remove(2);
    //cout << t << endl;
    EXPECT_FALSE(t.search(2));
    EXPECT_TRUE(t.search(1));
    EXPECT_TRUE(t.search(3));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Left_With_No_Nodes) {
    AVLTree t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.remove(1);
    //cout << t << endl;
    EXPECT_FALSE(t.search(1));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Right_With_No_Nodes) {
    AVLTree t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.remove(3);
    //cout << t << endl;
    EXPECT_FALSE(t.search(3));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Left_With_Left_Node) {
    AVLTree t;
    t.insert(5);
    t.insert(3);
    t.insert(6);
    t.insert(1);
    t.remove(3);
    //cout << t << endl;
    EXPECT_FALSE(t.search(3));
    EXPECT_TRUE(t.search(1));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Left_With_Right_Node) {
    AVLTree t;
    t.insert(5);
    t.insert(3);
    t.insert(6);
    t.insert(4);
    t.remove(3);
    //cout << t << endl;
    EXPECT_FALSE(t.search(3));
    EXPECT_TRUE(t.search(4));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Right_With_Left_Node) {
    AVLTree t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(6);
    t.remove(7);
    //cout << t << endl;
    EXPECT_FALSE(t.search(7));
    EXPECT_TRUE(t.search(6));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Right_With_Right_Node) {
    AVLTree t;
    t.insert(5);
    t.insert(3);
    t.insert(6);
    t.insert(8);
    t.remove(6);
    //cout << t << endl;
    EXPECT_FALSE(t.search(6));
    EXPECT_TRUE(t.search(8));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Left_With_Two_Nodes) {
    AVLTree t;
    t.insert(5);
    t.insert(3);
    t.insert(6);
    t.insert(1);
    t.insert(4);
    t.remove(3);
    //cout << t << endl;
    EXPECT_FALSE(t.search(3));
    EXPECT_TRUE(t.search(1));
    EXPECT_TRUE(t.search(4));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Remove_Right_With_Two_Nodes) {
    AVLTree t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(6);
    t.insert(8);
    t.remove(7);
    //cout << t << endl;
    EXPECT_FALSE(t.search(7));
    EXPECT_TRUE(t.search(6));
    EXPECT_TRUE(t.search(8));
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Single_Left_Rotation) {
    AVLTree t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Single_Right_Rotation) {
    AVLTree t;
    t.insert(3);
    t.insert(2);
    t.insert(1);
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Double_Left_Rotation) {
    AVLTree t;
    t.insert(1);
    t.insert(3);
    t.insert(2);
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_Double_Right_Rotation) {
    AVLTree t;
    t.insert(3);
    t.insert(1);
    t.insert(2);
    EXPECT_TRUE(t.balanced());
}

TEST(TestAVLTree , Test_It_All) {
    AVLTree t;
    t.insert(5);
    t.insert(3);
    t.insert(2);
    EXPECT_TRUE(t.balanced());
    t.insert(2);
    EXPECT_TRUE(t.balanced());
    t.insert(5);
    EXPECT_TRUE(t.balanced());
    t.insert(8);
    t.insert(4);
    t.insert(7);
    EXPECT_TRUE(t.balanced());
    EXPECT_TRUE(t.search(2));
    EXPECT_TRUE(t.search(3));
    EXPECT_TRUE(t.search(4));
    EXPECT_TRUE(t.search(5));
    EXPECT_TRUE(t.search(7));
    EXPECT_TRUE(t.search(8));
}
