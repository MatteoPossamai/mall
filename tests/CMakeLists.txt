include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    test_red_black_tree.cpp
    test_skip_list.cpp
)

target_link_libraries(run_tests PRIVATE
    rbtree
    skiplist
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)
