#include "binary_tree.h"

Node* CreateNode(const Order& order)
{
    Node* newNode = new Node;
    newNode->data = order;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

NodeUser* CreateNode(const User& user)
{
    NodeUser* newNode = new NodeUser;
    newNode->data = user;
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

NodeUser* InsertNode(NodeUser* root, User& user)
{
    if (root == nullptr)
    {
        return CreateNode(user);
    }
    if (user.GetLogin() < root->data.GetLogin()) {
        root->left = InsertNode(root->left, user);
    }
    else {
        root->right = InsertNode(root->right, user);
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

void SearchUsers(NodeUser* root, const std::string& name, const std::string& password)
{
    if (root != nullptr) {
        SearchUsers(root->left, name, password);
        int found_position_name = root->data.GetLogin().find(name);
        int found_position_password = root->data.GetPassword().find(password);
        if ((found_position_name != string::npos && found_position_name + name.length() == root->data.GetLogin().length())
            && (found_position_password != string::npos && found_position_password + password.length() == root->data.GetPassword().length()))
        {
            std::cout << "Login: " << root->data.GetLogin() << "Password: " << root->data.GetPassword() << "Is Admin: " << root->data.GetIsAdmin() << std::endl;
        }
        SearchUsers(root->right, name, password);
    }
}

void SaveOrdersToFile(Node* root, const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary | std::ios::out);
    if (outFile.is_open()) 
    {
        if (root != nullptr)
        {
            // Запись _product_name
            int product_name_size = (root->data).GetProductName().size();
            outFile.write(reinterpret_cast<char*>(&product_name_size), sizeof(int));
            outFile.write(root->data.GetProductName().c_str(), product_name_size);

            // Запись _product_brand
            int product_brand_size = (root->data).GetProductBrand().size();
            outFile.write(reinterpret_cast<char*>(&product_brand_size), sizeof(int));
            outFile.write(root->data.GetProductBrand().c_str(), product_brand_size);

            // Запись _owner_full_name
            int owner_full_name_size = root->data.GetOwnerFullName().size();
            outFile.write(reinterpret_cast<char*>(&owner_full_name_size), sizeof(int));
            outFile.write(root->data.GetOwnerFullName().c_str(), owner_full_name_size);

            // Запись _owner_phone_number
            int owner_phone_number_size = root->data.GetOwnerPhoneNumber().size();
            outFile.write(reinterpret_cast<char*>(&owner_phone_number_size), sizeof(int));
            outFile.write(root->data.GetOwnerPhoneNumber().c_str(), owner_phone_number_size);

            // Запись _repair_cost
            //outFile.write(reinterpret_cast<char*>(&((&(root->data))->GetRepairCost())), sizeof(double));
            double temp = root->data.GetRepairCost();
            outFile.write(reinterpret_cast<char*>(&temp), sizeof(double));
            //std::cout << root->data.GetRepairCost();
            // Запись _acceptance_date
            int acceptance_date_size = root->data.GetAcceptanceDate().size();
            outFile.write(reinterpret_cast<char*>(&acceptance_date_size), sizeof(int));
            outFile.write(root->data.GetAcceptanceDate().c_str(), acceptance_date_size);

            // Запись _issue_date
            int issue_date_size = root->data.GetIssueDate().size();
            outFile.write(reinterpret_cast<char*>(&issue_date_size), sizeof(int));
            outFile.write(root->data.GetIssueDate().c_str(), issue_date_size);

            // Запись _status
            bool temp2 = root->data.GetStatus();
            outFile.write(reinterpret_cast<char*>(&temp2), sizeof(bool));

            SaveOrdersToFile(root->left, filename);
            SaveOrdersToFile(root->right, filename);

            outFile.close();
            std::cout << "Data has been written to the file." << std::endl;
        }
    }
    else {
        std::cout << "Failed to open the file for writing." << std::endl;
    }
}
    /*if (outFile.is_open()) {
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
}*/

Node* LoadOrdersFromFile(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary | std::ios::in);
    if (inFile.is_open()) 
    {
        Node* root = nullptr;
        while (inFile.good())
        {
            Order order;
            // Чтение _product_name
            int buf_size;
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            std::string buf;
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order.SetProductName(buf);

            // Read _product_brand
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order.SetProductBrand(buf);

            // Read _owner_full_name
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order.SetOwnerFullName(buf);

            // Read _owner_phone_number
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order.SetOwnerPhoneNumber(buf);

            // Read _repair_cost
            double temp_double;
            inFile.read(reinterpret_cast<char*>(&temp_double), sizeof(double));
            order.SetRepairCost(temp_double);

            // Read _acceptance_date
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order.SetAcceptanceDate(buf);

            // Read _issue_date
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order.SetIssueDate(buf);

            // Read _issue_date
            bool temp_bool;
            inFile.read(reinterpret_cast<char*>(&temp_bool), sizeof(bool));
            order.SetStatus(temp_bool);

            root = InsertNode(root, order);
        }
        inFile.close();
        return root;
        //// Чтение _product_brand
        //int product_brand_size;
        //inFile.read(reinterpret_cast<char*>(&product_brand_size), sizeof(int));
        //_product_brand.resize(product_brand_size);
        //inFile.read(&_product_brand[0], product_brand_size);

        //// Чтение _owner_full_name
        //int owner_full_name_size;
        //inFile.read(reinterpret_cast<char*>(&owner_full_name_size), sizeof(int));
        //_owner_full_name.resize(owner_full_name_size);
        //inFile.read(&_owner_full_name[0], owner_full_name_size);

        //// Чтение _owner_phone_number
        //int owner_phone_number_size;
        //inFile.read(reinterpret_cast<char*>(&owner_phone_number_size), sizeof(int));
        //_owner_phone_number.resize(owner_phone_number_size);
        //inFile.read(&_owner_phone_number[0], owner_phone_number_size);

        //// Чтение _repair_cost
        //inFile.read(reinterpret_cast<char*>(&_repair_cost), sizeof(double));

        //// Чтение _acceptance_date
        //int acceptance_date_size;
        //inFile.read(reinterpret_cast<char*>(&acceptance_date_size), sizeof(int));
        //_acceptance_date.resize(acceptance_date_size);
        //inFile.read(&_acceptance_date[0], acceptance_date_size);

        //// Чтение _issue_date
        //int issue_date_size;
        //inFile.read(reinterpret_cast<char*>(&issue_date_size), sizeof(int));
        //_issue_date.resize(issue_date_size);
        //inFile.read(&_issue_date[0], issue_date_size);

        //// Чтение _status
        //inFile.read(reinterpret_cast<char*>(&_status), sizeof(bool));

        //inFile.close();
        //std::cout << "Data has been read from the file." << std::endl;
    }
    else {
        std::cout << "Failed to open the file for reading." << std::endl;
    }
    /*if (inFile.is_open())
    {
        Node* root = nullptr;
        while (inFile.good()) {
            Order order;
            int count;
            inFile.read(reinterpret_cast<char*>(&count), sizeof(int));
            order.GetProductName().resize(count);
            std::string temp;
            inFile.read(&temp[0], count);
            order.SetProductName(temp);
            char* str = new char[count + 1];
            inFile.read(str, count + 1);
            order.SetProductName(std::string(str));

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
    }*/
}

NodeUser* LoadUsersFromFile(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary | std::ios::in);
    if (inFile.is_open())
    {
        NodeUser* root = nullptr;
        while (inFile.good())
        {
            User user;
            // Чтение login
            int buf_size = 0;
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            std::string buf;
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            user.SetLogin(buf);
            if (buf == "")
            {
                inFile.close();
                break;
            }
            // Read password
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            user.SetPassword(buf);

            // Read IsAdmin
            bool temp_bool;
            inFile.read(reinterpret_cast<char*>(&temp_bool), sizeof(bool));
            user.SetIsAdmin(temp_bool);

            root = InsertNode(root, user);
        }
        inFile.close();
        return root;
    }
    else {
        std::cout << "Failed to open the file for reading." << std::endl;
    }
}

void SaveUsersToFile(NodeUser* root, const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary | std::ios::out);
    if (outFile.is_open())
    {
        if (root != nullptr)
        {
            // Запись _owner_phone_number
            int name_size = root->data.GetLogin().size();
            outFile.write(reinterpret_cast<char*>(&name_size), sizeof(int));
            outFile.write(root->data.GetLogin().c_str(), name_size);

            // Запись _issue_date
            int password_size = root->data.GetPassword().size();
            outFile.write(reinterpret_cast<char*>(&password_size), sizeof(int));
            outFile.write(root->data.GetPassword().c_str(), password_size);

            // Запись _status
            bool temp2 = root->data.GetIsAdmin();
            outFile.write(reinterpret_cast<char*>(&temp2), sizeof(bool));

            SaveUsersToFile(root->left, filename);
            SaveUsersToFile(root->right, filename);

            outFile.close();
            std::cout << "Data has been written to the file." << std::endl;
        }
    }
    else {
        std::cout << "Failed to open the file for writing." << std::endl;
    }
}