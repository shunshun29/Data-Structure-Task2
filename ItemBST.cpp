#include "ItemBST.hpp"

ItemBST::ItemBST() : root(nullptr) {}

ItemBST::~ItemBST() {
    destroyTree(root);
}

// delete all nodes to free memory
void ItemBST::destroyTree(Node* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// kick off the recursive insert from the root
void ItemBST::insert(const Item& item) {
    root = insertHelper(root, item);
}

// smaller IDs go left, larger go right
// if the same ID already exists, update it instead of inserting a duplicate
ItemBST::Node* ItemBST::insertHelper(Node* node, const Item& item) {
    if (node == nullptr) {
        return new Node(item);
    }

    int cmp = strcmp(item.itemId, node->data.itemId);

    if (cmp < 0) {
        node->left = insertHelper(node->left, item);
    } else if (cmp > 0) {
        node->right = insertHelper(node->right, item);
    } else {
        // duplicate ID, update the existing entry
        cout << "[ItemBST] Item ID " << item.itemId << " already exists. Updating record." << endl;
        copyText(node->data.itemName, item.itemName, MAX_NAME_LENGTH);
        copyText(node->data.location, item.location, MAX_LOCATION_LENGTH);
    }

    return node;
}

// start the search from the root
bool ItemBST::search(const char itemId[], Item& result) const {
    Node* found = searchHelper(root, itemId);
    if (found != nullptr) {
        result = found->data;
        return true;
    }
    return false;
}

// walk left or right based on string comparison until found or not found
ItemBST::Node* ItemBST::searchHelper(Node* node, const char itemId[]) const {
    if (node == nullptr) return nullptr;
    if (strcmp(itemId, node->data.itemId) == 0) return node;

    if (strcmp(itemId, node->data.itemId) < 0) {
        return searchHelper(node->left, itemId);
    } else {
        return searchHelper(node->right, itemId);
    }
}

// names are not sorted so we have to check every node
bool ItemBST::searchByName(const char name[], Item& result) const {
    bool found = false;
    searchByNameHelper(root, name, result, found);
    return found;
}

// traverse the whole tree and compare each name
void ItemBST::searchByNameHelper(Node* node, const char name[], Item& result, bool& found) const {
    if (node == nullptr || found) return;

    searchByNameHelper(node->left, name, result, found);

    if (strcmp(name, node->data.itemName) == 0) {
        result = node->data;
        found = true;
        return;
    }

    searchByNameHelper(node->right, name, result, found);
}

// in-order traversal prints items sorted by ID because of how the BST is built
void ItemBST::displayInOrder() const {
    if (root == nullptr) {
        cout << "[ItemBST] No items in the system." << endl;
        return;
    }
    cout << "\n===== Item List (Sorted by Item ID) =====" << endl;
    cout << "-------------------------------------------" << endl;
    inOrderHelper(root);
    cout << "-------------------------------------------" << endl;
}

// left subtree first, then current node, then right subtree
void ItemBST::inOrderHelper(Node* node) const {
    if (node == nullptr) return;
    inOrderHelper(node->left);
    cout << "ID       : " << node->data.itemId   << endl;
    cout << "Name     : " << node->data.itemName  << endl;
    cout << "Location : " << node->data.location  << endl;
    cout << "-------------------------------------------" << endl;
    inOrderHelper(node->right);
}

bool ItemBST::remove(const char itemId[]) {
    bool removed = false;
    root = removeHelper(root, itemId, removed);
    return removed;
}

// three cases: no left child, no right child, or two children
ItemBST::Node* ItemBST::removeHelper(Node* node, const char itemId[], bool& removed) {
    if (node == nullptr) return nullptr;

    int cmp = strcmp(itemId, node->data.itemId);

    if (cmp < 0) {
        node->left = removeHelper(node->left, itemId, removed);
    } else if (cmp > 0) {
        node->right = removeHelper(node->right, itemId, removed);
    } else {
        removed = true;

        if (node->left == nullptr) {
            // no left child, just connect the right child up
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            // no right child, just connect the left child up
            Node* temp = node->left;
            delete node;
            return temp;
        } else {
            // two children: replace this node with the in-order successor
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = removeHelper(node->right, successor->data.itemId, removed);
        }
    }
    return node;
}

// keep going left until there is no more left child
ItemBST::Node* ItemBST::findMin(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
