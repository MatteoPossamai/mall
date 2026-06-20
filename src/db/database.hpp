#pragma once

#include "memtable/memtable.hpp"

template <Memtable M>
class Database {
    M memtable;
};
