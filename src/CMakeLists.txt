add_subdirectory(memtable)
add_subdirectory(db)

add_executable(main_test main.cpp)
target_link_libraries(main_test PRIVATE rbtree skiplist)

target_include_directories(main_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(main_test PRIVATE -Wall -Wextra -Wpedantic)
