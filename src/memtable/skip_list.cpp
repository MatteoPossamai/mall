#include "skip_list.hpp"

#include <string>

ListNode *create_new_node(std::string key, std::string value, bool sentinel, bool tombstone)
{
    return new ListNode{key, value, sentinel, tombstone, nullptr, nullptr, nullptr, nullptr};
}

std::string SkipList::get(std::string key)
{
    ListNode *current = levels[SKIP_LIST_SIZE - 1];
    for (int i = SKIP_LIST_SIZE - 1; i >= 0; i--)
    {
        while (current->right != nullptr && current->right->key < key)
        {
            current = current->right;
        }
        if (i > 0)
        {
            current = current->down;
        }
    }

    ListNode *target = current->right;
    if (target == nullptr || target->key != key || target->tombstone)
    {
        return NOT_FOUND_VALUE;
    }
    return target->value;
}

void SkipList::_insert(std::string key, std::string value, bool remove)
{
    ListNode *current = levels[SKIP_LIST_SIZE - 1];
    ListNode *prev[SKIP_LIST_SIZE];
    int no_levels = generator.generate_level();

    for (int i = SKIP_LIST_SIZE - 1; i >= 0; i--)
    {
        while (current->right != nullptr && current->right->key < key)
        {
            current = current->right;
        }
        prev[i] = current;
        if (i > 0)
        {
            current = current->down;
        }
    }

    if (prev[0]->right != nullptr && prev[0]->right->key == key)
    {
        ListNode *node = prev[0]->right;
        while (node != nullptr)
        {
            node->value = value;
            node->tombstone = remove;
            node = node->up;
        }
        return;
    }

    ListNode *down_node = nullptr;
    for (int i = 0; i <= no_levels; i++)
    {
        // Insert a new node
        current = prev[i];
        ListNode *new_node = create_new_node(key, value, false, remove);
        if (current->right != nullptr)
        {
            current->right->left = new_node;
            new_node->right = current->right;
        }
        current->right = new_node;
        new_node->left = current;

        if (down_node != nullptr)
        {
            down_node->up = new_node;
            new_node->down = down_node;
        }
        down_node = new_node;
    }
}

void SkipList::insert(std::string key, std::string value)
{
    _insert(key, value, false);
}

void SkipList::remove(std::string key)
{
    _insert(key, NOT_FOUND_VALUE, true);
}