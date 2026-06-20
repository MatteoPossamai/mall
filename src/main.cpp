#include "database.hpp"
#include "skip_list.hpp" // brings in the concrete SkipList type

int main()
{
    Database<SkipList> d;
    (void)d;
    return 0;
}
