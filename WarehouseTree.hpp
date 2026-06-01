#pragma once

#include "common.hpp"

// maximum num of child locations for each node
const int MAX_CHILDREN = 10;

class WarehouseTree {
private:
    // represents one location in the warehouse
    struct TreeNode {
        char name[MAX_LOCATION_LENGTH];
        TreeNode* children[MAX_CHILDREN];
        int childCount;
        TreeNode* parent;
    };

    TreeNode* root;

    TreeNode* createNode(const char name[], TreeNode* parent);

    TreeNode* addChild(TreeNode* parentNode, const char name[]);

    void printTree(TreeNode* node, int depth) const;

    TreeNode* findNode(TreeNode* node, const char name[]) const;

    int buildPathToNode(TreeNode* node, char path[][MAX_LOCATION_LENGTH]) const;

    void destroyTree(TreeNode* node);

public:
    WarehouseTree();
    ~WarehouseTree();

    WarehouseTree(const WarehouseTree&) = delete;
    WarehouseTree& operator=(const WarehouseTree&) = delete;

    void buildLayout();

    void displayLayout() const;

    bool generateRoute(const char from[], const char to[], Route& route);

    void displayRoute(const Route& route) const;
};
