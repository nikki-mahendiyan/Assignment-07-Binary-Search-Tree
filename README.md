# Assignment-07-Binary-Search-Tree
# Binary Search Tree (Assignment 07)

A binary search tree of ints in C++17, written from scratch. It does not use std::set, std::map, or any other tree container.

## Files
- `bst.h`: the `Node` struct and the `BinarySearchTree` class (insert, search, remove, inorder, preorder, postorder, height)
- `main.cpp`: demo of every required operation, plus a random test that checks the tree against a sorted vector
- `output.txt`: the output from one run of the program

## Build and run
```
g++ -std=c++17 -Wall -Wextra -pedantic -o bst main.cpp
./bst
```

The program exits with 0 if all the checks pass.

## Notes
- Duplicate keys are ignored (insert returns false).
- Height of an empty tree is -1, height of a single node is 0.
- Removal with two children copies in the inorder successor.
