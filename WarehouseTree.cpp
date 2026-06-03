#include "WarehouseTree.hpp"

#include <iostream>
#include <cstring>

using namespace std;

// allocate and set up a new tree node
WarehouseTree::TreeNode* WarehouseTree::createNode(const char name[], TreeNode* parent)
{
    TreeNode* node = new TreeNode;

    copyText(node->name, name, MAX_LOCATION_LENGTH);

    node->childCount = 0;
    node->parent = parent;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = nullptr;
    }

    return node;
}

// create a new node and attach it under the given parent
WarehouseTree::TreeNode* WarehouseTree::addChild(TreeNode* parentNode, const char name[])
{
    if (parentNode == nullptr) {
        cout << "Error: Parent node does not exist.\n";
        return nullptr;
    }

    if (parentNode->childCount >= MAX_CHILDREN) {
        cout << "Error: Maximum child limit reached for " << parentNode->name << ".\n";
        return nullptr;
    }

    TreeNode* child = createNode(name, parentNode);

    parentNode->children[parentNode->childCount] = child;
    parentNode->childCount++;

    return child;
}

// print the tree with indentation to show the hierarchy
void WarehouseTree::printTree(TreeNode* node, int depth) const
{
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        cout << "   ";
    }

    if (depth > 0) {
        cout << "|-- ";
    }

    cout << node->name << "\n";

    for (int i = 0; i < node->childCount; i++) {
        printTree(node->children[i], depth + 1);
    }
}

// depth-first search to find a node by name
WarehouseTree::TreeNode* WarehouseTree::findNode(TreeNode* node, const char name[]) const
{
    if (node == nullptr) {
        return nullptr;
    }

    if (strcmp(node->name, name) == 0) {
        return node;
    }

    for (int i = 0; i < node->childCount; i++) {
        TreeNode* found = findNode(node->children[i], name);

        if (found != nullptr) {
            return found;
        }
    }

    return nullptr;
}

// walk from a node up to the root collecting names, then reverse the array
// so the result goes from root down to the node
int WarehouseTree::buildPathToNode(TreeNode* node, char path[][MAX_LOCATION_LENGTH]) const
{
    if (node == nullptr) {
        return 0;
    }

    int count = 0;
    TreeNode* current = node;

    char tempPath[MAX_ROUTE_STEPS][MAX_LOCATION_LENGTH];

    // collect names going up toward the root
    while (current != nullptr && count < MAX_ROUTE_STEPS) {
        copyText(tempPath[count], current->name, MAX_LOCATION_LENGTH);
        count++;
        current = current->parent;
    }

    // reverse so the path goes top-down
    for (int i = 0; i < count; i++) {
        copyText(path[i], tempPath[count - 1 - i], MAX_LOCATION_LENGTH);
    }

    return count;
}

// recursively delete all nodes
void WarehouseTree::destroyTree(TreeNode* node)
{
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < node->childCount; i++) {
        destroyTree(node->children[i]);
    }

    delete node;
}

WarehouseTree::WarehouseTree()
{
    root = nullptr;
}

WarehouseTree::~WarehouseTree()
{
    destroyTree(root);
    root = nullptr;
}

// build the default warehouse layout with three zones, aisles, and shelves
void WarehouseTree::buildLayout()
{
    if (root != nullptr) {
        destroyTree(root);
        root = nullptr;
    }

    root = createNode("Warehouse", nullptr);

    // Zone A
    TreeNode* zoneA = addChild(root, "ZoneA");

    TreeNode* aisleA1 = addChild(zoneA, "AisleA1");
    addChild(aisleA1, "ShelfA1-1");
    addChild(aisleA1, "ShelfA1-2");
    addChild(aisleA1, "ShelfA1-3");

    TreeNode* aisleA2 = addChild(zoneA, "AisleA2");
    addChild(aisleA2, "ShelfA2-1");
    addChild(aisleA2, "ShelfA2-2");

    // Zone B
    TreeNode* zoneB = addChild(root, "ZoneB");

    TreeNode* aisleB1 = addChild(zoneB, "AisleB1");
    addChild(aisleB1, "ShelfB1-1");
    addChild(aisleB1, "ShelfB1-2");

    TreeNode* aisleB2 = addChild(zoneB, "AisleB2");
    addChild(aisleB2, "ShelfB2-1");
    addChild(aisleB2, "ShelfB2-2");
    addChild(aisleB2, "ShelfB2-3");

    // Zone C
    TreeNode* zoneC = addChild(root, "ZoneC");

    TreeNode* aisleC1 = addChild(zoneC, "AisleC1");
    addChild(aisleC1, "ShelfC1-1");
    addChild(aisleC1, "ShelfC1-2");

    TreeNode* aisleC2 = addChild(zoneC, "AisleC2");
    addChild(aisleC2, "ShelfC2-1");

    cout << "Warehouse layout built successfully.\n";
}

