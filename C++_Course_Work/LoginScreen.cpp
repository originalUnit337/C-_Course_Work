#include "LoginScreen.h"
#include "SHA256.h"
#include "binary_tree.h"
//#include "user.h"
#include <iostream>
#include <conio.h>

LoginScreen::LoginScreen()
{

}
LoginScreen::~LoginScreen()
{
}
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
		if (tree_user->SearchUsers(username, SHA256::toString(digest)) == 1) // 1 - admin, 2 - user, 0 - no such user
		{
			flag = 0;
			system("cls");
			std::cout << "Welcome, " << username << std::endl;
			this->AdminMenu();
		}
		else
		{
			if (tree_user->SearchUsers(username, SHA256::toString(digest)) == 2)
			{
				flag = 0;
				system("cls");
				std::cout << "Welcome, " << username << std::endl;
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
	//SHA256 sha;
	//std::string hahapassword = "Balabol";
	//sha.update(hahapassword);
	//hahapassword.clear();
	//std::array<uint8_t, 32> digest = sha.digest();
	//User* haha = new User("Balbes", SHA256::toString(digest), 0);
	//tree_user->Insert(haha);
	//tree_user->PrintUsers();
	//tree_user->SaveUsersToFile("../data/users.bin");
	Admin* admin = new Admin();
	BinaryTreeOrder* tree_order = new BinaryTreeOrder();
	tree_order->LoadOrdersFromFile("../data/orders.bin");
	//tree_order->LoadOrdersFromFile(OrdersFileName);
	int choice;
	do 
	{
		//system("cls");
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
			//in.ignore(in.rdbuf()->in_avail());
			cin.clear();
			while (cin.get() != '\n');
			std::cout << "Invalid value. Try again" << std::endl;
			cin >> choice;
			//throw 1;
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
				//in.ignore(in.rdbuf()->in_avail());
				cin.clear();
				while (cin.get() != '\n');
				std::cout << "Invalid value. Try again" << std::endl;
				cin >> number;
				//throw 1;
			}
			tree_order->DeleteOrderNode(&number);
			//deleteUser(users);
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
				//in.ignore(in.rdbuf()->in_avail());
				cin.clear();
				while (cin.get() != '\n');
				std::cout << "Invalid value. Try again" << std::endl;
				cin >> number2;
				//throw 1;
			}
			tree_order->EditOrderNode(&number2);
			break;
		case 4:
			system("cls");
			tree_order->SaveOrdersToFile("../data/orders.bin");
			//tree_order->SaveOrdersToFile(OrdersFileName);
			//writeUsersToFile(users, "users.txt");
			//std::cout << "Changes saved successfully." << std::endl;
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
					//in.ignore(in.rdbuf()->in_avail());
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
					//tree_order->LoadOrdersFromFile(OrdersFileName);
					break;
				case 2:
					system("cls");
					std::cout << "Canceled..." << std::endl;
					choice2 = 0;
					break;
				default:
					std::cout << "Invalid choice. Please try again." << std::endl;
					//break;
				}
				//users = readUsersFromFile("users.txt");
				//std::cout << "Changes cancelled." << std::endl;
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
			std::cin >> number3;
			while (cin.fail())
			{
				//in.ignore(in.rdbuf()->in_avail());
				cin.clear();
				while (cin.get() != '\n');
				std::cout << "Invalid value. Try again" << std::endl;
				cin >> number3;
				//throw 1;
			}
			tree_user->DeleteUserNode(&number3);
			//deleteUser(users);
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
				//in.ignore(in.rdbuf()->in_avail());
				cin.clear();
				while (cin.get() != '\n');
				std::cout << "Invalid value. Try again" << std::endl;
				cin >> number4;
				//throw 1;
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
					//in.ignore(in.rdbuf()->in_avail());
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
					//tree_order->LoadOrdersFromFile(OrdersFileName);
					break;
				case 2:
					system("cls");
					std::cout << "Canceled..." << std::endl;
					choice4 = 0;
					break;
				default:
					std::cout << "Invalid choice. Please try again." << std::endl;
					//break;
				}
				//users = readUsersFromFile("users.txt");
				//std::cout << "Changes cancelled." << std::endl;
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
					break;
					std::cout << "Exiting..." << std::endl;
				case 2:
					//system("cls");
					choice = 1;
					choice3 = 0;
					break;
				default:
					choice3 = 1;
					std::cout << "Invalid choice. Please try again." << std::endl;
				}
			} while (choice3 != 0);
			//users = readUsersFromFile("users.txt");
			//std::cout << "Changes cancelled." << std::endl;
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
			//in.ignore(in.rdbuf()->in_avail());
			cin.clear();
			while (cin.get() != '\n');
			std::cout << "Invalid value. Try again" << std::endl;
			cin >> choice;
			//throw 1;
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
					//in.ignore(in.rdbuf()->in_avail());
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