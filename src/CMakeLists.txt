add_library(rbtree STATIC
    red_black_tree.cpp
)

target_include_directories(rbtree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(rbtree PRIVATE -Wall -Wextra -Wpedantic)
