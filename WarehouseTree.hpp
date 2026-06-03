#pragma once

#include "common.hpp"

const int MAX_CHILDREN = 10;  // max child nodes per location

// tree structure that represents the warehouse layout
// warehouse -> zones -> aisles -> shelves
// each node stores its parent pointer so we can build routes by walking up the tree
class WarehouseTree {
private:
    struct TreeNode {
        char name[MAX_LOCATION_LENGTH];
        TreeNode* children[MAX_CHILDREN];
        int childCount;
        TreeNode* parent;  // used when building a route path
    };

    TreeNode* root;

    TreeNode* createNode(const char name[], TreeNode* parent);
    TreeNode* addChild(TreeNode* parentNode, const char name[]);
    void printTree(TreeNode* node, int depth) const;
    TreeNode* findNode(TreeNode* node, const char name[]) const;  // DFS search
    int buildPathToNode(TreeNode* node, char path[][MAX_LOCATION_LENGTH]) const;
    void destroyTree(TreeNode* node);

public:
    WarehouseTree();
    ~WarehouseTree();

    void buildLayout();
    void displayLayout() const;
    bool generateRoute(const char from[], const char to[], Route& route);
    void displayRoute(const Route& route) const;
    bool locationExists(const char name[]) const;  // check if a location is in the tree
};
