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

add_executable(
    main_test
    main.cpp
    skip_list.cpp
    red_black_tree.cpp
)

target_include_directories(main_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(main_test PRIVATE -Wall -Wextra -Wpedantic)
