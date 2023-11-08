#include "functions.h"

void Authorization(std::string& username, std::string& SHA)
{
	std::string line;
	std::ifstream in("../data/users_info.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	in.close();     // закрываем файл
}
