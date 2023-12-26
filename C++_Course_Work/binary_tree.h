#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "TreeNode.h"
#include <fstream>
#include <string>
#include <iomanip>

class TreeNodeOrder;
class TreeNodeUser;

//extern std::string OrdersFileName = "../data/orders.bin";

//extern std::string UsersFileName = "../data/users.bin";

class BinaryTreeUser 
{
private:
    TreeNodeUser* root;

    TreeNodeUser* InsertUser(TreeNodeUser* node, User* user);
    void PrintUsersPrivate(TreeNodeUser* node, int* count);

    int SearchUsersPrivate(TreeNodeUser* node, const std::string& name, const std::string& password);
    int SearchUserNamePrivate(TreeNodeUser* node, const std::string& name);
    void SaveUsersToFilePrivate(TreeNodeUser* node, std::ofstream* outFile);

    void DeleteUserTreePrivate(TreeNodeUser* node);
    TreeNodeUser* DeleteUserNodePrivate(TreeNodeUser* node, int* count_to_find, int* count);
    TreeNodeUser* FindMinNode(TreeNodeUser* node);
    void EditUserNodePrivate(TreeNodeUser* node, int* count_to_find, int* count, BinaryTreeUser* tree);
    
    int GetNameNumberPrivate(TreeNodeUser* node, std::string s, int* count);
public:
    BinaryTreeUser();

    void LoadUsersFromFile(const std::string& filename);
    void SaveUsersToFile(const std::string& filename);
    int SearchUsers(const std::string& name, const std::string& password);
    int SearchUserName(const std::string& name);
    int GetNameNumber(std::string s);
    void Insert(User* user);
    void PrintUsers();
    void DeleteUserTree();
    void DeleteUserNode(int* count);
    void EditUserNode(int* count);
};


class BinaryTreeOrder {
private:
    TreeNodeOrder* root;

    TreeNodeOrder* InsertOrder(TreeNodeOrder* node, Order* order);
    void PrintOrdersPrivate(TreeNodeOrder* node, int* count);
    void PrintRepairingOrdersPrivate(TreeNodeOrder* node, int* count);
    void SearchOrdersByProductNamePrivate(TreeNodeOrder* node, const std::string& _product_name, int* count);

    void SaveOrdersToFilePrivate(TreeNodeOrder* node, std::ofstream* outFile);

    void DeleteOrderTreePrivate(TreeNodeOrder* node);
    TreeNodeOrder* DeleteOrderNodePrivate(TreeNodeOrder* node, int* count_to_find, int* count);
    TreeNodeOrder* FindMinNode(TreeNodeOrder* node);

    void EditOrderNodePrivate(TreeNodeOrder* node, int* count_to_find, int* count);
public:
    BinaryTreeOrder();

    void Insert(Order* order);
    void PrintOrders();
    void SaveOrdersToFile(const std::string& filename);
    void LoadOrdersFromFile(const std::string& filename);
    void PrintRepairingOrders();
    void SearchOrdersByProductName(const std::string& _product_name);
    void DeleteOrderTree();
    void DeleteOrderNode(int* count);
    void EditOrderNode(int* count);
};

#endif // !BINARY_TREE_H