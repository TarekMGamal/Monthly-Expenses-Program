#include "Expense.h"
#include <string>




Expense::Expense()
{
	//myChoice = -1;
}



Expense::Expense(exspense_info info)
{
	this->info = info;
	
}

void Expense::display_data(int count1,int count2)
{
	if (info.name != "")
		cout << info.date << '\t' << '\t' << info.name;
	for (int i = 0; i < count1 + 6- (info.name.size()); i++)
		cout << " ";
	cout << info.category;
	for (int i = 0; i < count2 + 6 -(info.category.size()); i++)
		cout << " ";
	cout << info.category;
	cout << info.amount << '\t' << info.price << '\t' << info.description << '\n';
}
string Expense::get_category() 
{
	return info.category;
}
string Expense::get_data()
{
	return info.name + ',' + info.category + ',' + ',' + to_string((info.amount)) + ',' + to_string(info.price)
		+ '\n' +
		info.description
		+ '\n' +
		to_string(info.day) + '-' + to_string(info.month) + '-' + to_string(info.year );

}
string Expense::get_date() 
{
	return info.date;
}
string Expense::get_name()
{
	return info.name;
}

int Expense::get_amount()
{
	return info.amount;
}
float Expense::get_price()
{
	return info.price;
}
int Expense::get_year()
{
	return info.year;
}
int Expense::get_month()
{
	return info.month;
}
int Expense::get_day()
{
	return info.day;
}