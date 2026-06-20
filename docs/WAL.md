# WAL

Write Ahead Log. Short design and principles.

## Usage

Fast, on disk storage of transactions coming in, for replayability reasons.

## Features

- Fast to write into
    - Achieved by appending at the end of a file
- Easy to parse
    - Achieved by adding paddings on every element
- Checkpoint-able
    - Achieved by numerating the indexes at the end, enabling parsing the file
- Multiple segments (remove older transactions)
    - Achieved by keeping track of indexes and establishing max number of segments M

## Design

We will have different segments of the  WAL. These will be ordered by their file name. So for example:

```shell
0001.log
0002.log
...
```

Each segment will have a max number of  entries, that we can define as M.
The first entry is the top of the file. The last entry is the bottom of the file.
The number of entries will be kept in memory, and when M is reached, a new log file is rolled.
At the end of a segment, there are two numbers saying the index of the first and the last segment that is stored there. This so that once a `memtable` if flushed into memory, we can get the highest number that is permanently stored and start to collect segments that do contain everything before. We add numbers in the end so that is faster to append and know where they are. 

The fact that we add to the logs at the end of a file makes the operation as fast as possible to store something permanently, and makes it linear to parse as well.

## File format

A log file will look something like

```shell
--- SEGMENT ---
--- SEGMENT ---
--- SEGMENT ---
--- SEGMENT ---
START_SEGMENT_IDX
END_SEGMENT_IDX
```

## Segment format

```shell
<0|1>\0<KEY_SIZE>\0<KEY_VALUE>\0<VALUE_SIZE>\0<VALUE_VALUE>\n
```

Where:
- `0/1` represents if the operation is a put (`0`) or a delete (`1`)
- `KEY_SIZE` is the number of bytes of the key
- `KEY_VALUE` is the key
- `VALUE_SIZE` is the number of bytes of the value
- `VALUE_VALUE` is the value