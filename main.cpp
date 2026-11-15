// AI was used to help write this code
// main.cpp
// Binary search tree of ints, written from scratch (no std::set or std::map).
// Duplicate keys are ignored.
// Height counts edges: an empty tree is -1, a single node is 0.

#include <algorithm>
#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root = nullptr;

    static Node* insert(Node* node, int value) {
        if (node == nullptr) return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;  // equal value: ignore the duplicate
    }

    static bool search(const Node* node, int value) {
        if (node == nullptr) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    static Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // returns the new root of this subtree after the removal
    static Node* remove(Node* node, int value) {
        if (node == nullptr) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
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

            // case 3: two children, copy in the inorder successor
            // (smallest value on the right), then remove that successor
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }

        return node;
    }

    static void inorder(const Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << ' ';
        inorder(node->right);
    }

    static void preorder(const Node* node) {
        if (node == nullptr) return;
        std::cout << node->data << ' ';
        preorder(node->left);
        preorder(node->right);
    }

    static void postorder(const Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << ' ';
    }

    static int height(const Node* node) {
        if (node == nullptr) return -1;
        return 1 + std::max(height(node->left), height(node->right));
    }

    static void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BinarySearchTree() {}
    ~BinarySearchTree() { clear(root); }

    // The tree owns raw pointers, so copying would delete nodes twice.
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    void insert(int value) { root = insert(root, value); }
    bool search(int value) const { return search(root, value); }
    void remove(int value) { root = remove(root, value); }
    void inorder() const { inorder(root); std::cout << '\n'; }
    void preorder() const { preorder(root); std::cout << '\n'; }
    void postorder() const { postorder(root); std::cout << '\n'; }
    int height() const { return height(root); }
};

int main() {
    BinarySearchTree tree;
    const int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};

    std::cout << "Inserted: ";
    for (int value : values) {
        tree.insert(value);
        std::cout << value << ' ';
    }
    std::cout << '\n';

    std::cout << "Inorder: "; tree.inorder();
    std::cout << "Preorder: "; tree.preorder();
    std::cout << "Postorder: "; tree.postorder();
    std::cout << "Height (edges): " << tree.height() << '\n';

    std::cout << "\nSearch 60: " << (tree.search(60) ? "found" : "not found") << '\n';
    std::cout << "Search 99: " << (tree.search(99) ? "found" : "not found") << '\n';

    std::cout << "\nRemove 45 (leaf)\n";
    tree.remove(45);
    std::cout << "Inorder: "; tree.inorder();

    std::cout << "\nRemove 60 (one child: 65)\n";
    tree.remove(60);
    std::cout << "Inorder: "; tree.inorder();

    std::cout << "\nRemove 50 (two children: 30 and 70, the root)\n";
    tree.remove(50);
    std::cout << "Inorder: "; tree.inorder();
    std::cout << "Preorder: "; tree.preorder();

    std::cout << "\nRemove 99 (not in the tree)\n";
    tree.remove(99);
    std::cout << "Inorder: "; tree.inorder();
    std::cout << "Final height (edges): " << tree.height() << '\n';

    // worst case: keys inserted in sorted order make a chain
    BinarySearchTree chain;
    for (int i = 1; i <= 10; i++) chain.insert(i);
    std::cout << "\nKeys 1..10 inserted in order, height (edges): " << chain.height() << '\n';

    return 0;
}
