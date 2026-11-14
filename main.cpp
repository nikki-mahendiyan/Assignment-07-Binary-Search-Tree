// AI was used to help write this code
// main.cpp
// Demo and tests for the BinarySearchTree in bst.h

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void printList(const std::string& label, const std::vector<int>& v) {
    std::cout << label;
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << " ";
    }
    std::cout << "\n";
}

bool isSorted(const std::vector<int>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i - 1] >= v[i]) return false;  // strict, no duplicates allowed
    }
    return true;
}

void showTree(const BinarySearchTree& t) {
    printList("  inorder:   ", t.inorder());
    printList("  preorder:  ", t.preorder());
    printList("  postorder: ", t.postorder());
    std::cout << "  height:    " << t.height() << "\n";
    std::cout << "  inorder sorted? " << (isSorted(t.inorder()) ? "yes" : "NO") << "\n";
}

// removes a key, prints what happened, and checks inorder is still sorted
void removeAndShow(BinarySearchTree& t, int key, const std::string& caseName) {
    std::cout << "\nRemove " << key << " (" << caseName << ")\n";
    bool ok = t.remove(key);
    std::cout << "  remove returned " << (ok ? "true" : "false") << "\n";
    showTree(t);
    std::cout << "  tree shape (sideways):\n";
    t.printSideways();
}

int main() {
    BinarySearchTree tree;

    // ---- insertion: 11 distinct integers ----
    int keys[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 85};
    std::cout << "=== Insert 11 distinct keys ===\n";
    for (int k : keys) {
        tree.insert(k);
    }
    showTree(tree);
    std::cout << "  tree shape (sideways):\n";
    tree.printSideways();

    std::cout << "\nInsert 50 again (duplicate): returned "
              << (tree.insert(50) ? "true" : "false") << "\n";

    // ---- search ----
    std::cout << "\n=== Search ===\n";
    std::cout << "search(60) = " << (tree.search(60) ? "found" : "not found") << "\n";
    std::cout << "search(99) = " << (tree.search(99) ? "found" : "not found") << "\n";

    // ---- removal, all three cases ----
    std::cout << "\n=== Removal ===\n";
    removeAndShow(tree, 45, "case 1: leaf");
    removeAndShow(tree, 60, "case 2: one child (65)");
    removeAndShow(tree, 50, "case 3: two children, the root");
    removeAndShow(tree, 99, "key not in the tree");

    // ---- worst case shape ----
    std::cout << "\n=== Worst case: keys inserted in sorted order ===\n";
    BinarySearchTree chain;
    for (int i = 1; i <= 10; i++) {
        chain.insert(i);
    }
    std::cout << "  inserted 1..10 in order\n";
    std::cout << "  height: " << chain.height() << " (n - 1 = 9, it is a linked list)\n";

    // ---- extra check: random operations against a sorted vector ----
    std::cout << "\n=== Random check against a sorted vector ===\n";
    BinarySearchTree t;
    std::vector<int> model;  // kept sorted by hand, no duplicates
    std::srand(12345);
    int bad = 0;
    for (int step = 0; step < 5000; step++) {
        int key = std::rand() % 200;
        bool inModel = std::binary_search(model.begin(), model.end(), key);
        if (std::rand() % 2 == 0) {
            bool added = t.insert(key);
            if (added == inModel) bad++;
            if (!inModel) {
                model.insert(std::lower_bound(model.begin(), model.end(), key), key);
            }
        } else {
            bool removed = t.remove(key);
            if (removed != inModel) bad++;
            if (inModel) {
                model.erase(std::lower_bound(model.begin(), model.end(), key));
            }
        }
        if (t.search(key) != std::binary_search(model.begin(), model.end(), key)) bad++;
        if (t.inorder() != model) bad++;
    }
    std::cout << "  5000 random inserts/removes, mismatches: " << bad << "\n";
    std::cout << "  final size: " << model.size() << ", final height: " << t.height() << "\n";

    return bad == 0 ? 0 : 1;
}
