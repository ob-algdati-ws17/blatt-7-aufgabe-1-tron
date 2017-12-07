#include "testLibrary.h"
#include <memory>

using namespace std;

TEST(AVLTreeTest, Test_CreateTree) {
cout << " a test is needed here" << endl;
AVLTree tree;
EXPECT_FALSE(tree.search(1));
}

