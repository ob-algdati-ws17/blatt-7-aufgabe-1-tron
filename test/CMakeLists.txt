file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(testAVLTree ${SRCS} ../avltree/AVLTree.h ../avltree/AVLTree.cpp)

target_link_libraries(testAVLTree
        gtest
        gmock
        )

include_directories("..")

install(TARGETS testAVLTree DESTINATION bin)