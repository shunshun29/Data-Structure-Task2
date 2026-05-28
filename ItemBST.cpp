#include "ItemBST.hpp"

// ─── Constructor & Destructor ────────────────────────────────────────────────

ItemBST::ItemBST() : root(nullptr) {}

ItemBST::~ItemBST() {
    destroyTree(root);
}

// Recursively delete all nodes to free memory
void ItemBST::destroyTree(Node* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// ─── Insert ──────────────────────────────────────────────────────────────────

// Public insert: starts the recursive insertion from root
void ItemBST::insert(const Item& item) {
    root = insertHelper(root, item);
}

// Private helper: places the new item in the correct BST position by itemId
ItemBST::Node* ItemBST::insertHelper(Node* node, const Item& item) {
    // Base case: empty spot found, create new node here
    if (node == nullptr) {
        return new Node(item);
    }

    int cmp = strcmp(item.itemId, node->data.itemId);

    if (cmp < 0) {
        // New item ID is smaller → go left
        node->left = insertHelper(node->left, item);
    } else if (cmp > 0) {
        // New item ID is larger → go right
        node->right = insertHelper(node->right, item);
    } else {
        // Duplicate ID: update existing record
        cout << "[ItemBST] Item ID " << item.itemId << " already exists. Updating record." << endl;
        copyText(node->data.itemName, item.itemName, MAX_NAME_LENGTH);
        copyText(node->data.location, item.location, MAX_LOCATION_LENGTH);
    }

    return node;
}

// ─── Search by ID ─────────────────────────────────────────────────────────────

// Public search: returns true and fills result if found
bool ItemBST::search(const char itemId[], Item& result) const {
    Node* found = searchHelper(root, itemId);
    if (found != nullptr) {
        result = found->data;
        return true;
    }
    return false;
}

// Private helper: BST search — O(log n) average
ItemBST::Node* ItemBST::searchHelper(Node* node, const char itemId[]) const {
    // Base case: not found or exact match
    if (node == nullptr) return nullptr;
    if (strcmp(itemId, node->data.itemId) == 0) return node;

    if (strcmp(itemId, node->data.itemId) < 0) {
        // Target is smaller → search left subtree
        return searchHelper(node->left, itemId);
    } else {
        // Target is larger → search right subtree
        return searchHelper(node->right, itemId);
    }
}

// ─── Search by Name ───────────────────────────────────────────────────────────

// Public searchByName: traverses entire tree since names are not sorted
bool ItemBST::searchByName(const char name[], Item& result) const {
    bool found = false;
    searchByNameHelper(root, name, result, found);
    return found;
}

// Private helper: full in-order traversal to find by name
void ItemBST::searchByNameHelper(Node* node, const char name[], Item& result, bool& found) const {
    if (node == nullptr || found) return;

    searchByNameHelper(node->left, name, result, found);

    // Case-sensitive name comparison
    if (strcmp(name, node->data.itemName) == 0) {
        result = node->data;
        found = true;
        return;
    }

    searchByNameHelper(node->right, name, result, found);
}

// ─── Display (In-Order) ───────────────────────────────────────────────────────

// Public display: prints all items sorted by itemId (in-order = sorted for BST)
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

// Private helper: left → root → right traversal
void ItemBST::inOrderHelper(Node* node) const {
    if (node == nullptr) return;
    inOrderHelper(node->left);
    cout << "ID       : " << node->data.itemId   << endl;
    cout << "Name     : " << node->data.itemName  << endl;
    cout << "Location : " << node->data.location  << endl;
    cout << "-------------------------------------------" << endl;
    inOrderHelper(node->right);
}

// ─── Remove ───────────────────────────────────────────────────────────────────

// Public remove: returns true if item was found and deleted
bool ItemBST::remove(const char itemId[]) {
    bool removed = false;
    root = removeHelper(root, itemId, removed);
    return removed;
}

// Private helper: handles 3 BST deletion cases
ItemBST::Node* ItemBST::removeHelper(Node* node, const char itemId[], bool& removed) {
    if (node == nullptr) return nullptr;  // Item not found

    int cmp = strcmp(itemId, node->data.itemId);

    if (cmp < 0) {
        node->left = removeHelper(node->left, itemId, removed);
    } else if (cmp > 0) {
        node->right = removeHelper(node->right, itemId, removed);
    } else {
        // Found the node to delete
        removed = true;

        if (node->left == nullptr) {
            // Case 1: No left child → replace with right child
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            // Case 2: No right child → replace with left child
            Node* temp = node->left;
            delete node;
            return temp;
        } else {
            // Case 3: Two children → replace with in-order successor (smallest in right subtree)
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = removeHelper(node->right, successor->data.itemId, removed);
        }
    }
    return node;
}

// Find leftmost (smallest) node in a subtree
ItemBST::Node* ItemBST::findMin(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
