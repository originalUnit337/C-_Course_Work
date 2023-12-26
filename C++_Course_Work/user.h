#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>
#include <conio.h>
#include "SHA256.h"

class BinaryTreeOrder;
class BinaryTreeUser;

using namespace std;

class User
{
	string name;
	string password;
	bool isAdmin;

public:
	User();

	User(const string& name, const string& password, bool isAdmin);

	void SetLogin(string name) { this->name = name; }
	void SetPassword(string password) { this->password = password; }
	void SetIsAdmin(bool isAdmin) { this->isAdmin = isAdmin; }

	string GetLogin() { return name; }
	string GetPassword() { return password; }
	bool GetIsAdmin() { return isAdmin; }
};

class Admin : User
{

public:
	void AddNewOrder(BinaryTreeOrder* tree);
	void AddNewUser(BinaryTreeUser* tree);
	Admin() = default;
};
#endif // !USER_H