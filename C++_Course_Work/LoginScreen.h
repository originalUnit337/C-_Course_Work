#pragma once
#include <iostream>
#include "binary_tree.h"

class LoginScreen
{
public:
	LoginScreen();
	~LoginScreen();

	//int GetNameNumber(TreeNodeUser* root, std::string s);


	void Authorization();
	void AdminMenu();
	void UserMenu();

	void SetName(std::string x) { authorizated_username = x; }
	std::string GetName() { return authorizated_username; }
private:
	//int GetNameNumberPrivate(TreeNodeUser* node, std::string s, int* count);
	std::string authorizated_username;
};