# Mall

Goal: write a key value store for didactic purpuses.

## TODO

### Memtables

- [X] RedBlackTree
- [X] Skip List
- [X] Interface for them (Memtable)
- [ ] Benchmark + profile
- [ ] Optimize

### WAL

- [X] Binary File encoding for data
- [ ] Log manager
    - [ ] Store on entry -> Forward to Memtable
    - [ ] Replay from a given step