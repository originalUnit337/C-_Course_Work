#include "binary_tree.h"

BinaryTreeOrder::BinaryTreeOrder() { root = nullptr; }

void BinaryTreeOrder::Insert(Order* order) { root = InsertOrder(root, order); }

void BinaryTreeOrder::PrintOrders()
{
    int count = 1;
    int* countptr = &count;
    std::cout << std::left << std::setw(3) << "#" << std::setw(30) << "Product Name"
        << std::setw(30) << "Product Brand"
        << std::setw(30) << "Owner Full Name"
        << std::setw(20) << "Phone Number"
        << std::setw(15) << "Repair Cost"
        << std::setw(17) << "Acceptance Date"
        << std::setw(17) << "Issue Date"
        << std::setw(10) << "Status" << std::endl;

    // Вывод разделительной строки
    std::cout << std::setfill('-') << std::setw(150) << "-" << std::endl;
    std::cout << std::setfill(' ');
    PrintOrdersPrivate(root, countptr);
}

void BinaryTreeOrder::PrintRepairingOrders()
{
    int count = 1;
    int* countptr = &count;
    std::cout << std::left << std::setw(3) << "#" << std::setw(30) << "Product Name"
        << std::setw(30) << "Product Brand"
        << std::setw(30) << "Owner Full Name"
        << std::setw(20) << "Phone Number"
        << std::setw(15) << "Repair Cost"
        << std::setw(17) << "Acceptance Date"
        << std::setw(17) << "Issue Date"
        << std::setw(10) << "Status" << std::endl;

    // Вывод разделительной строки
    std::cout << std::setfill('-') << std::setw(150) << "-" << std::endl;
    std::cout << std::setfill(' ');
    PrintRepairingOrdersPrivate(root, countptr);
}

void BinaryTreeOrder::SearchOrdersByProductName(const std::string& _product_name)
{
    int count = 1;
    int* countptr = &count;
    std::cout << std::left << std::setw(3) << "#" << std::setw(30) << "Product Name"
        << std::setw(30) << "Product Brand"
        << std::setw(30) << "Owner Full Name"
        << std::setw(20) << "Phone Number"
        << std::setw(15) << "Repair Cost"
        << std::setw(17) << "Acceptance Date"
        << std::setw(17) << "Issue Date"
        << std::setw(10) << "Status" << std::endl;

    // Вывод разделительной строки
    std::cout << std::setfill('-') << std::setw(150) << "-" << std::endl;
    std::cout << std::setfill(' ');
    SearchOrdersByProductNamePrivate(root, _product_name, countptr);
    if (count == 1)
    {
        system("cls");
        std::cout << "No such orders found" << std::endl;
    }
}

void BinaryTreeOrder::SaveOrdersToFile(const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary | std::ios::out);
    if (outFile.is_open())
    {
        SaveOrdersToFilePrivate(root, &outFile);
        outFile.close();
        std::cout << "Data has been written to the file." << std::endl;
    }
    else {
        std::cout << "Failed to open the file for writing." << std::endl;
    }
}

void BinaryTreeOrder::DeleteOrderTree()
{
    DeleteOrderTreePrivate(root);
    root = nullptr;
}

void BinaryTreeOrder::DeleteOrderNode(int* count_to_find)
{
    int count = 1;
    int* countptr = &count;
    root = DeleteOrderNodePrivate(root, count_to_find, countptr);
}

void BinaryTreeOrder::EditOrderNode(int* count_to_find)
{
    int count = 1;
    int* countptr = &count;
    EditOrderNodePrivate(root, count_to_find, countptr);
    if (*count_to_find == *countptr)
    {
        std::cout << "No such object" << std::endl;
    }
}

bool compareDates(const std::string& date1, const std::string& date2);

TreeNodeOrder* BinaryTreeOrder::InsertOrder(TreeNodeOrder* node, Order* order)
{
    if (node == nullptr) {
        return new TreeNodeOrder(order);
    }
    else
    {
        if (compareDates(order->GetAcceptanceDate(), node->data->GetAcceptanceDate()))
        {
            node->left = InsertOrder(node->left, order);
        }
        else
        {
            node->right = InsertOrder(node->right, order);
        }
    }
    return node;
}

bool compareDates(const std::string& date1, const std::string& date2) 
{
    try
    {
        int day1 = std::stoi(date1.substr(0, 2));
        int month1 = std::stoi(date1.substr(3, 2));
        int year1 = std::stoi(date1.substr(6, 4));

        int day2 = std::stoi(date2.substr(0, 2));
        int month2 = std::stoi(date2.substr(3, 2));
        int year2 = std::stoi(date2.substr(6, 4));
        if (year1 != year2) {
            return year1 < year2;
        }
        else if (month1 != month2) {
            return month1 < month2;
        }
        else {
            return day1 < day2;
        }
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error: Invalid date format." << std::endl;
    }
}

