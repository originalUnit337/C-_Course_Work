#include <iostream>
class Order
{
private:
	std::string _product_name;
	std::string _product_brand;
	std::string _owner_full_name;
	std::string _owner_phone_number;
	double _repair_cost;
	std::string _acceptance_date;
	std::string _issue_date;
	bool _status;
public:
	Order();

	Order(const std::string& _product_name, const std::string& _product_brand, const std::string& _owner_full_name, const std::string& _owner_phone_number, double _repair_cost, const std::string& _acceptance_date, const std::string& _issue_date, bool _status);
	
	void Print(const std::string& _product_name, const std::string& _product_brand, const std::string& _owner_full_name, const std::string& _owner_phone_number, double _repair_cost, const std::string& _acceptance_date, const std::string& _issue_date, bool _status);
	

	friend std::ostream& operator << (std::ostream& os, const Order& order);

	friend std::istream& operator >> (std::istream& in, Order& order);

	std::string GetProductName();
	std::string GetProductBrand();
	std::string GetOwnerFullName();
	std::string GetOwnerPhoneNumber();
	double GetRepairCost();
	std::string GetAcceptanceDate();
	std::string GetIssueDate();
	bool GetStatus();

};
