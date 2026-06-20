add_library(rbtree STATIC
    red_black_tree.cpp
)

add_library(skiplist STATIC
    skip_list.cpp
)

target_include_directories(rbtree PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(skiplist PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_compile_options(rbtree PUBLIC -Wall -Wextra -Wpedantic)
target_compile_options(skiplist PUBLIC -Wall -Wextra -Wpedantic)