void BinaryTreeOrder::PrintOrdersPrivate(TreeNodeOrder* node, int* count)
{
    if (node != nullptr)
    {
        PrintOrdersPrivate(node->right, count);
        std::cout << std::left << std::setw(3) << (*count)++  << *(node->data) << std::endl;
        PrintOrdersPrivate(node->left, count);
    }
}

void BinaryTreeOrder::PrintRepairingOrdersPrivate(TreeNodeOrder* node, int* count)
{
    if (node != nullptr)
    {
        PrintRepairingOrdersPrivate(node->right, count);
        if (!node->data->GetStatus())
        {
            std::cout << std::left << std::setw(3) << (*count)++ << *(node->data) << std::endl;
        }
        PrintRepairingOrdersPrivate(node->left, count);
    }
}

void BinaryTreeOrder::SearchOrdersByProductNamePrivate(TreeNodeOrder* node, const std::string& _product_name, int* count)
{
    if (node != nullptr) 
    {
        SearchOrdersByProductNamePrivate(node->right, _product_name, count);
        if (node->data->GetProductName().find(_product_name) != std::string::npos) 
        {
            std::cout << std::left << std::setw(3) << (*count)++ << *(node->data) << std::endl;
        }
        SearchOrdersByProductNamePrivate(node->left, _product_name, count);
    }
}

void BinaryTreeOrder::DeleteOrderTreePrivate(TreeNodeOrder* node)
{
    if (node == nullptr)
    {
        return;
    }

    DeleteOrderTreePrivate(node->left);
    DeleteOrderTreePrivate(node->right);

    delete node;
}

TreeNodeOrder* BinaryTreeOrder::DeleteOrderNodePrivate(TreeNodeOrder* node, int* count_to_find, int* count)
{
    if (node != nullptr)
    {
        node->right = DeleteOrderNodePrivate(node->right, count_to_find, count);

        if (*count_to_find == *count)
        {
            if (node->left == nullptr && node->right == nullptr) {
                (*count)++;
                delete node;
                return nullptr;
            }
            else if (node->right == nullptr) {
                TreeNodeOrder* temp = node->left;
                (*count)++;
                delete node;
                return temp;
            }
            else if (node->left == nullptr) {
                TreeNodeOrder* temp = node->right;
                (*count)++;
                delete node;
                return temp;
            }
            else {
                TreeNodeOrder* minRightNode = FindMinNode(node->right);
                *(node->data) = *(minRightNode->data);
                node->right = DeleteOrderNodePrivate(node->right, count_to_find, count);
                (*count)++;
            }
        }
        else
        {
            (*count)++;
            node->left = DeleteOrderNodePrivate(node->left, count_to_find, count);
        }
    }
    else
    {
        return nullptr;
    }
    return node;
}

