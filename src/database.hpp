#pragma once

#include "memtable.hpp"

template <Memtable M>
class Database {
    M memtable;
};
