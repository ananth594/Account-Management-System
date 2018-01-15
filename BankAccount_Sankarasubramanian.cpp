#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <string>

#include "BankAccount_Sankarasubramanian.h"

using namespace std;

void BankAccount::disp_menu()
{
	cout << endl;
	/* the total portfolio value and cash balance of both stock account is
     updated with latest values by reading from tot_acc_bal.txt */
	read_cash_bal();
	cout << " Bank Account " << endl;
	int flag = 0;
	int choice;
	do
	{
		cout << " Please select an option"<<endl;
		cout << "1.View account balance" << endl;
		cout << "2.Deposit money" << endl;
		cout << "3.Withdraw money" << endl;
		cout << "4.Print out history" << endl;
		cout << "5.Return to Previous menu" << endl;
		cin >> choice;
		
		switch (choice)
		{
		case 1:
		{
			view_balance(); // display bank balance
			break;
		}
		case 2: 
		{
			deposit();// deposit money into bank account
			break;

		}

		case 3:
		{
			withdraw();// withdraw money from bank account
			break;

		}
		case 4:
		{
			trans_hist();// display bank transaction history
			break;
			
		}
		case 5:
		{
			write_cash_bal();// update total portfolio value and cash balance and break from loop
			flag = 1;
			break;
			

		}

		default:
		{
			cout << "\nPlease select a valid option!";
		}

		}
	} while (flag == 0);

	

}

void BankAccount::view_balance()// function to display current bank balance
{
	cout <<endl<< " You have $ " << cash_bal << " in your bank acount"<<endl;
	cout << endl;

}

void BankAccount::deposit()// function to deposit money into bank account
{
	cout << endl;
	cout << "Please Enter the amount you wish to deposit: " << endl;
	double amount;
	cin >> amount;
	cash_bal = cash_bal + amount;// update the  the current cash balance
	cout << " You hav deposited $ " << amount << " to your bank account"<< endl;// update total portfolio value
	cout << "The current balance is: $ " << cash_bal << endl;
	cout << endl;
	write_bank_trns("Credit", amount); // write the transaction into bank account)
	
}

void BankAccount::withdraw()
// function to withdraw money from bank account
{
	cout << endl;
	double amount;
	cout << "Please Enter the amount you wish to withdraw:$ " << endl;
	cin >> amount;

	if (amount > cash_bal)// Insufficient Funds
		cout << "Transaction failed!Insufficient funds." << endl;
	else
	{
		cash_bal = cash_bal - amount;// subtract the amount withdrawn from the current cash balance
		cout << "You have withdrawn:$ " << amount << " from your account." << endl;
		cout << "Current balance is:$ " << cash_bal;
		cout << endl;
		write_bank_trns("Debit", amount);// write the transaction
		
	}

	cout << endl;

}

void BankAccount::trans_hist()  // function to display bank transaction history
{
	double amount, balance;
	string event, date;
	
	ifstream fin("bank_transaction.txt", ios::in);
	fin >> event >> amount >> date >> balance;

	if (!fin.eof())
	{
		cout << "Event" << "\t\t" << "Amount" << "\t\t" << "Date" << "\t\t" << "Balance" << endl;
		do	{

			cout << setfill(' ') << setw(4) << event;
			cout << fixed << setprecision(4);
			cout << setfill(' ') << setw(6) << "$" << amount << setfill(' ') << setw(14) << date << setfill(' ') << setw(8) << right << "$" << balance << endl;
			fin >> event >> amount >> date >> balance;
			
			
		} while (!fin.eof());
		fin.close();
	}
	else
		cout << "Transaction history unavailable" << endl;

	cout << endl;
	}



