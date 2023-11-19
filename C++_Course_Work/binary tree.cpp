#include "binary_tree.h"

Node* CreateNode(const Order& order)
{
    Node* newNode = new Node;
    newNode->data = order;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* InsertNode(Node* root, Order& order)
{
    if (root == nullptr)
    {
        return CreateNode(order);
    }
    if (order.GetAcceptanceDate() < root->data.GetAcceptanceDate()) {
        root->left = InsertNode(root->left, order);
    }
    else {
        root->right = InsertNode(root->right, order);
    }
    return root;
}

void PrintOrdersByAcceptanceDate(Node* root)
{
    if (root != nullptr) 
    {
        PrintOrdersByAcceptanceDate(root->left);
        std::cout << "Product: " << root->data.GetProductName() << ", Acceptance Date: " << root->data.GetAcceptanceDate() << std::endl;
        PrintOrdersByAcceptanceDate(root->right);
    }
}

void PrintRepairingOrders(Node* root)
{
    if (root != nullptr)
    {
        PrintRepairingOrders(root->left);
        if (!root->data.GetStatus())
        {
            std::cout << "Product: " << root->data.GetProductName() << ", Issue Date: " << root->data.GetIssueDate() << std::endl;
        }
        PrintRepairingOrders(root->right);
    }
}

void SearchOrdersByProductName(Node* root, const std::string& _product_name)
{
    if (root != nullptr) {
        SearchOrdersByProductName(root->left, _product_name);
        if (root->data.GetProductName().find(_product_name) != std::string::npos) {
            std::cout << "Product: " << root->data.GetProductName() << ", Owner: " << root->data.GetOwnerFullName() << std::endl;
        }
        SearchOrdersByProductName(root->right, _product_name);
    }
}

void SaveOrdersToFile(Node* root, const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary | std::ios::out);
    if (outFile.is_open()) {
        if (root != nullptr) {
            outFile.write(reinterpret_cast<const char*>(&root->data), sizeof(Order));
            SaveOrdersToFile(root->left, filename);
            SaveOrdersToFile(root->right, filename);
        }
        outFile.close();
    }
    else {
        std::cout << "Failed to open the file for writing." << std::endl;
    }
}

Node* LoadOrdersFromFile(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary | std::ios::in);
    if (inFile.is_open()) {
        Node* root = nullptr;
        while (!inFile.eof()) {
            Order order;
            inFile.read(reinterpret_cast<char*>(&order), sizeof(Order));
            if (inFile.gcount() > 0) {
                root = InsertNode(root, order);
            }
        }
        inFile.close();
        return root;
    }
    else {
        std::cout << "Failed to open the file for reading." << std::endl;
        return nullptr;
    }
}
