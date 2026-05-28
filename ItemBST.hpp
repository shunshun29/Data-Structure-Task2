#ifndef ITEMBST_HPP
#define ITEMBST_HPP

#include "common.hpp"

class ItemBST {
private:
    struct Node {
        Item data;
        Node* left;
        Node* right;
        Node(const Item& item) : data(item), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Private helper functions
    Node* insertHelper(Node* node, const Item& item);
    Node* searchHelper(Node* node, const char itemId[]) const;
    void searchByNameHelper(Node* node, const char name[], Item& result, bool& found) const;
    void inOrderHelper(Node* node) const;
    Node* removeHelper(Node* node, const char itemId[], bool& removed);
    Node* findMin(Node* node) const;
    void destroyTree(Node* node);

public:
    ItemBST();
    ~ItemBST();

    void insert(const Item& item);
    bool search(const char itemId[], Item& result) const;
    bool searchByName(const char name[], Item& result) const;
    void displayInOrder() const;
    bool remove(const char itemId[]);
};

#endif
