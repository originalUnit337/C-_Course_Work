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

std::string Order::GetProductName() { return this->_product_name; }

std::string Order::GetProductBrand() { return this->_product_brand; }

std::string Order::GetOwnerFullName() { return this->_owner_full_name; }

std::string Order::GetOwnerPhoneNumber() { return this->_owner_phone_number; }

double Order::GetRepairCost() { return this->_repair_cost; }

std::string Order::GetAcceptanceDate() { return this->_acceptance_date; }

std::string Order::GetIssueDate() { return this->_issue_date; }

bool Order::GetStatus() { return this->_status; }

void Order::SetProductName(std::string name) { this->_product_name = name; }

void Order::SetProductBrand(std::string name) { this->_product_brand = name; }

void Order::SetOwnerFullName(std::string name) { this->_owner_full_name = name; }

void Order::SetOwnerPhoneNumber(std::string phone_number) { _owner_phone_number = phone_number; }

void Order::SetRepairCost(double cost) { this->_repair_cost = cost; }

void Order::SetAcceptanceDate(std::string date) { this->_acceptance_date = date; }

void Order::SetIssueDate(std::string date) { this->_issue_date = date; }

void Order::SetStatus(bool status) { this->_status = status; }

std::ostream& operator << (std::ostream& os, const Order& order)
{
	os << std::left << std::setw(30) << order._product_name
		<< std::setw(30) << order._product_brand
		<< std::setw(30) << order._owner_full_name
		<< std::setw(20) << order._owner_phone_number
		<< std::setw(15) << order._repair_cost
		<< std::setw(17) << order._acceptance_date
		<< std::setw(17) << order._issue_date
		<< std::setw(10) << (order._status ? "Completed" : "Not completed") << std::endl;
	return os;
}

std::istream& operator >> (std::istream& in, Order& order)
{
	try
	{
		in.ignore(in.rdbuf()->in_avail());
		in.clear();
		std::cout << "Product Name: "; 
		std::getline(in, order._product_name);

		std::cout << "Product Brand: ";
		std::getline(in, order._product_brand);
	
		std::cout << "Owner Name: ";
		std::getline(in, order._owner_full_name);

		std::cout << "Owner phone number: ";
		std::getline(in, order._owner_phone_number);

		std::cout << "Repair cost: ";
		in >> order._repair_cost;

		while (in.fail())
		{
			in.clear();
			while (in.get() != '\n');
			std::cout << "Invalid value. Try again" << std::endl;
			std::cout << "Repair cost: ";
			in >> order._repair_cost;
		}
		in.ignore(in.rdbuf()->in_avail());

		std::cout << "Acceptance date: ";
		std::getline(in, order._acceptance_date);

		std::cout << "Issue date: ";
		std::getline(in, order._issue_date);

		std::cout << "Status: ";
		in >> order._status;
		in.clear();
		return in;
	}
	catch (int code)
	{
		std::cout << "Error code: " << code << std::endl;
	}
}
