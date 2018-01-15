#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

#include "Account_Sankarasubramanian.h"
#include "BankAccount_Sankarasubramanian.h"
#include "StockAccount_Sankarasubramanian.h"

int main()
{
	int choice;
	
	results r1,r2,r3,r4;
	r1.data("Result_1.txt");// storing the 4 result.txt files with random values into a data structure
	r2.data("Result_2.txt");
	r3.data("Result_3.txt");
	r4.data("Result_4.txt");

	BankAccount obj1;  // object of class StockAccount
	StockAccount obj2;// object of class BankAccount

	obj1.openfiles();
	obj2.from_portfolio_to_Dll();  //Information in current_portfolio.txt is copied to the double linked list

	obj1.read_cash_bal();
	obj2.read_cash_bal();

	cout << "Welcome to the account Management System!" << endl;
	do
	{
		cout << endl;
		cout << "Please select an account to access:"<<endl;
		cout << " 1.Stock Account " << endl;
		cout << " 2.Bank Account" << endl;
		cout << " 3.Exit" << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			obj2.stock_menu(r1, r2, r3, r4);// print stock account menu 
			break;
		}
		case 2:
		{
			obj1.disp_menu();// print bank account menu
			break;
		}
		case 3:
			//obj2.put_graph_values();
			exit(0);

		default:cout << "Please Select a valid Option!" << endl;
		}
	} while (1);
	
	
	return 0;
}