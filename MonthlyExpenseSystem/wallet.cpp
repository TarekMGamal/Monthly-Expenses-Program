#include "wallet.h"
#include <fstream>
#include <stack>
#include "FileHandler.h"
Wallet::Wallet()
{
	
}

Wallet::Wallet(string Walletname, int totalMoney)
{
    this->WalletName = Walletname;
    income = totalMoney;

	FileHandler handler;
	handler.makeWallet(WalletName);

	
}

void Wallet::saveIncome(float income)
{

    fstream incomes("Data\\incomes.txt", ios::app);

	incomes << WalletName << '[' << income << ';';

	incomes.close();
}

void Wallet::setName(string walletName)
{
	this->WalletName = walletName;
}



void Wallet::increaseIncome(float increase,vector<string> walletsName,int chosenWallet)
{
	vector<float> incomes;
	float old_income;
	for (int i = 0; i < walletsName.size(); i++)
	{
		old_income = loadRemaning(walletsName[i]);

		if (i == chosenWallet - 1)
			old_income += increase;

		incomes.push_back(old_income);
		

	}
	
		saveIncomes(walletsName,incomes);

	

	
}

void Wallet::saveIncomes(vector<string> walletsName, vector<float> incomes)
{
	FileHandler handler;
	handler.textFile.open("Data\\incomes.txt", ios::out);
	
	for (int i = 0; i < walletsName.size(); i++)
	{
		handler.textFile << walletsName[i] << '[' << incomes[i]<<';';
	}

	handler.textFile.close();
}

float Wallet::loadRemaning(string walletName)
{

	fstream textFile;
	textFile.open("Data\\incomes.txt",ios::in);
	
	string line;
	// save it to value this is better 
	string value;
	if (textFile.is_open())
	{
		
		while (getline(textFile, line, ';') )
		{
			
			vector<string>text = FileHandler::split(line, "[");

			
				if (text[0] == walletName)
				{
					
					value = text[1];  // gets last thing before ; which is the number

					//break; to get the last wallet value
				}

			
			

			
			
		}


		textFile.close();

		return stof(value);

	}


	return(1);

    


}

float Wallet::loadIncome(string walletName)
{
	fstream textFile;
	textFile.open("Data\\incomes.txt", ios::in);

	string line;
	// save it to value this is better 
	string value;
	if (textFile.is_open())
	{

		while (getline(textFile, line, ';'))
		{

			vector<string>text = FileHandler::split(line, "[");


			if (text[0] == walletName)
			{

				value = text[1];  // gets last thing before ; which is the number

				//break; to get the last wallet value
			}






		}


		textFile.close();

		return stof(value);

	}


	return(1);


}





 float Wallet::getTotalMoney()
{

	 //this code can't sum the last edited money
	fstream textFile;
	textFile.open("Data\\incomes.txt");

	string line;
	float sum = 0;
	if (textFile.is_open())
	{
		while (getline(textFile, line, ';'))
		{
			vector<string>text = FileHandler::split(line, "[");
				if(text[1] !="")
				sum+= stof(text[1]);  // gets last thing before ; which is the number
		}
		textFile.close();
		//system("pause");
		return sum;

	}


	return(1);
}

 void Wallet::setExpenses(vector<Expense> expensesList)
 {
	 expenses = expensesList;
 }

void Wallet::viewExpenses(vector<Expense> allExpenses)
{
    for (int expense = 0; expense < allExpenses.size(); expense++)
    {
    }
}

// Do I have money to buy or I have borrowed ? 
bool Wallet::checkWallet()
{

    if (income > 0)
        return true;

    return false;
}

Wallet::~Wallet()
{
}
