#include "binary_tree.h"

BinaryTreeUser::BinaryTreeUser()
{
    root = nullptr;
}

void BinaryTreeUser::Insert(User* user)
{
    root = InsertUser(root, user);
}

void BinaryTreeUser::PrintUsers()
{
    PrintUsersPrivate(root);
}

void BinaryTreeUser::SaveUsersToFile(const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary | std::ios::out);
    if (outFile.is_open())
    {
        SaveUsersToFilePrivate(root, &outFile);
        outFile.close();
        //SaveOrdersToFilePrivate(root, outFile);
        std::cout << "Data has been written to the file." << std::endl;
    }
    else {
        std::cout << "Failed to open the file for writing." << std::endl;
    }
}


TreeNodeUser* BinaryTreeUser::InsertUser(TreeNodeUser* node, User* user)
{
    if (node == nullptr) {
        return new TreeNodeUser(user);
    }
    else
    {
        if (user->GetLogin() < root->data->GetLogin())
        {
            node->left = InsertUser(node->left, user);
        }
        else
        {
            node->right = InsertUser(node->right, user);
        }
    }
    return node;
}

void BinaryTreeUser::PrintUsersPrivate(TreeNodeUser* node)
{
    if (node != nullptr)
    {
        PrintUsersPrivate(node->left);
        std::cout << std::setw(10) << std::left << node->data->GetLogin() << std::setw(64) << std::left << node->data->GetPassword() << std::setw(1) << std::left << node->data->GetIsAdmin() << std::endl;
        PrintUsersPrivate(node->right);
    }
}

void BinaryTreeUser::LoadUsersFromFile(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary | std::ios::in);
    if (inFile.is_open())
    {
        while (inFile.good())
        {
            User* user = new User();
            // Чтение login
            int buf_size = 0;
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            std::string buf;
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            user->SetLogin(buf);
            if (buf == "")
            {
                inFile.close();
                break;
            }
            // Read password
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            user->SetPassword(buf);

            // Read IsAdmin
            bool temp_bool;
            inFile.read(reinterpret_cast<char*>(&temp_bool), sizeof(bool));
            user->SetIsAdmin(temp_bool);

            this->Insert(user);
        }
        inFile.close();
    }
    else {
        std::cout << "Failed to open the file for reading." << std::endl;
    }
}

void BinaryTreeUser::SaveUsersToFilePrivate(TreeNodeUser* node, std::ofstream* outFile)
{
    if (node != nullptr)
    {
        // Запись _owner_phone_number
        int name_size = node->data->GetLogin().size();
        outFile->write(reinterpret_cast<char*>(&name_size), sizeof(int));
        outFile->write(node->data->GetLogin().c_str(), name_size);

        // Запись _issue_date
        int password_size = node->data->GetPassword().size();
        outFile->write(reinterpret_cast<char*>(&password_size), sizeof(int));
        outFile->write(node->data->GetPassword().c_str(), password_size);

        // Запись _status
        bool temp2 = node->data->GetIsAdmin();
        outFile->write(reinterpret_cast<char*>(&temp2), sizeof(bool));


        SaveUsersToFilePrivate(node->left, outFile);
        SaveUsersToFilePrivate(node->right, outFile);
    }
}

int BinaryTreeUser::SearchUsersPrivate(TreeNodeUser* node, const std::string& name, const std::string& password)
{
    if (node != nullptr) 
    {
        if (SearchUsersPrivate(node->left, name, password) == 1) return 1;
        else if (SearchUsersPrivate(node->left, name, password) == 2) return 2;
        int found_position_name = node->data->GetLogin().find(name);
        int found_position_password = node->data->GetPassword().find(password);
        if ((found_position_name != string::npos && found_position_name + name.length() == node->data->GetLogin().length())
            && (found_position_password != string::npos && found_position_password + password.length() == node->data->GetPassword().length()))
        {
            if (node->data->GetIsAdmin())
            {
                return 1;
            }
            else return 2;
            std::cout << "Login: " << node->data->GetLogin() << "Password: " << node->data->GetPassword() << "Is Admin: " << node->data->GetIsAdmin() << std::endl;
        }
        if (SearchUsersPrivate(node->right, name, password) == 1) return 1;
        else if (SearchUsersPrivate(node->left, name, password) == 2) return 2;
    }
    return 0;
}

int BinaryTreeUser::SearchUsers(const std::string& name, const std::string& password)
{
    return SearchUsersPrivate(root, name, password);
}