# CMake generated Testfile for 
# Source directory: C:/Users/Max/Documents/GitHub/blatt-7-aufgabe-1-tron
# Build directory: C:/Users/Max/Documents/GitHub/blatt-7-aufgabe-1-tron/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TestAVLTree "test/testLibrary" "--gtest_output=xml:report.xml")
subdirs("avltree")
subdirs("googletest-build")
subdirs("test")
