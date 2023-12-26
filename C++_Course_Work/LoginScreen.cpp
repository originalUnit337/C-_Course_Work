#include "LoginScreen.h"
#include "SHA256.h"
#include "binary_tree.h"
#include <iostream>
#include <conio.h>

LoginScreen::LoginScreen()
{

}
LoginScreen::~LoginScreen()
{
}

//int LoginScreen::GetNameNumber(TreeNodeUser* root, std::string s)
//{
//	int count = 1;
//	int* countptr = &count;
//	return GetNameNumberPrivate(root, s, countptr);
//}
//
//int LoginScreen::GetNameNumberPrivate(TreeNodeUser* node, std::string s, int* count)
//{
//	if (node != nullptr)
//	{
//		GetNameNumberPrivate(node->left, s, count);
//		if (node->data->GetLogin() == s)
//		{
//			int temp = *count;
//			return temp;
//		}
//		else (*count)++;
//		GetNameNumberPrivate(node->right, s, count);
//	}
//}

void LoginScreen::Authorization()
{
	int flag = 1;
	while (flag)
	{
		std::string username;
		std::cout << "Enter username: ";
		std::cin >> username;
		std::string password;
		std::cout << "Enter your password: ";
		char ch;
		while ((ch = _getch()) != '\r')
		{
			if (ch == '\b')
			{
				if (!password.empty())
				{
					password.pop_back();
					std::cout << "\b \b";
				}
			}
			else
			{
				password.push_back(ch);
				std::cout << "*";
			}
		}
		std::cout << std::endl;
		SHA256 sha;
		sha.update(password);
		password.clear();
		std::array<uint8_t, 32> digest = sha.digest();
		// проверка на верность логина и пароля в файле
		BinaryTreeUser* tree_user = new BinaryTreeUser();
		tree_user->LoadUsersFromFile("../data/users.bin");
		//std::cout << SHA256::toString(digest);
		if (tree_user->SearchUsers(username, SHA256::toString(digest)) == 1) // 1 - admin, 2 - user, 0 - no such user
		{
			flag = 0;
			system("cls");
			std::cout << "Welcome, " << username << std::endl;
			this->SetName(username);
			this->AdminMenu();
		}
		else
		{
			if (tree_user->SearchUsers(username, SHA256::toString(digest)) == 2)
			{
				flag = 0;
				system("cls");
				std::cout << "Welcome, " << username << std::endl;
				this->SetName(username);
				this->UserMenu();
			}
			else
			{
				std::cout << "Error: wrong password or username" << std::endl;
			}
		}
	}
}

