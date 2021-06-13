#pragma once
#include <iostream>
#include "Expense.h"
#include <vector>
#include <string>
#include "FileHandler.h"
using namespace std;

class filter
{
private:
public:
    vector<Expense> filter_date(vector<Expense> v, int iyear, int imonth, int iday, string filter_type);
    vector<Expense> filter_category(vector<Expense> v, string icategory);
    vector<Expense> filter_amount(vector<Expense> v, float amount, string  filter_type);
    vector<Expense> filter_price(vector<Expense> v, float price, string  filter_type);
    filter();
};