void WarehouseTree::displayLayout() const
{
    if (root == nullptr) {
        cout << "Warehouse layout has not been built yet. There is nothing here.\n";
        return;
    }

    cout << "\n--- Warehouse Layout ---\n";

    printTree(root, 0);
}

// find the path from each location to the root, then combine them at the common ancestor
bool WarehouseTree::generateRoute(const char from[], const char to[], Route& route)
{
    route.stepCount = 0;

    if (root == nullptr) {
        cout << "Error: Warehouse layout has not been built yet. There is nothing here.\n";
        return false;
    }

    TreeNode* sourceNode = findNode(root, from);
    TreeNode* destNode   = findNode(root, to);

    if (sourceNode == nullptr) {
        cout << "Error: Starting location not found.\n";
        return false;
    }

    if (destNode == nullptr) {
        cout << "Error: Destination location not found.\n";
        return false;
    }

    // same location, nothing to route
    if (strcmp(from, to) == 0) {
        copyText(route.steps[0], from, MAX_LOCATION_LENGTH);
        route.stepCount = 1;
        return true;
    }

    char sourcePath[MAX_ROUTE_STEPS][MAX_LOCATION_LENGTH];
    const int sourceSize = buildPathToNode(sourceNode, sourcePath);

    char destPath[MAX_ROUTE_STEPS][MAX_LOCATION_LENGTH];
    const int destSize = buildPathToNode(destNode, destPath);

    // find the deepest node that both paths share (common ancestor)
    int commonIndex = 0;
    const int smallerSize = sourceSize < destSize ? sourceSize : destSize;

    for (int i = 0; i < smallerSize; i++) {
        if (strcmp(sourcePath[i], destPath[i]) == 0) {
            commonIndex = i;
        } else {
            break;
        }
    }

    int stepIndex = 0;

    // go up from the start to the common ancestor
    for (int i = sourceSize - 1; i >= commonIndex; i--) {
        if (stepIndex >= MAX_ROUTE_STEPS) {
            cout << "Error: Route is too long.\n";
            route.stepCount = 0;
            return false;
        }

        copyText(route.steps[stepIndex], sourcePath[i], MAX_LOCATION_LENGTH);
        stepIndex++;
    }

    // go down from the common ancestor to the destination
    for (int i = commonIndex + 1; i < destSize; i++) {
        if (stepIndex >= MAX_ROUTE_STEPS) {
            cout << "Error: Route is too long.\n";
            route.stepCount = 0;
            return false;
        }

        copyText(route.steps[stepIndex], destPath[i], MAX_LOCATION_LENGTH);
        stepIndex++;
    }

    route.stepCount = stepIndex;

    cout << "Route generated successfully!\n";
    return true;
}

void WarehouseTree::displayRoute(const Route& route) const
{
    if (route.stepCount <= 0) {
        cout << "No route to display here.\n";
        return;
    }

    cout << "\n--- Generated Route ---\n";

    for (int i = 0; i < route.stepCount; i++) {
        cout << route.steps[i];

        if (i < route.stepCount - 1) {
            cout << " -> ";
        }
    }

    cout << "\n";
}

// just use findNode and check if the result is not null
bool WarehouseTree::locationExists(const char name[]) const
{
    return findNode(root, name) != nullptr;
}