void LoginScreen::AdminMenu()
{
	BinaryTreeUser* tree_user = new BinaryTreeUser();
	tree_user->LoadUsersFromFile("../data/users.bin");
	Admin* admin = new Admin();
	BinaryTreeOrder* tree_order = new BinaryTreeOrder();
	tree_order->LoadOrdersFromFile("../data/orders.bin");
	int choice;
	int number_of_current_user;
	do 
	{
		std::cout << "Menu:" << std::endl;
		std::cout << "---------------------------|" << std::endl;
		std::cout << "1. Add new Order           |" << std::endl;
		std::cout << "2. Delete Order            |" << std::endl;
		std::cout << "3. Edit Order              |" << std::endl;
		std::cout << "4. Save Changes (orders)   |" << std::endl;
		std::cout << "5. Cancel Changes (orders) |" << std::endl;
		std::cout << "6. Show orders             |" << std::endl;
		std::cout << "---------------------------|" << std::endl;
		std::cout << "7. Add new user/admin      |" << std::endl;
		std::cout << "8. Delete user/admin       |" << std::endl;
		std::cout << "9. Edit user/admin         |" << std::endl;
		std::cout << "10. Save Changes (users)   |"<< std::endl;
		std::cout << "11. Cancel Changes (users) |" << std::endl;
		std::cout << "12. Show users             |" << std::endl;
		std::cout << "---------------------------|" << std::endl;
		std::cout << "0. Exit                    |" << std::endl;
		std::cout << "---------------------------|" << std::endl;
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
			admin->AddNewOrder(tree_order);
			break;
		case 2:
			system("cls");
			tree_order->PrintOrders();
			std::cout << "Enter a number of order to delete: ";
			int number;
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.clear();
			std::cin >> number;
			while (cin.fail())
			{
				cin.clear();
				while (cin.get() != '\n');
				std::cout << "Invalid value. Try again" << std::endl;
				cin >> number;
			}
			tree_order->DeleteOrderNode(&number);
			break;
		case 3:
			system("cls");
			tree_order->PrintOrders();
			std::cout << "Enter a number of order to edit: ";
			int number2;
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.clear();
			std::cin >> number2;
			while (cin.fail())
			{
				cin.clear();
				while (cin.get() != '\n');
				std::cout << "Invalid value. Try again" << std::endl;
				cin >> number2;
			}
			tree_order->EditOrderNode(&number2);
			break;
		case 4:
			system("cls");
			tree_order->SaveOrdersToFile("../data/orders.bin");
			break;
		case 5:
			system("cls");
			std::cout << "Are you sure ?" << std::endl;	
			std::cout << "1. Yes" << std::endl;
			std::cout << "2. No" << std::endl;
			int choice2;
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.clear();

			do
			{
				std::cin >> choice2;

				while (cin.fail())
				{
					cin.clear();
					while (cin.get() != '\n');
					std::cout << "Invalid value. Try again" << std::endl;
					cin >> choice2;
				}
				switch (choice2)
				{
				case 1:
					system("cls");
					std::cout << "Success" << std::endl;
					tree_order->DeleteOrderTree();
					tree_order->LoadOrdersFromFile("../data/orders.bin");
					choice2 = 0;
					break;
				case 2:
					system("cls");
					std::cout << "Canceled..." << std::endl;
					choice2 = 0;
					break;
				default:
					std::cout << "Invalid choice. Please try again." << std::endl;
				}
			} while (choice2 != 0);
			break;
		case 6:
			system("cls");
			tree_order->PrintOrders();
			std::cout << "Press any key to continue" << std::endl;
			_getch();
			system("cls");
			break;
		case 7:
			system("cls");
			admin->AddNewUser(tree_user);
			break;
		case 8:
			system("cls");
			tree_user->PrintUsers();
			std::cout << "Enter a number of user to delete: ";
			int number3;
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.clear();
			number_of_current_user = tree_user->GetNameNumber(this->GetName());
			std::cin >> number3;
			while (cin.fail())
			{
				cin.clear();
				while (cin.get() != '\n');
				std::cout << "Invalid value. Try again" << std::endl;
				cin >> number3;
			}
			if (number_of_current_user == number3)
			{
				std::cout << "Are you sure you want to delete yourself ?" << std::endl;
				std::cout << "1. Yes" << std::endl;
				std::cout << "2. No" << std::endl;
				int choice5;
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				std::cin.clear();

				do
				{
					std::cin >> choice5;

					while (cin.fail())
					{
						cin.clear();
						while (cin.get() != '\n');
						std::cout << "Invalid value. Try again" << std::endl;
						cin >> choice5;
					}
					switch (choice5)
					{
					case 1:
						system("cls");
						std::cout << "Success" << std::endl;
						tree_user->DeleteUserNode(&number3);
						choice5 = 0;
						break;
					case 2:
						system("cls");
						std::cout << "Canceled..." << std::endl;
						choice5 = 0;
						break;
					default:
						std::cout << "Invalid choice. Please try again." << std::endl;
					}
				} while (choice5 != 0);
			}
			break;
		case 9:
			system("cls");
			tree_user->PrintUsers();
			std::cout << "Enter a number of user to edit: ";
			int number4;
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.clear();
			std::cin >> number4;
			while (cin.fail())
			{
				cin.clear();
				while (cin.get() != '\n');
				std::cout << "Invalid value. Try again" << std::endl;
				cin >> number4;
			}
			tree_user->EditUserNode(&number4);
			break;
		case 10:
			system("cls");
			tree_user->SaveUsersToFile("../data/users.bin");
			break;
		case 11:
			system("cls");
			std::cout << "Are you sure ?" << std::endl;
			std::cout << "1. Yes" << std::endl;
			std::cout << "2. No" << std::endl;
			int choice4;
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.clear();

			do
			{
				std::cin >> choice4;

				while (cin.fail())
				{
					cin.clear();
					while (cin.get() != '\n');
					std::cout << "Invalid value. Try again" << std::endl;
					cin >> choice4;
				}
				switch (choice4)
				{
				case 1:
					system("cls");
					std::cout << "Success" << std::endl;
					tree_user->DeleteUserTree();
					tree_user->LoadUsersFromFile("../data/users.bin");
					choice4 = 0;
					break;
				case 2:
					system("cls");
					std::cout << "Canceled..." << std::endl;
					choice4 = 0;
					break;
				default:
					std::cout << "Invalid choice. Please try again." << std::endl;
				}
			} while (choice4 != 0);
			break;
		case 12:
			system("cls");
			tree_user->PrintUsers();
			std::cout << "Press any key to continue" << std::endl;
			_getch();
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
					break;
					std::cout << "Exiting..." << std::endl;
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

void LoginScreen::UserMenu()
{
	std::string name;
	BinaryTreeOrder* tree_order = new BinaryTreeOrder();
	tree_order->LoadOrdersFromFile("../data/orders.bin");
	int choice;
	do {
		std::cout << "Menu:" << std::endl;
		std::cout << "------------------------------------------------------|" << std::endl;
		std::cout << "1. Display a general list of orders                   |" << std::endl;
		std::cout << "2. Display a list of orders under repair              |" << std::endl;
		std::cout << "3. Searching for information for a given product name |" << std::endl;
		std::cout << "------------------------------------------------------|" << std::endl;
		std::cout << "0. Exit                                               |" << std::endl;
		std::cout << "------------------------------------------------------|" << std::endl;
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
			tree_order->PrintOrders();
			std::cout << "Press any key to continue" << std::endl;
			_getch();
			system("cls");
			break;
		case 2:
			system("cls");
			tree_order->PrintRepairingOrders();
			std::cout << "Press any key to continue" << std::endl;
			_getch();
			system("cls");
			break;
		case 3:
			system("cls");
			std::cout << "Enter product name to search: ";
			std::cin >> name;
			tree_order->SearchOrdersByProductName(name);
			break;
		case 0:
			system("cls");
			std::cout << "Are you sure ?" << std::endl;
			std::cout << "1. Yes" << std::endl;
			std::cout << "2. No" << std::endl;
			int choice2;
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.clear();
			do
			{
				std::cin >> choice2;
				while (cin.fail())
				{
					cin.clear();
					while (cin.get() != '\n');
					std::cout << "Invalid value. Try again" << std::endl;
					cin >> choice2;
				}
				switch (choice2)
				{
				case 1:
					choice2 = 0;
					break;
					std::cout << "Exiting..." << std::endl;
				case 2:
					system("cls");
					std::cout << "Canceled..." << std::endl;
					choice = 1;
					choice2 = 0;
					break;
				default:
					choice2 = 1;
					std::cout << "Invalid choice. Please try again." << std::endl;
				}
			} while (choice2 != 0);
			break;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	} while (choice != 0);
}