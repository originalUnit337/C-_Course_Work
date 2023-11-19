#include "binary_tree.h"
#include "user.h"
#include <conio.h>
#include <Windows.h>
#include "SHA256.h"
//#include <fstream>
//b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9
//e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
int main()
{
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
		//if (ch == '\b') std::cout << '\b';
	}
	std::cout << std::endl;
	//std::cout << password;
	//std::cin >> password;
	SHA256 sha;
	sha.update(password);
	std::array<uint8_t, 32> digest = sha.digest();

	std::cout << SHA256::toString(digest) << std::endl;

	/*ifstream in;
	in.open("data/users_info.txt");
	string str;
	while (!in.eof())
	{
		in >> str;
		std::cout << str << std::endl;
	}
	in.close();*/
	std::string line;

	std::ifstream in("../data/orders_info.txt"); // окрываем файл для чтения
	//std::ifstream in("data/users_info.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	in.close();     // закрываем файл
	Order ball("Name", "Brand", "Full Name", "+37535453245", 34.365, "15.10.2023", "20.10.2023", false);
	Order goal("Goal", "Brand2", "Full Name2", "+3754412369", 28.9, "16.10.2023", "25.10.2023", true);
	Node* root = nullptr;//LoadOrdersFromFile("../data/orders.bin");
	//CreateNode(ball);
	//InsertNode(root, ball);
	InsertNode(root, goal);
	//PrintOrdersByAcceptanceDate(root);
	return 0;
	int countOfElements = 1;
	std::ofstream out("../data/orders_info.txt");
	if (out.is_open())
	{
		for (int i = 0; i < countOfElements; i++)
		{
			out << ball;
			out << goal;
		}
	}

	std::cout << ball;
	Order test;
	User user;
	std::cin >> test;
	std::cout << test;
	//std::string::npos;
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