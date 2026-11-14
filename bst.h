// bst.h
// Binary search tree of ints, written from scratch (no std::set / std::map).
// Duplicate keys are not stored: insert returns false if the key already exists.
// Height convention: an empty tree has height -1, a single node has height 0.

#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        destroy(root);
    }

    // The tree owns raw pointers, so copying would double delete.
    // I am turning copying off instead of writing a deep copy.
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // returns true if the key was added, false if it was already there
    bool insert(int key) {
        bool added = false;
        root = insertAt(root, key, added);
        return added;
    }

    bool search(int key) const {
        Node* cur = root;
        while (cur != nullptr) {
            if (key == cur->key) {
                return true;
            }
            if (key < cur->key) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return false;
    }

    // returns true if the key was found and removed
    bool remove(int key) {
        bool removed = false;
        root = removeAt(root, key, removed);
        return removed;
    }

    std::vector<int> inorder() const {
        std::vector<int> out;
        inorderAt(root, out);
        return out;
    }

    std::vector<int> preorder() const {
        std::vector<int> out;
        preorderAt(root, out);
        return out;
    }

    std::vector<int> postorder() const {
        std::vector<int> out;
        postorderAt(root, out);
        return out;
    }

    int height() const {
        return heightAt(root);
    }

    bool empty() const {
        return root == nullptr;
    }

    // prints the tree sideways: right subtree on top, root on the left
    void printSideways() const {
        printAt(root, 0);
    }

private:
    Node* root;

    static Node* insertAt(Node* node, int key, bool& added) {
        if (node == nullptr) {
            added = true;
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insertAt(node->left, key, added);
        } else if (key > node->key) {
            node->right = insertAt(node->right, key, added);
        }
        // equal key: do nothing, added stays false
        return node;
    }

    static Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // returns the new root of this subtree after the removal
    static Node* removeAt(Node* node, int key, bool& removed) {
        if (node == nullptr) {
            return nullptr;  // key not in the tree
        }

        if (key < node->key) {
            node->left = removeAt(node->left, key, removed);
        } else if (key > node->key) {
            node->right = removeAt(node->right, key, removed);
        } else {
            removed = true;

            // case 1: leaf
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // case 2: one child, the child takes this node's place
            if (node->left == nullptr) {
                Node* child = node->right;
                delete node;
                return child;
            }
            if (node->right == nullptr) {
                Node* child = node->left;
                delete node;
                return child;
            }
            // case 3: two children
            // copy the inorder successor (smallest key on the right) into this node,
            // then delete that successor from the right subtree
            Node* successor = findMin(node->right);
            node->key = successor->key;
            bool ignore = false;
            node->right = removeAt(node->right, successor->key, ignore);
        }
        return node;
    }

    static void inorderAt(Node* node, std::vector<int>& out) {
        if (node == nullptr) return;
        inorderAt(node->left, out);
        out.push_back(node->key);
        inorderAt(node->right, out);
    }

    static void preorderAt(Node* node, std::vector<int>& out) {
        if (node == nullptr) return;
        out.push_back(node->key);
        preorderAt(node->left, out);
        preorderAt(node->right, out);
    }

    static void postorderAt(Node* node, std::vector<int>& out) {
        if (node == nullptr) return;
        postorderAt(node->left, out);
        postorderAt(node->right, out);
        out.push_back(node->key);
    }

    static int heightAt(Node* node) {
        if (node == nullptr) return -1;
        int lh = heightAt(node->left);
        int rh = heightAt(node->right);
        return 1 + (lh > rh ? lh : rh);
    }

    static void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    static void printAt(Node* node, int depth) {
        if (node == nullptr) return;
        printAt(node->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            std::cout << "    ";
        }
        std::cout << node->key << "\n";
        printAt(node->left, depth + 1);
    }
};

#endif
