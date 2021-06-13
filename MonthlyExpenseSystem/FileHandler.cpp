


#include "FileHandler.h"
#include "Expense.h"
//expenses section



int FileHandler::getNumberOfWallets()
{
	return nofWallets;
}

vector<string> FileHandler::split(string s, string del)
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

void FileHandler::countExpenses(string currentWallet)
{
	nofExpenses = 0;
	currentWallet = "Data\\" + currentWallet;
	textFile.open(currentWallet,ios::in);

	int begin = 0;

	string line;

	if (textFile.is_open())
	{

		while (getline(textFile,line,';'))
		{
			nofExpenses++;

			//cout << "Number of expenses" << nofExpenses;
		}

		textFile.close();
	}
	
}

void FileHandler:: saveExpense(string walletName,exspense_info info)

	{
	if (info.amount != -1){
		walletName = "Data\\" + walletName;
		textFile.open(walletName, ios::app);

		if (textFile.is_open())
		{
			

		textFile << info.date << ',' << info.description 

			<< ',' << info.category << ',' << info.amount << ',' << info.price << ',' << info.name << ';';

					
		textFile.close();
		}
	}
	}

	void  FileHandler:: rewriteExpense(Expense expense)
	{

	}

	vector<Expense> FileHandler::loadWallet(string walletName)
	{

		countExpenses(walletName);

		vector <Expense> expenses(nofExpenses);
		if (nofExpenses < 1)
		{
			return   vector<Expense> (1);
		}
		

	


		textFile.open("Data\\"+walletName);
		
		string line;
		if (textFile.is_open())
		{
			int i = 0;
			while (getline(textFile,line,';'))
			{
				exspense_info expenseInfo(split(line, ","));

				expenses[i] = Expense(expenseInfo);

				//cout << line;
				i++;
			}

			
			textFile.close();

		}
		


		return expenses;
	}

	void  FileHandler:: eraseExpense(Expense expense)
	{

	}

//wallet section


	Wallet FileHandler::findWallet(string walletName)
	{

		string foundedWallet = "";

		// this gets all the wallets names
		//C:\\Users\\mercy\\source\\repos\\MonthlyExpenses-Manager-System\\MonthlyExpenseSystem\\Data
		//C:\\Users\\ahmed\\source\\repos\\MonthlyExpenses-Manager-System\\MonthlyExpenseSystem\\Data
		string path = "C:\\Users\\ahmed\\source\\repos\\MonthlyExpenses-Manager-System\\MonthlyExpenseSystem\\Data";
		for (const auto& entry : fs::directory_iterator(path))
		{
			foundedWallet = entry.path().filename().string();
			if ( foundedWallet == walletName)
			{
				foundedWallet = entry.path().filename().string();

				cout << "the wallet     : " << foundedWallet << " has been found";
				break;
			}
			
			foundedWallet = "";

		}


		// needs to be revised
		Wallet wallet;

		if (foundedWallet == "")
			return wallet;


		else
		{
			
			return  wallet;
		}
		
	

	}

	vector<string> FileHandler::  scanAllWallets()
	{
		nofWallets = 0;
		// this gets all the wallets names
		vector<string>wallets;
		//C:\\Users\\ahmed\\source\\repos\\MonthlyExpenses - Manager - System\\MonthlyExpenseSystem\\Data


		string path = "C:\\Users\\ahmed\\source\\repos\\MonthlyExpenses-Manager-System\\MonthlyExpenseSystem\\Data";
			
		for (const auto& entry : fs::directory_iterator(path))
		{
			string walletName = entry.path().filename().string();
			if (walletName == "incomes.txt")
				continue;
			//std::cout <<"Enter "<<nofWallets+1<<"- "<< walletName  << std::endl;
			
			wallets.push_back(walletName);

			nofWallets++;
		}

		
			
		return wallets;
	}

	string FileHandler::chooseWalletFile(int myChoice)
	{
		string walletName = "";

		
		cout << "Enter 1 for cash wallet" << endl;
		cout << "Enter 2 for credit card wallet" << endl;
		cout << "Enter 3 for debit card wallet" << endl;
		vector<string> walletsNames = scanAllWallets();
		 if (myChoice == 3)
			 cout << "Enter 4 for all" << endl;
		 cin >> walletName;
		while (walletName != "1" && walletName != "2" && walletName != "3" )
		{
			bool flag = false;
			if (myChoice == 3)
				while (walletName != "1" && walletName != "2" && walletName != "3" && walletName == "4")
				{
					flag = true;
					break;
				}
				if (flag == true)
					break;
			cout << "Enter valid choice : ";
			cin >> walletName;
		}

		int chosenWallet = stoi(walletName);
		for (int i = 1; i < walletsNames.size() + 1; i++)

			if (chosenWallet == i)
			{
				walletName = walletsNames[i - 1];

				break;
			}

		
		if (chosenWallet == 4)
			walletName = "4";
	
		return walletName;
	}

	void FileHandler:: deleteWallet(Wallet wallet)
	{

	}
	void FileHandler::makeWallet(string name)
	{
		name = "Data\\" + name;
		fstream WalletFile(name, ios::out | ios::app);
	}

	

	float FileHandler::totalExpenses(string walletName)
	{
		float total = 0;
		
			countExpenses("Data\\"+walletName);

			vector <Expense> expenses(nofExpenses);
			textFile.open("Data\\" + walletName, ios::in);

			string line;

			if (textFile.is_open())
			{
				int i = 0;
				while (getline(textFile, line, ';'))
				{
					exspense_info expenseInfo(split(line, ","));

					expenses[i] = Expense(expenseInfo);
					total += (expenses[i].get_amount() * expenses[i].get_price());
					i++;
				}
				textFile.close();


				return total;

			}
	}

	FileHandler::FileHandler() {
	// TODO Auto-generated constructor stub

	nofWallets = 0;
	nofExpenses = 0;

}
float FileHandler::totalPrices()
{
	vector<string>wallets = scanAllWallets();
	nofWallets = wallets.size();

	float total = 0;
	for (int i = 0; i < nofWallets; i++)
	{
		countExpenses(wallets[i]);

		vector <Expense> expenses(nofExpenses);
		textFile.open("Data\\"+wallets[i], ios::in);

		string line;
		
		if (textFile.is_open())
		{
			int i = 0;
			while (getline(textFile, line, ';'))
			{
				exspense_info expenseInfo(split(line, ","));

				expenses[i] = Expense(expenseInfo);
				total += (expenses[i].get_amount() * expenses[i].get_price());
				i++;
			}
			textFile.close();

		}
	}
	
	
	
	return total;
}
FileHandler::~FileHandler() {
	// TODO Auto-generated destructor stub
}

