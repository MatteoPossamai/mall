# Commands

List of useful commands to run on the repository.

## `cmake`

### Configure

Run every time `CmakeLists.txt` changes.

```shell
cmake -S . -B build
```

- `-S` as source directory
- `-B` as build directory

### Build

Run every time code changes.

```shell
cmake --build build
```

### Test

Run every time you need to test.

```shell
ctest --test-dir build
```
