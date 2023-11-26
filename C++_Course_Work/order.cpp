#include "order.h"

Order::Order()
{
	_product_name = "Undefined";
	_product_brand = "Undefined";
	_owner_full_name = "Undefined";
	_owner_phone_number = "Undefined";
	_repair_cost = 0;
	_acceptance_date = "Undefined";
	_issue_date = "Undefined";
	_status = false;
}

Order::Order(const std::string& _product_name, const std::string& _product_brand, const std::string& _owner_full_name, const std::string& _owner_phone_number, double _repair_cost, const std::string& _acceptance_date, const std::string& _issue_date, bool _status)
	: _product_name(_product_name), _product_brand(_product_brand), _owner_full_name(_owner_full_name), _owner_phone_number(_owner_phone_number), _repair_cost(_repair_cost), _acceptance_date(_acceptance_date), _issue_date(_issue_date), _status(_status)
{
	/*this->_product_name = _product_name;
	this->_product_brand = _product_brand;
	this->_owner_full_name = _owner_full_name;
	this->_owner_phone_number = _owner_phone_number;
	this->_repair_cost = _repair_cost;
	this->_acceptance_date = _acceptance_date;*/

}

void Order::Print(const std::string& _product_name, const std::string& _product_brand, const std::string& _owner_full_name, const std::string& _owner_phone_number, double _repair_cost, const std::string& _acceptance_date, const std::string& _issue_date, bool _status)
{
	
}

std::string Order::GetProductName()
{
	return this->_product_name;
}

std::string Order::GetProductBrand()
{
	return this->_product_brand;
}

std::string Order::GetOwnerFullName()
{
	return this->_owner_full_name;
}

std::string Order::GetOwnerPhoneNumber()
{
	return this->_owner_phone_number;
}

double Order::GetRepairCost()
{
	return this->_repair_cost;
}

std::string Order::GetAcceptanceDate()
{
	return this->_acceptance_date;
}

std::string Order::GetIssueDate()
{
	return this->_issue_date;
}

bool Order::GetStatus()
{
	return this->_status;
}

std::ostream& operator << (std::ostream& os, const Order& order)
{
	os << "Product Name: " << order._product_name << "\t";
	os << "Product Brand: " << order._product_brand << "\t";
	os << "Owner Name: " << order._owner_full_name << "\t";
	os << "Owner phone number: " << order._owner_phone_number << "\t";
	os << "Repair cost: " << order._repair_cost << "\t";
	os << "Acceptance date: " << order._acceptance_date << "\t";
	os << "Issue date: " << order._issue_date << "\t";
	os << "Status: " << order._status << std::endl;
	return os;
	// TODO: вставьте здесь оператор return
}

std::istream& operator >> (std::istream& in, Order& order)
{
	//name:
	try
	{
		std::cout << "Product Name: "; 
		in >> order._product_name;// std::cout << "\t";

		std::cout << "Product Brand: ";
		in >> order._product_brand;// std::cout << "\t";
	
		std::cout << "Owner Name: ";
		in >> order._owner_full_name;// std::cout << "\t";

		std::cout << "Owner phone number: ";
		in >> order._owner_phone_number;// std::cout << std::endl;

		std::cout << "Repair cost: ";
		in >> order._repair_cost;// std::cout << "\t";

		while (in.fail())
		{
			//in.ignore(in.rdbuf()->in_avail());
			in.clear();
			while (in.get() != '\n');
			std::cout << "Invalid value. Try again" << std::endl;
			std::cout << "Repair cost: ";
			in >> order._repair_cost;
			//throw 1;
		}

		std::cout << "Acceptance date: ";
		in >> order._acceptance_date;// std::cout << "\t";

		std::cout << "Issue date: ";
		in >> order._issue_date;// std::cout << "\t";

		std::cout << "Status: ";
		in >> order._status;// std::cout << std::endl;
		return in;
	}
	catch (int code)
	{
		std::cout << "Error code: " << code << std::endl;
	}
	//goto name;
	/*catch (const std::exception& ex)
	{
		std::cout << &ex;
	}*/
}
