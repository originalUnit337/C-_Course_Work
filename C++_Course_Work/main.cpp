#include "binary_tree.h"
//#include "user.h"
#include <conio.h>
#include <Windows.h>
#include "SHA256.h"
#include "LoginScreen.h"
//#include <fstream>
//b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9
//e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
int main()
{
	LoginScreen ls;
	ls.Authorization();
	return 0;
	string username;
	std::cout << "Enter username: ";
	std::cin >> username;
	string password;
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
	std::array<uint8_t, 32> digest = sha.digest();

	std::cout << SHA256::toString(digest) << std::endl;
	User user(username, SHA256::toString(digest), 1);
	NodeUser* rootUser = nullptr;
	rootUser = InsertNode(rootUser, user);
	SaveUsersToFile(rootUser, "../data/users.bin");
	// koroche zdes bude avtorizaciya
	// a tut checknim hashi i if sovpadaut to ok;
	// vot taki pirogi
	Order ball("Name", "Brand", "Full Name", "+37535453245", 34.365, "15.10.2023", "20.10.2023", false);
	Order goal("Goal", "Brand2", "Full Name2", "+3754412369", 28.9, "16.10.2023", "25.10.2023", true);
	std::cout << "--------------------------------------------" << std::endl;
	//Node* root = nullptr;
	Node* root = /*nullptr; */  LoadOrdersFromFile("../data/orders.bin");
	//CreateNode(ball);
	//root = InsertNode(root, ball);
	//root = InsertNode(root, goal);
	PrintOrdersByAcceptanceDate(root);
	//SaveOrdersToFile(root, "../data/orders.bin");
	return 0;
	char key_code = '\0';
	while (true)
	{
		if (_kbhit())
		{
			key_code = _getch();
			//std::cout << key_code << "\a" << "\a" << std::endl;
			//std::cout << "\b";
		}
		if (key_code == 'q')
		{
			break;
		}
		//else continue;
	}
	return 0;
}