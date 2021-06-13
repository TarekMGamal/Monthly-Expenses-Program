#include <iostream>
#include "filter.h"
#include "Expense.h"
#include <vector>
#include <string>
using namespace std;
filter::filter()
{

}
vector<Expense> filter::filter_amount(vector<Expense> v, float amount, string filter_type)
{
    vector<Expense> ret;
    for (int i = 0; i < v.size(); ++i) {
        if (filter_type == "=")
        {
            if (v[i].info.amount == amount)
                ret.push_back(v[i]);
        }

        else if (filter_type == "<>") {
            if (v[i].info.amount != amount)
                ret.push_back(v[i]);
        }
        else if (filter_type == ">=") {
            if (v[i].info.amount >= amount)
                ret.push_back(v[i]);
        }
        else if (filter_type == "<=") {
            if (v[i].info.amount <= amount)
                ret.push_back(v[i]);
        }
        else if (filter_type == "<")
        {
            if (v[i].info.amount < amount)
                ret.push_back(v[i]);
        }
        else if (filter_type == ">")
        {
            if (v[i].info.amount > amount)
                ret.push_back(v[i]);
        }
        }
    return ret;
}
//vector<Expense> filter::filter_price(vector<Expense> v, float price, string filter_type)
//{
//    vector<Expense> ret;
//        for (int i = 0; i < v.size(); ++i) {
//            if (filter_type == "=")
//                if (v[i].info.price == price)
//                    ret.push_back(v[i]);
//            else if (filter_type == "<>") 
//                if (v[i].info.price != price)
//                    ret.push_back(v[i]);
//            else if (filter_type == ">=") 
//                if (v[i].info.price >= price)
//                    ret.push_back(v[i]);
//            else if (filter_type == "<=") 
//                if (v[i].info.price <= price)
//                    ret.push_back(v[i]);
//            
//            else if (filter_type == "<") 
//                if (v[i].info.price < price)
//                    ret.push_back(v[i]);
//
//            else if (filter_type == ">") 
//                if (v[i].info.price > price)
//                    ret.push_back(v[i]);
//        }
//        return ret;
//}
vector<Expense> filter::filter_category(vector<Expense> v, string icategory) {
    vector<Expense> ret;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i].get_category() == icategory) {
            ret.push_back(v[i]);
        }
    }
    return ret;
}
vector<Expense> filter::filter_date(vector<Expense> v, int iyear, int imonth, int iday, string filter_type)
{
    vector<Expense> ret;
    for (int i = 0; i < v.size(); ++i) 
    {
        if (filter_type == "=") {
            if (v[i].info.year == iyear && v[i].info.month == imonth && v[i].info.day == iday)
                ret.push_back(v[i]);
        }
        else if (filter_type == "<>") {
            if (v[i].info.year!= iyear && v[i].info.month != imonth && v[i].info.day != iday)
                ret.push_back(v[i]);
        }
            
        else if (filter_type == ">=") {
            if (v[i].info.year > iyear)
            {
                ret.push_back(v[i]);
            }
            else if (v[i].info.year == iyear)
            {
                if (v[i].info.month > imonth)
                {
                    ret.push_back(v[i]);
                }
                else if (v[i].info.month == imonth)
                {
                    if (v[i].info.day>= iday)
                        ret.push_back(v[i]);
                }
            }
        }
                
        else if (filter_type == "<=")
        {
            if (v[i].info.year < iyear)
            {
                ret.push_back(v[i]);
            }
            else if (v[i].info.year == iyear)
            {
                if (v[i].info.month < imonth)
                {
                    ret.push_back(v[i]);
                }
                else if (v[i].info.month == imonth)
                {
                    if (v[i].info.day <= iday)
                        ret.push_back(v[i]);
                }
            }

        }

        else if (filter_type == "<")
        {
            if (v[i].info.year < iyear)
            {
                ret.push_back(v[i]);
            }
            else if (v[i].info.year == iyear)
            {
                if (v[i].info.month < imonth)
                {
                    ret.push_back(v[i]);
                }
                else if (v[i].info.month == imonth)
                {
                    if (v[i].info.day < iday)
                        ret.push_back(v[i]);
                }
            }
        }
        else if (filter_type == ">") 
        {
            if (v[i].info.year > iyear)
            {
                ret.push_back(v[i]);
            }
            else if (v[i].info.year == iyear)
            {
                if (v[i].info.month > imonth)
                {
                    ret.push_back(v[i]);
                }
                else if (v[i].info.month == imonth)
                {
                    if (v[i].info.day > iday)
                        ret.push_back(v[i]);
                }
            }
        }
                           
    }
    return ret;
}