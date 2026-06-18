#pragma once

#include <string>

enum Colors
{
    BLACK,
    RED
};

struct Node
{
    std::string key;
    std::string value;
    bool tombstone;
    Colors color;
    Node *left;
    Node *right;
    Node *parent;
};

class NIL
{
public:
    static Node *instance()
    {
        static Node *nil = []
        {
            Node *n = new Node{"", "", Colors::BLACK};
            n->left = n->right = n->parent = n;
            return n;
        }();
        return nil;
    }
};

class RedBlackTree
{
    Node *root = NIL::instance();

public:
    void insert(std::string key, std::string value);
    void remove(std::string key);

private:
    void _insert(std::string key, std::string value, bool tombstone = false);
    void rebalance(Node *node);
    Node *rotate_helper(Node *node);
    void rotate_left(Node *node);
    void rotate_right(Node *node);

    bool is_left_child(Node *node)
    {
        if (node == root)
        {
            return false;
        }
        return node == node->parent->left;
    }

    void destroy(Node *node)
    {
        if (node == NIL::instance())
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

Node *create_new_node(std::string key, std::string value, bool tombstone = false)
{
    return new Node{key, value, tombstone, Colors::RED, NIL::instance(), NIL::instance(), NIL::instance()};
};