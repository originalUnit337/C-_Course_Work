#include "binary_tree.h"


User::User(const string& name, const string& password, bool isAdmin)
	: name(name), password(password), isAdmin(isAdmin)
{

};

User::User() = default;

void Admin::AddNewOrder(BinaryTreeOrder* tree)
{
	Order* order = new Order();
	std::cout << "Enter data: " << std::endl;
	cin >> *order;
	tree->Insert(order);
	system("cls");
	std::cout << "The data has been added succesfully " << std::endl;
}

void Admin::AddNewUser(BinaryTreeUser* tree)
{
	User* user = new User();
	std::cout << "Enter data: " << std::endl;
	cout << "Enter username: ";
	string s;
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	getline(cin, s);
	while (tree->SearchUserName(s) == 1)
	{
		cin.clear();
		//while (cin.get() != '\n');
		std::cout << "Error: such username already exists. Please try again." << std::endl;
		getline(cin, s);
	}
	user->SetLogin(s);
	cout << "Enter user's password: ";
	string password;
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
	user->SetPassword(SHA256::toString(digest));
	cout << "Set a role (1 - admin, 0 - not admin): ";
	bool b;
	cin >> b;
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	user->SetIsAdmin(b);
	tree->Insert(user);
	tree->PrintUsers();
}
