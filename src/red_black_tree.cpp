#include "red_black_tree.hpp"

void RedBlackTree::_insert(std::string key, std::string value, bool tombstone)
{
    if (root == NIL::instance())
    {
        root = create_new_node(key, value, tombstone);
        root->color = Colors::BLACK;
        return;
    }

    // Insertion at the end
    TreeNode *current = root;
    TreeNode *prev = NIL::instance();
    while (current != NIL::instance())
    {
        prev = current;
        if (key > current->key)
        {
            current = current->right;
        }
        else if (key < current->key)
        {
            current = current->left;
        }
        else // case in which key already present we just need to overwrite
        {
            current->value = value;
            current->tombstone = tombstone;
            return;
        }
    }
    TreeNode *new_node = create_new_node(key, value, tombstone);
    new_node->parent = prev;
    if (prev->key > key)
    {
        prev->left = new_node;
    }
    else
    {
        prev->right = new_node;
    }
    rebalance(new_node);
}

TreeNode *RedBlackTree::rotate_helper(TreeNode *node)
{
    TreeNode *father = node->parent;
    if (father != root)
    {
        if (is_left_child(father))
        {
            father->parent->left = node;
        }
        else
        {
            father->parent->right = node;
        }
    }
    else
    {
        root = node;
    }
    return father;
}

void RedBlackTree::rotate_left(TreeNode *node)
{
    if (node == NIL::instance() || node == root)
    {
        return;
    }
    TreeNode *father = rotate_helper(node);
    node->parent = father->parent;

    TreeNode *left = node->left;
    node->left = father;
    father->parent = node;

    father->right = left;
    if (left != NIL::instance())
        left->parent = father;
}

void RedBlackTree::rotate_right(TreeNode *node)
{
    if (node == NIL::instance() || node == root)
    {
        return;
    }
    TreeNode *father = rotate_helper(node);
    node->parent = father->parent;

    TreeNode *right = node->right;
    node->right = father;
    father->parent = node;

    father->left = right;
    if (right != NIL::instance())
        right->parent = father;
}

void RedBlackTree::rebalance(TreeNode *node)
{
    while (node != root && node->parent->color == Colors::RED)
    {
        TreeNode *father = node->parent;
        TreeNode *grand = father->parent;
        bool father_is_left = is_left_child(father);
        TreeNode *uncle = father_is_left ? grand->right : grand->left;

        if (uncle->color == Colors::RED)
        {
            // Case 1: recolor, bubble up
            father->color = Colors::BLACK;
            uncle->color = Colors::BLACK;
            grand->color = Colors::RED;
            node = grand;
        }
        else
        {
            // Case 2: zig-zag -> straighten into line
            if (is_left_child(node) != father_is_left)
            {
                TreeNode *old_father = father;
                father_is_left ? rotate_left(node) : rotate_right(node);
                node = old_father;
                father = node->parent;
            }
            // Case 3: line -> recolor + rotate father up
            father->color = Colors::BLACK;
            grand->color = Colors::RED;
            father_is_left ? rotate_right(father) : rotate_left(father);
        }
    }
    root->color = Colors::BLACK;
}

void RedBlackTree::insert(std::string key, std::string value)
{
    _insert(key, value, false);
}

void RedBlackTree::remove(std::string key)
{
    _insert(key, NOT_FOUND_VALUE, true);
}

std::string RedBlackTree::get(std::string key)
{
    TreeNode *current = root;

    while (current != NIL::instance() && current->key != key)
    {
        current = current->key > key ? current->left : current->right;
    }

    if (current->tombstone)
    {
        return NOT_FOUND_VALUE;
    }

    return current->value;
}

TreeNode *create_new_node(std::string key, std::string value, bool tombstone)
{
    return new TreeNode{key, value, tombstone, Colors::RED, NIL::instance(), NIL::instance(), NIL::instance()};
};