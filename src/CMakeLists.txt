add_library(rbtree STATIC
    red_black_tree.cpp
)

add_library(skiplist STATIC
    skip_list.cpp
)

target_include_directories(rbtree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(skiplist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(rbtree PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(skiplist PRIVATE -Wall -Wextra -Wpedantic)
