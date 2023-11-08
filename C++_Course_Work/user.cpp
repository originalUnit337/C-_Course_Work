#include "user.h"

User::User(const string& name, const string& password)
	: name(name), password(password)
{

};

User::User() = default;