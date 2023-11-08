#pragma once
#include <iostream>
using namespace std;

class User
{
	string name;
	string password;

public:
	User();

	User(const string& name, const string& password);

};

class Admin : User
{

public:

	Admin() = default;
};