TreeNodeOrder* BinaryTreeOrder::FindMinNode(TreeNodeOrder* node)
{
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

void BinaryTreeOrder::EditOrderNodePrivate(TreeNodeOrder* node, int* count_to_find, int* count)
{
    if (node != nullptr)
    {
        EditOrderNodePrivate(node->right, count_to_find, count);

        if (*count_to_find == *count)
        {
            (*count)++; // во избежании повторного выполнения условия
            int choice;
            std::string s;
            double d;
            bool b;
            do
            {
                system("cls");
                std::cout << *(node)->data << std::endl;
                std::cout << "What do you want to change ?" << std::endl;
                std::cout << "1. Product Name" << std::endl;
                std::cout << "2. Product Brand" << std::endl;
                std::cout << "3. Owner Full Name" << std::endl;
                std::cout << "4. Owner Phone Number" << std::endl;
                std::cout << "5. Repair Cost" << std::endl;
                std::cout << "6. Acceptance Date" << std::endl;
                std::cout << "7. Issue Date" << std::endl;
                std::cout << "8. Status" << std::endl;
                std::cout << "0. Exit" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::cin.clear();
                std::cin >> choice;
                while (cin.fail())
                {
                    cin.clear();
                    while (cin.get() != '\n');
                    std::cout << "Invalid value. Try again" << std::endl;
                    cin >> choice;
                }
                switch (choice) {
                case 1:
                    system("cls");
                    std::cout << "Enter a new product name: ";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                    std::getline(std::cin, s);
                    node->data->SetProductName(s);
                    break;
                case 2:
                    system("cls");
                    std::cout << "Enter a new product brand: ";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                    std::getline(std::cin, s);
                    node->data->SetProductBrand(s);
                    break;
                case 3:
                    system("cls");
                    std::cout << "Enter a new owner full name: ";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                    std::getline(std::cin, s);
                    node->data->SetOwnerFullName(s);
                    break;
                case 4:
                    system("cls");
                    std::cout << "Enter a new owner phone number: ";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                    std::getline(std::cin, s);
                    node->data->SetOwnerPhoneNumber(s);
                    break;
                case 5:
                    system("cls");
                    std::cout << "Enter a new repair cost: ";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                    std::cin >> d;
                    while (cin.fail())
                    {
                        cin.clear();
                        while (cin.get() != '\n');
                        std::cout << "Invalid value. Try again" << std::endl;
                        cin >> d;
                    }
                    node->data->SetRepairCost(d);
                    break;
                case 6:
                    system("cls");
                    std::cout << "Enter a new acceptance date (please, use the dd.mm.yyyy format): ";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                    std::getline(std::cin, s);
                    node->data->SetAcceptanceDate(s);
                    system("cls");
                    break;
                case 7:
                    system("cls");
                    std::cout << "Enter a new issue date (please, use the dd.mm.yyyy format): ";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                    std::getline(std::cin, s);
                    node->data->SetIssueDate(s);
                    system("cls");
                    break;
                case 8:
                    system("cls");
                    std::cout << "Enter a new status: ";
                    std::cin.ignore(std::cin.rdbuf()->in_avail());
                    std::cin.clear();
                    std::cin >> b;
                    node->data->SetStatus(b);
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
                            cin.clear();
                            while (cin.get() != '\n');
                            std::cout << "Invalid value. Try again" << std::endl;
                            cin >> choice3;
                        }
                        switch (choice3)
                        {
                        case 1:
                            choice3 = 0;
                            system("cls");
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
            EditOrderNodePrivate(node->left, count_to_find, count);
        }
    }
    else
    {
        return;
    }
    return;
}


void BinaryTreeOrder::SaveOrdersToFilePrivate(TreeNodeOrder* node, std::ofstream* outFile)
{
        if (node != nullptr)
        {
            // Запись _product_name
            int product_name_size = (node->data)->GetProductName().size();
            outFile->write(reinterpret_cast<char*>(&product_name_size), sizeof(int));
            outFile->write(node->data->GetProductName().c_str(), product_name_size);

            // Запись _product_brand
            int product_brand_size = (node->data)->GetProductBrand().size();
            outFile->write(reinterpret_cast<char*>(&product_brand_size), sizeof(int));
            outFile->write(node->data->GetProductBrand().c_str(), product_brand_size);

            // Запись _owner_full_name
            int owner_full_name_size = node->data->GetOwnerFullName().size();
            outFile->write(reinterpret_cast<char*>(&owner_full_name_size), sizeof(int));
            outFile->write(node->data->GetOwnerFullName().c_str(), owner_full_name_size);

            // Запись _owner_phone_number
            int owner_phone_number_size = node->data->GetOwnerPhoneNumber().size();
            outFile->write(reinterpret_cast<char*>(&owner_phone_number_size), sizeof(int));
            outFile->write(node->data->GetOwnerPhoneNumber().c_str(), owner_phone_number_size);

            // Запись _repair_cost
            double temp = node->data->GetRepairCost();
            outFile->write(reinterpret_cast<char*>(&temp), sizeof(double));

            // Запись _acceptance_date
            int acceptance_date_size = node->data->GetAcceptanceDate().size();
            outFile->write(reinterpret_cast<char*>(&acceptance_date_size), sizeof(int));
            outFile->write(node->data->GetAcceptanceDate().c_str(), acceptance_date_size);

            // Запись _issue_date
            int issue_date_size = node->data->GetIssueDate().size();
            outFile->write(reinterpret_cast<char*>(&issue_date_size), sizeof(int));
            outFile->write(node->data->GetIssueDate().c_str(), issue_date_size);

            // Запись _status
            bool temp2 = node->data->GetStatus();
            outFile->write(reinterpret_cast<char*>(&temp2), sizeof(bool));

            SaveOrdersToFilePrivate(node->left, outFile);
            SaveOrdersToFilePrivate(node->right, outFile);

        }
}

void BinaryTreeOrder::LoadOrdersFromFile(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary | std::ios::in);
    if (inFile.is_open())
    {
        while (inFile.good())
        {
            Order* order = new Order();
            // Чтение _product_name
            int buf_size = 0;
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            std::string buf;
            buf.clear();
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order->SetProductName(buf);
            if (buf.empty() || buf_size == 1)
            {
                inFile.close();
                break;
            }

            // Read _product_brand
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order->SetProductBrand(buf);

            // Read _owner_full_name
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order->SetOwnerFullName(buf);

            // Read _owner_phone_number
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order->SetOwnerPhoneNumber(buf);

            // Read _repair_cost
            double temp_double;
            inFile.read(reinterpret_cast<char*>(&temp_double), sizeof(double));
            order->SetRepairCost(temp_double);

            // Read _acceptance_date
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order->SetAcceptanceDate(buf);

            // Read _issue_date
            inFile.read(reinterpret_cast<char*>(&buf_size), sizeof(int));
            buf.resize(buf_size);
            inFile.read(&buf[0], buf_size);
            order->SetIssueDate(buf);

            // Read _issue_date
            bool temp_bool;
            inFile.read(reinterpret_cast<char*>(&temp_bool), sizeof(bool));
            order->SetStatus(temp_bool);

            this->Insert(order);
        }
        inFile.close();
    }
    else {
        std::cout << "Failed to open the file for reading." << std::endl;
    }
}