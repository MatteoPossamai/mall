#include <gtest/gtest.h>

#include <algorithm>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "red_black_tree.hpp"

namespace
{
std::string pad(int i)
{
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << i;
    return oss.str();
}
}

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

TEST(RedBlackTree, GetMissingFromEmptyTree)
{
    RedBlackTree t;
    EXPECT_EQ(t.get("nope"), NIL_VALUE);
}

TEST(RedBlackTree, GetMissingFromNonEmptyTree)
{
    RedBlackTree t;
    t.insert("a", "1");
    t.insert("b", "2");
    t.insert("c", "3");
    EXPECT_EQ(t.get("z"), NIL_VALUE);
}

TEST(RedBlackTree, RemoveExistingReturnsNil)
{
    RedBlackTree t;
    t.insert("k", "v");
    t.remove("k");
    EXPECT_EQ(t.get("k"), NIL_VALUE);
}

TEST(RedBlackTree, ReinsertAfterRemoveReturnsNewValue)
{
    RedBlackTree t;
    t.insert("k", "v1");
    t.remove("k");
    t.insert("k", "v2");
    EXPECT_EQ(t.get("k"), "v2");
}

TEST(RedBlackTree, RemoveNonExistentTombstoneStillNil)
{
    RedBlackTree t;
    t.remove("ghost");
    EXPECT_EQ(t.get("ghost"), NIL_VALUE);
}

TEST(RedBlackTree, MultipleKeysAllRetrievable)
{
    RedBlackTree t;
    t.insert("a", "1");
    t.insert("b", "2");
    t.insert("c", "3");
    t.insert("d", "4");
    EXPECT_EQ(t.get("a"), "1");
    EXPECT_EQ(t.get("b"), "2");
    EXPECT_EQ(t.get("c"), "3");
    EXPECT_EQ(t.get("d"), "4");
}

TEST(RedBlackTree, LargeInsertAscending)
{
    RedBlackTree t;
    const int N = 500;
    for (int i = 0; i < N; ++i)
    {
        t.insert(pad(i), "v" + pad(i));
    }
    for (int i = 0; i < N; ++i)
    {
        EXPECT_EQ(t.get(pad(i)), "v" + pad(i));
    }
}

TEST(RedBlackTree, LargeInsertDescending)
{
    RedBlackTree t;
    const int N = 500;
    for (int i = N - 1; i >= 0; --i)
    {
        t.insert(pad(i), "v" + pad(i));
    }
    for (int i = 0; i < N; ++i)
    {
        EXPECT_EQ(t.get(pad(i)), "v" + pad(i));
    }
}

TEST(RedBlackTree, LargeInsertRandom)
{
    RedBlackTree t;
    const int N = 500;
    std::vector<int> keys(N);
    for (int i = 0; i < N; ++i) keys[i] = i;
    std::mt19937 rng(42);
    std::shuffle(keys.begin(), keys.end(), rng);

    for (int k : keys)
    {
        t.insert(pad(k), "v" + pad(k));
    }
    for (int i = 0; i < N; ++i)
    {
        EXPECT_EQ(t.get(pad(i)), "v" + pad(i));
    }
}

TEST(RedBlackTree, MixedInsertRemoveOverwriteWorkload)
{
    RedBlackTree t;
    t.insert("a", "1");
    t.insert("b", "2");
    t.insert("c", "3");
    t.remove("b");
    t.insert("a", "1new");
    t.insert("d", "4");
    t.remove("e");

    EXPECT_EQ(t.get("a"), "1new");
    EXPECT_EQ(t.get("b"), NIL_VALUE);
    EXPECT_EQ(t.get("c"), "3");
    EXPECT_EQ(t.get("d"), "4");
    EXPECT_EQ(t.get("e"), NIL_VALUE);
}
