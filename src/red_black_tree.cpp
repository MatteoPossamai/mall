#include "red_black_tree.hpp"

void RedBlackTree::_insert(std::string key, std::string value, bool tombstone = false)
{
    if (root == NIL::instance())
    {
        root = create_new_node(key, value);
        root->color = Colors::BLACK;
        return;
    }

    // Insertion at the end
    Node *current = root;
    Node *prev = NIL::instance();
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
    Node *new_node = create_new_node(key, value);
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

Node *RedBlackTree::rotate_helper(Node *node)
{
    Node *father = node->parent;
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

void RedBlackTree::rotate_left(Node *node)
{
    if (node == NIL::instance())
    {
        return;
    }
    Node *father = rotate_helper(node);
    node->parent = father->parent;

    Node *left = node->left;
    node->left = father;
    father->parent = node;

    father->right = left;
    left->parent = father;
}

void RedBlackTree::rotate_right(Node *node)
{
    if (node == NIL::instance())
    {
        return;
    }
    Node *father = rotate_helper(node);
    node->parent = father->parent;

    Node *right = node->right;
    node->right = father;
    father->parent = node;

    father->left = right;
    right->parent = father;
}

void RedBlackTree::rebalance(Node *node)
{
    while (node != root && node->parent->color == Colors::RED)
    {
        Node *father = node->parent;
        Node *grand = father->parent;
        bool father_is_left = is_left_child(father);
        Node *uncle = father_is_left ? grand->right : grand->left;

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
                Node *old_father = father;
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
    _insert(key, "", true);
}