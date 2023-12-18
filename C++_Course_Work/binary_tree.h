#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "TreeNode.h"
//#include "order.h"
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
    void SaveUsersToFilePrivate(TreeNodeUser* node, std::ofstream* outFile);

    void DeleteUserTreePrivate(TreeNodeUser* node);
    TreeNodeUser* DeleteUserNodePrivate(TreeNodeUser* node, int* count_to_find, int* count);
    TreeNodeUser* FindMinNode(TreeNodeUser* node);
    void EditUserNodePrivate(TreeNodeUser* node, int* count_to_find, int* count);
public:
    BinaryTreeUser();
    //~BinaryTreeUser();

    void LoadUsersFromFile(const std::string& filename);
    void SaveUsersToFile(const std::string& filename);
    int SearchUsers(const std::string& name, const std::string& password);
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
    //~BinaryTreeUser();

    void Insert(Order* order);
    void PrintOrders();
    void SaveOrdersToFile(const std::string& filename);
    void LoadOrdersFromFile(const std::string& filename);
    void PrintRepairingOrders();
    void SearchOrdersByProductName(const std::string& _product_name);
    void DeleteOrderTree();
    void DeleteOrderNode(int* count);
    void EditOrderNode(int* count);
    //TreeNodeOrder* GetRoot();
    //void SetRoot(TreeNodeOrder* data);
};

struct Node
{
	Order data;
	Node* left;
	Node* right;
};
struct NodeUser
{
	User data;
	NodeUser* left;
	NodeUser* right;
};

Node* CreateNode(const Order& order);
NodeUser* CreateNode(const User& user);
Node* InsertNode(Node* root, Order& order);
NodeUser* InsertNode(NodeUser* root, User& user);
void PrintOrdersByAcceptanceDate(Node* root);
void PrintRepairingOrders(Node* root);
void SearchOrdersByProductName(Node* root, const std::string& _product_name);
void SaveOrdersToFile(Node* root, const std::string& filename);
void SaveUsersToFile(NodeUser* root, const std::string& filename);
Node* LoadOrdersFromFile(const std::string& filename);
NodeUser* LoadUsersFromFile(const std::string& filename);
void SearchUsers(NodeUser* root, const std::string& name, const std::string& password);
#endif // !BINARY_TREE_H