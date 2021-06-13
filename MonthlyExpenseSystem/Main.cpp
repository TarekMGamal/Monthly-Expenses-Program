#include <iostream>
#include<string>
#include <stdlib.h>
#include "Expense.h"
#include "FileHandler.h"
#include "filter.h"
using namespace std;
string choice = "-1";
int myChoice=-1;
FileHandler handler;
bool menu();
exspense_info validData();
void LoadWithFilter(string currentWallet);
string filterType();
Wallet wallet;
void loadAll(string currentWallet, int number);
//current wallet file
string currentWallet = "cash.txt";

// Eslam 
int main() {
	
	cout << "\t\t\t\t\t ***                MENU           ***\t\t\t  " << endl;
	while (menu());
	return 0;
}
bool menu()
{
	if (choice != "-1")
		cout << "-------------------" << endl;
	cout << "Enter 1 to change your  monthly income" << endl;
	cout << "Enter 2 to enter daily expense " << endl;
	cout << "Enter 3 to view expenses" << endl;
	cout << "Enter 4 to view the remaining money " << endl;
	cout << "Enter 5 to exit " << endl;
	cin >> choice;
	if (choice == "1")
	{
		// this code update the montly income to new one
		//string walletName = "";
		
		cout << "Enter the wallet name to save a new wallet with it's income\n ";
		myChoice = 1;
		currentWallet = handler.chooseWalletFile(myChoice);
		/*vector<string> choices = handler.scanAllWallets();
		cout << endl;

		cin >> walletName;
		int choice = stoi(walletName);
		for (int i = 1; i < choices.size()+1; i++)
			if (choice == i)
			{
				walletName = choices[i-1];

				break;
			}*/
		float income = 0;

		cin >> income;

		if (income > 0)
		{
			// maybe Income should be in wallet constructor ? 
			//if(walletName.find(".txt")==-1)//:
			//	walletName = walletName + ".txt";

			Wallet wallet(currentWallet,income);
			

			wallet.saveIncome(income+wallet.loadIncome(currentWallet));

			float loaded = wallet.loadRemaning(currentWallet);
			if (income == loaded )
			{
				cout << "\nyour income is saved and loaded correctly" << loaded;
			}
		}
		return true;
	}
	else if (choice == "2")
	{
		
		myChoice = 2;
		currentWallet = handler.chooseWalletFile(myChoice);
		while (choice == "2")
		{
			//myChoice = 1;
			handler.saveExpense(currentWallet,validData());
			cout << "if you want to add another expense enter y" << endl;
			cin >> choice;
			if (choice == "y"|| choice == "Y")
				choice = "2";
		}
		return true;
	}
	else if (choice == "3")
	{

		int input = -1;
		myChoice = 3;
		
		vector<string> walletsNames = handler.scanAllWallets();
		currentWallet = handler.chooseWalletFile(myChoice);
		if (currentWallet == "4" )
		{
			if (stoi(currentWallet) == handler.getNumberOfWallets() + 1)
				loadAll(currentWallet, 2);
		}
		
		else
		{
			//load the chosen wallet
			if (currentWallet == "4")
			{
				for (int i = 1; i < walletsNames.size() + 1; i++)

					if (stoi(currentWallet) == i)
					{
						currentWallet = walletsNames[i - 1];

						break;
					}
			}
				

			LoadWithFilter(currentWallet);
		}
			
		
		return true;
	}
	else if (choice == "4")
	{
		
		cout <<"Enter 1 to choose specific wallet" << endl;
		cout <<"Enter 2 to choose all wallets" << endl;
		int input = -1;
		cout << "Enter your choice:"  ;
		while (!(cin >> input) || input< 1||input>2) {
			cout << "Enter your choice:" ;
			cin.clear();
			cin.ignore(123, '\n');
		}
		Wallet wallet;
		if (input == 1)
		{
			myChoice = 4;
			currentWallet = handler.chooseWalletFile(myChoice);
			cout << "your ramaining money is : ";
			cout << wallet.loadRemaning(currentWallet)  << "LE" << endl;
		}
			

		else if (input == 2)
		{

			float total=0;
			//This gets all money from all wallets - all expenses from all wallets 
			vector<string> walletsNames = handler.scanAllWallets();
			for (int i = 0; i < walletsNames.size(); i++)
				total += wallet.loadRemaning(walletsNames[i]);

				cout << total << "LE" << endl;
		}
		
		
		return true;
	}
	else if (choice == "5")
	{
		cout << "good bye"<<endl;
		return false;
	}
	else
	{
		choice = "0";
		return true;
	}
}
exspense_info validData()
{
	string name, description, category;
	float amount = 0, price = 0;
	int day = 0, month = 0, year = 0;
	cout << "Enter exspense name:";
	getline(cin, name);
	getline(cin, name);
	cout << "Enter exspense description:";
	getline(cin, description);
	cout << "Enter exspense category:";
	getline(cin, category);
	cout << "Enter exspense amount:" ;
	while (!(cin >> amount) || amount <= 0) {
		cout << "Enter exspense amount:";
		cin.clear();
		cin.ignore(123, '\n');
	}
	cout << "Enter exspense price :";
	while (!(cin >> price) || price <= 0) {
		cout << "Enter exspense price :" ;
		cin.clear();
		cin.ignore(123, '\n');
	}
	
	float remaning = wallet.loadRemaning(currentWallet) - (amount * price) ;
	if (remaning <=0 )
	{
		
		cout << "you cant compelete this, no enough money "<<endl;
		cout << "your remaining money : " << wallet.loadRemaning(currentWallet)- handler.totalExpenses(currentWallet) << " LE" <<endl;
		cout << "items price : " << ((double)amount * price) << " LE " << endl;
		exspense_info info(name, description, category, -1, price, day, month, year);
		return info;
	}
	else
	{
		cout << "Enter the day:";
		while (!(cin >> day) || day <= 0 || day > 31) {
			cout << "Enter the day:";
			cin.clear();
			cin.ignore(123, '\n');
		}
		cout << "Enter the month:" ;
		while (!(cin >> month) || month <= 0 || month > 12) {
			cout << "Enter the month:";
			cin.clear();
			cin.ignore(123, '\n');
		}
		cout << "Enter the year:";
		while (!(cin >> year) || year <= 2000 || year > 2021) {
			cout << "Enter the year:" ;
			cin.clear();
			cin.ignore(123, '\n');
		}
		exspense_info info(name, description, category, amount, price, day, month, year);

		wallet.setName(currentWallet);
		
		wallet.saveIncome(remaning);
		return info;
	}
	

}
void LoadWithFilter(string currentWallet) {
	char filterChoice = 'n';
	vector<Expense> expenses = handler.loadWallet(currentWallet);
	filter filter;

	cout << "If you want to apply filters enter y else enter anything " << endl;
	cin >> filterChoice;
	filterChoice = tolower(filterChoice);
	while (filterChoice == 'y')
	{
		cout << "In filter type you will be able to enter these choices : " << endl;
		cout << "1) = if you want to show equal to " <<   endl;
		cout << "2) <> if you want to show not equal to " <<   endl;
		cout << "3) <= if you want to show less than or equal to " <<   endl;
		cout << "4) >= if you want to show greater than or equal to " <<   endl;
		cout << "5) < if you want to show less than " <<   endl;
		cout << "6) > if you want to show greater than " <<  endl;
		cout << "if you want to apply category filter enter y " << endl;
		cin >> filterChoice;
		filterChoice = tolower(filterChoice);
		while (filterChoice == 'y')
		{
			cout << "Enter the category : ";
			string categoryTest;
			cin >> categoryTest;
			expenses = filter.filter_category(expenses, categoryTest);
			break;
		}
		cout << "if you want to apply amount filter enter y else press anything ";
		cin >> filterChoice;
		filterChoice = tolower(filterChoice);
		while (filterChoice == 'y')
		{
		
			float  amountTest;
			cout << "Enter exspense amount:";
			while (!(cin >> amountTest) || amountTest < 0) {
				cout << "Enter exspense amount:" << endl;
				cin.clear();
				cin.ignore(123, '\n');
			}
			expenses = filter.filter_amount(expenses, amountTest, filterType());
			break;
		}
		cout << "if you want to apply date filter enter y else press anything" << endl;
		cin >> filterChoice;
		while (filterChoice == 'y')
		{
			int yearTest, monthTest, dayTest;
			cout << "Enter the year" ;
			while (!(cin >> yearTest) || yearTest <= 2000 || yearTest > 2021) {
				cout << "Enter the year:" ;
				cin.clear();
				cin.ignore(123, '\n');
			}
			
			cout << "Enter the Month" ;
			while (!(cin >> monthTest) || monthTest <= 0 || monthTest >=13) {
				cout << "Enter the month:" ;
				cin.clear();
				cin.ignore(123, '\n');
			}
			
			cout << "Enter the day" ;
			while (!(cin >> dayTest) || dayTest <= 0 || dayTest >= 31) {
				cout << "Enter the day:";
				cin.clear();
				cin.ignore(123, '\n');
			}
			expenses = filter.filter_date(expenses, yearTest, monthTest, dayTest, filterType());
			break;
		}
		filterChoice = 'n';
	}
}
void loadAll(string currentWallet,int number) {
	char filterChoice = 'n';

	vector<string> wallets = handler.scanAllWallets();
	int k = 0;
	vector<Expense> expenses(50);
	if (number == 2)
	{
	
		for (int i = 0; i < wallets.size(); i++)
		{
			vector<Expense> temp = handler.loadWallet(wallets[i]);

			for (int j = 0; j < temp.size(); j++)
			{
				expenses[k] = temp[j];
				k++;
			}
		}
		filter filter;
		expenses.resize(k);
		cout << "if you want to apply filters enter y else enter anything " << endl;
		cin >> filterChoice;
		filterChoice = tolower(filterChoice);
		while (filterChoice == 'y')
		{
			cout << "In filter type you will be able to enter these choices : " << endl;
			cout << "1) = if you want to show equal to " << endl;
			cout << "2) >= if you want to show greater than or equal to " << endl;
			cout << "3) > if you want to show greater than " << endl;
			cout << "4) <= if you want to show less than or equal to " << endl;
			cout << "5) < if you want to show less than " << endl;
			cout << "if you want to apply category filter enter y else enter anything" << endl;
			cin >> filterChoice;
			filterChoice = tolower(filterChoice);
			while (filterChoice == 'y')
			{
				cout << "Enter the category : " ;
				string categoryTest;
				cin >> categoryTest;
				expenses = filter.filter_category(expenses, categoryTest);
				break;
			}
			cout << "if you want to apply amount filter enter y else enter anything" ;
			cin >> filterChoice;
			filterChoice = tolower(filterChoice);
			while (filterChoice == 'y')
			{
				cout << "Enter the amount : ";
				float  amountTest;
				cin >> amountTest;
				expenses = filter.filter_amount(expenses, amountTest, filterType());
				break;
			}
			cout << "if you want to apply date filter enter y else  enter anything" << endl;
			cin >> filterChoice;
			while (filterChoice == 'y')
			{
				int yearTest, monthTest, dayTest;
				cout << "Enter the Year" << endl;
				while (!(cin >> yearTest) || yearTest <= 2000 || yearTest > 2021) {
					cout << "Enter the Year:" << endl;
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Enter the Month:" << endl;
				while (!(cin >> monthTest) || monthTest <= 0 || monthTest >= 13) {
					cout << "Enter the Month:" << endl;
					cin.clear();
					cin.ignore(123, '\n');
				}
				cout << "Enter the day:" << endl;
				while (!(cin >> dayTest) || dayTest <= 0 || dayTest >= 32) {
					cout << "Enter the day:" << endl;
					cin.clear();
					cin.ignore(123, '\n');
				}
				expenses = filter.filter_date(expenses, yearTest, monthTest, dayTest, filterType());
				break;
			}
			filterChoice = 'n';
		}
		int count1 = 0;
		int count2 = 0;
		for (int i = 0; i < expenses.size(); i++)
		{
			string spaces1 = expenses[i].get_name();
			string spaces2 = expenses[i].get_category();
			if (spaces1.size() > count1)
				count1 = spaces1.size();
			if (spaces2.size() > count2)
				count2 = spaces2.size();
		}
		for (int i = 0; i <expenses.size(); i++)
		{
			if (i == 0)
			{
				if (i == 0)
				{
					cout << "table structure : ";
					cout << '(';
					cout << "Date\\" ;
					cout << "Name\\";
					cout << "Category\\";
					cout << "Amount\\"  << " Price\\"  << "Description)"  << endl;
					cout << "-----------------------------------------------------------------------" << endl;
				}
			}
		}
		for (int i = 0; i < expenses.size()-2; i++)
		{
			expenses[i].display_data(count1, count2);
			cout << endl;
		}
	}
}
string filterType()
{
	string expression;
	cout << "Enter filter type : ";
	cin >> expression;
	while (expression != ">" && expression != "<" && expression != "<=" &&  expression != ">=" && expression != "=")
	{
		cout << "Enter valid choice :";
		cin >> expression;
	}
	return expression;
}