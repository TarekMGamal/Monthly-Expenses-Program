#pragma once
#include <iostream>
#include <ctime>
#include<string>
#include <string.h>
#include<vector>
using namespace std;


struct exspense_info {
	string name, description, category;
	float amount, price;
	int day, month, year;
	string date;


	vector<string> split(string s, string del)
	{
		int start = 0;
		int end = s.find(del);
		int i = 0;
		vector<string> items(6);
		while (end != -1) {
			items[i] = s.substr(start, end - start);

			start = end + del.size();
			end = s.find(del, start);

			i++;
		}

		items[i] = s.substr(start, end - start);


		return items;
	}

	exspense_info()
	{

	}
	exspense_info(vector<string> info)
	{
		date = info[0];
		description = info[1];

		category = info[2];

		amount = stof(info[3]);

		price = stof(info[4]);
		name = info[5];
		
		vector<string> dateInfo(3);
		dateInfo = split(info[0],"-");


		// It's now working  you can extract day  , month or year from a date :) 
		day = stoi(dateInfo[0]);

		month = stoi(dateInfo[1]);

		year = stoi(dateInfo[2]);

		
	}
	exspense_info(string name, string description, string category, float amount, float price, int day , int month,int year)
	{
		this->name = name;
		this->description = description;

		this->category = category;

		this->amount = amount;

		this->price = price;
		this->day = day;
		this->month = month;
		this->year = year;
		date = to_string(day) + '-' + to_string(month) + '-' + to_string(year);
	}
};
class Expense
{
public:
	
	//int capacity;
	//informations of expense 
	exspense_info info;
	

	 // int expenses_count;
public:
	Expense();

	Expense(exspense_info info);
	void display_data(int count1, int count2);
	string get_category();
	string get_data();
	string get_date();
	string get_name();
	int get_amount();
	float  get_price();
	int get_year();
	int get_month();
	int get_day();
	//void add_expense(string icategory, int idate, int imonth, int iyear);

};

