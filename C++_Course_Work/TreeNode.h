#pragma once
#ifndef TREENODE_H
#define TREENODE_H


#include "user.h"
#include "order.h"

class TreeNodeUser {
public:
    User* data;
    TreeNodeUser* left;
    TreeNodeUser* right;

    TreeNodeUser(User* data);
};

class TreeNodeOrder {
public:
    Order* data;
    TreeNodeOrder* left;
    TreeNodeOrder* right;

    TreeNodeOrder(Order* data);
};
#endif // !TREENODE_H