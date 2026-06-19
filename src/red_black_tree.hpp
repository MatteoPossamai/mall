#pragma once

#include "common.hpp"

#include <string>

static std::string NIL_KEY = "<---NIL--->";

enum Colors
{
    BLACK,
    RED
};

struct TreeNode
{
    std::string key;
    std::string value;
    bool tombstone;
    Colors color;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
};

class NIL
{
public:
    static TreeNode *instance()
    {
        static TreeNode *nil = []
        {
            TreeNode *n = new TreeNode{NIL_KEY, NOT_FOUND_VALUE, false, Colors::BLACK, nullptr, nullptr, nullptr};
            n->left = n->right = n->parent = n;
            return n;
        }();
        return nil;
    }
};

class RedBlackTree
{
    TreeNode *root = NIL::instance();

public:
    void insert(std::string key, std::string value);
    void remove(std::string key);
    std::string get(std::string key);

private:
    void _insert(std::string key, std::string value, bool tombstone = false);
    void rebalance(TreeNode *node);
    TreeNode *rotate_helper(TreeNode *node);
    void rotate_left(TreeNode *node);
    void rotate_right(TreeNode *node);

    bool is_left_child(TreeNode *node)
    {
        if (node == root)
        {
            return false;
        }
        return node == node->parent->left;
    }

    void destroy(TreeNode *node)
    {
        if (node == NIL::instance())
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

TreeNode *create_new_node(std::string key, std::string value, bool tombstone = false);