#include "db/database.hpp"
#include "memtable/skip_list.hpp"

int main()
{
    Database<SkipList> d;
    (void)d;
    return 0;
}
