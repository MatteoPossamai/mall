#pragma once

#include "common/common.hpp"

#include <limits.h>
#include <random>
#include <string>

#define SKIP_LIST_SIZE 16

struct ListNode
{
    std::string key;
    std::string value;
    bool sentinel;
    bool tombstone;
    ListNode *up;    // The level above. Level 0 is the smallest. Up(0) = 1
    ListNode *down;  // The level below.
    ListNode *left;  // The layer before. Going back
    ListNode *right; // The layer after. Going on
};

ListNode *create_new_node(std::string key, std::string value, bool sentinel = false, bool tombstone = false);

class RandomGenerator
{
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    RandomGenerator()
        : gen(rd()), dist(0, INT_MAX)
    {
    }
    int generate()
    {
        return dist(gen);
    }
    int generate_level()
    {
        int level = 0;
        int generated = generate();
        while (level < SKIP_LIST_SIZE - 1 && (generated & 1))
        {
            level++;
            generated >>= 1;
        }
        return level;
    }
};

class SkipList
{
    ListNode *levels[SKIP_LIST_SIZE];
    RandomGenerator *generator;

public:
    SkipList()
    {
        levels[0] = create_new_node("", "", true, false);
        for (int i = 1; i < SKIP_LIST_SIZE; i++)
        {
            levels[i] = create_new_node("", "", true, false);
            levels[i]->down = levels[i - 1];
            levels[i - 1]->up = levels[i];
        }
        generator = new RandomGenerator();
    }

    void insert(std::string key, std::string value);
    void remove(std::string key);
    std::string get(std::string key);

private:
    void _insert(std::string key, std::string value, bool remove);
};
