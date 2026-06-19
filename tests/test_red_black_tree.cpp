#include <gtest/gtest.h>
#include "red_black_tree.hpp"

TEST(RedBlackTree, InsertSingleKey)
{
    RedBlackTree t;
    t.insert("k", "v");
    EXPECT_EQ(t.get("k"), "v");
}

TEST(RedBlackTree, OverwriteExisting)
{
    RedBlackTree t;
    t.insert("k", "v1");
    t.insert("k", "v2");
    EXPECT_EQ(t.get("k"), "v2");
}