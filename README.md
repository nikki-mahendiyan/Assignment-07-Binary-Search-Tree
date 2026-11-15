# Binary Search Tree (Assignment 07)

A binary search tree of ints in C++17, written from scratch in a single file. It does not use std::set, std::map, or any other tree container.

## Files
- `main.cpp`: the `Node` struct, the `BinarySearchTree` class (insert, search, remove, inorder, preorder, postorder, height), and a demo of every required operation
- `output.txt`: the output from one run of the program

## Build and run
```
g++ -std=c++17 -Wall -Wextra -pedantic -o bst main.cpp
./bst
```

## Notes
- Duplicate keys are ignored.
- Height counts edges: an empty tree is -1, a single node is 0.
- Removing a node with two children copies in the inorder successor.
