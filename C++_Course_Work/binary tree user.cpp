#include "binary_tree.h"

BinaryTreeUser::BinaryTreeUser() { root = nullptr; }

void BinaryTreeUser::Insert(User* user) { root = InsertUser(root, user); }

void BinaryTreeUser::PrintUsers()
{
    int count = 1;
    int* countptr = &count;
    std::cout << std::left << std::setw(3) << "#" << std::setw(20) << std::left << "Login" << std::setw(64) << std::left << "Password" << std::setw(1) << std::left << " " << "Role" << std::endl;
    std::cout << std::setfill('-') << std::setw(88 + 10) << "-" << std::endl;
    std::cout << std::setfill(' ');
    PrintUsersPrivate(root, countptr);
}

void BinaryTreeUser::DeleteUserTree()
{
    DeleteUserTreePrivate(root);
    root = nullptr;
}

void BinaryTreeUser::DeleteUserNode(int* count_to_find)
{
    int count = 1;
    int* countptr = &count;
    root = DeleteUserNodePrivate(root, count_to_find, countptr);
}

void BinaryTreeUser::EditUserNode(int* count_to_find)
{
    int count = 1;
    int* countptr = &count;
    EditUserNodePrivate(root, count_to_find, countptr, this);
}

void BinaryTreeUser::SaveUsersToFile(const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary | std::ios::out);
    if (outFile.is_open())
    {
        SaveUsersToFilePrivate(root, &outFile);
        outFile.close();
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
        if (user->GetLogin() < node->data->GetLogin())
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

void BinaryTreeUser::PrintUsersPrivate(TreeNodeUser* node, int* count)
{
    if (node != nullptr)
    {
        PrintUsersPrivate(node->left, count);
        std::cout << std::left << std::setw(3) << (*count)++ << std::setw(20) << std::left << node->data->GetLogin() << std::setw(64) << std::left << node->data->GetPassword() << std::setw(1) << std::left << " " << (node->data->GetIsAdmin() ? "admin" : "user") << std::endl;
        PrintUsersPrivate(node->right, count);
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

void BinaryTreeUser::DeleteUserTreePrivate(TreeNodeUser* node)
{
    if (node == nullptr)
    {
        return;
    }

    DeleteUserTreePrivate(node->left);
    DeleteUserTreePrivate(node->right);

    delete node;
}

TreeNodeUser* BinaryTreeUser::DeleteUserNodePrivate(TreeNodeUser* node, int* count_to_find, int* count)
{

    if (node != nullptr)
    {
        node->left = DeleteUserNodePrivate(node->left, count_to_find, count);

        if (*count_to_find == *count)
        {
            if (node->left == nullptr && node->right == nullptr) {
                (*count)++;
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) {
                TreeNodeUser* temp = node->right;
                (*count)++;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNodeUser* temp = node->left;
                (*count)++;
                delete node;
                return temp;
            }
            else {
                TreeNodeUser* minRightNode = FindMinNode(node->right);
                *(node->data) = *(minRightNode->data);
                node->right = DeleteUserNodePrivate(node->right, count_to_find, count);
                (*count)++;
            }
        }
        else
        {
            (*count)++;
            node->right = DeleteUserNodePrivate(node->right, count_to_find, count);
        }
    }
    else
    {
        return nullptr;
    }
    return node;
}

TreeNodeUser* BinaryTreeUser::FindMinNode(TreeNodeUser* node)
{
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

void BinaryTreeUser::EditUserNodePrivate(TreeNodeUser* node, int* count_to_find, int* count, BinaryTreeUser* tree)
{
    if (node != nullptr)
    {
        EditUserNodePrivate(node->left, count_to_find, count, tree);

        if (*count_to_find == *count)
        {
            int choice;
            std::string s;
            double d;
            bool b;
            do
            {
                std::cout << "What do you want to change ?" << std::endl;
                std::cout << "1. Username" << std::endl;
                std::cout << "2. Password" << std::endl;
                std::cout << "3. Role" << std::endl;
                std::cout << "0. Exit" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::cin.clear();
                std::cin >> choice;
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::cin.clear();
                while (cin.fail())
                {
                    cin.clear();
                    while (cin.get() != '\n');
                    std::cout << "Invalid value. Try again" << std::endl;
                    cin >> choice;
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                }
                SHA256 sha;
                switch (choice) {
                case 1:
                    system("cls");
                    std::cout << "Enter a new username: ";
                    std::getline(std::cin, s);
                    while (tree->SearchUserName(s) == 1)
                    {
                        cin.clear();
                        //while (cin.get() != '\n');
                        std::cout << "Error: such username already exists. Please try again." << std::endl;
                        getline(cin, s);
                    }
                    node->data->SetLogin(s);
                    break;
                case 2:
                    system("cls");
                    std::cout << "Enter a new password: ";
                    std::getline(std::cin, s);
                    sha.update(s);
                    s.clear();
                    std::array<uint8_t, 32> digest = sha.digest();
                    node->data->SetPassword(SHA256::toString(digest));
                    break;
                case 3:
                    system("cls");
                    std::cout << "Enter a new role (1 - admin, 0 - not admin): ";
                    std::cin >> b;
                    node->data->SetIsAdmin(b);
                    std::cin.clear();
                    system("cls");
                    break;
                case 0:
                    system("cls");
                    std::cout << "Are you sure ?" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    int choice3;
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();

                    do
                    {
                        std::cin >> choice3;
                        while (cin.fail())
                        {
                            //in.ignore(in.rdbuf()->in_avail());
                            cin.clear();
                            while (cin.get() != '\n');
                            std::cout << "Invalid value. Try again" << std::endl;
                            cin >> choice3;
                        }
                        switch (choice3)
                        {
                        case 1:
                            choice3 = 0;
                            std::cout << "Exiting..." << std::endl;
                            break;
                        case 2:
                            choice = 1;
                            choice3 = 0;
                            break;
                        default:
                            choice3 = 1;
                            std::cout << "Invalid choice. Please try again." << std::endl;
                        }
                    } while (choice3 != 0);
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } while (choice != 0);
        }
        else
        {
            (*count)++;
            EditUserNodePrivate(node->right, count_to_find, count, tree);
        }
    }
    else
    {
        return;
    }
    return;
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

int BinaryTreeUser::SearchUserNamePrivate(TreeNodeUser* node, const std::string& name) // true if such name exist
{
    if (node != nullptr)
    {
        if (SearchUserNamePrivate(node->left, name) == 1) return 1;
        else if (SearchUserNamePrivate(node->left, name) == 2) return 2;
        int found_position_name = node->data->GetLogin().find(name);
        if ((found_position_name != string::npos && found_position_name + name.length() == node->data->GetLogin().length()))
        {
            return 1;
        }
        if (SearchUserNamePrivate(node->right, name) == 1) return 1;
        else if (SearchUserNamePrivate(node->left, name) == 2) return 2;
    }
    return 0;
}

int BinaryTreeUser::SearchUsers(const std::string& name, const std::string& password) { return SearchUsersPrivate(root, name, password); }

int BinaryTreeUser::SearchUserName(const std::string& name) // true if such name exist
{
    return SearchUserNamePrivate(root, name);
}


int BinaryTreeUser::GetNameNumber(std::string s)
{
    int count = 1;
    int* countptr = &count;
    return GetNameNumberPrivate(root, s, countptr);
}

int BinaryTreeUser::GetNameNumberPrivate(TreeNodeUser* node, std::string s, int* count)
{
    if (node != nullptr)
    {
        GetNameNumberPrivate(node->left, s, count);
        if (node->data->GetLogin() == s)
        {
            int temp = *count;
            return temp;
        }
        else (*count)++;
        GetNameNumberPrivate(node->right, s, count);
    }
}