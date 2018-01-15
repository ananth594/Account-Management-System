#include "Account_Sankarasubramanian.h"
#include "BankAccount_Sankarasubramanian.h"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>

using namespace std;

void Account::write_cash_bal()
{
	ofstream fout("tot_acc_bal.txt", ios::trunc);// write the values of total portfolio value and cash balance
	fout << portfolio_val << "\t\t" << cash_bal;
	fout.close();

}

void Account::read_cash_bal()// read the values of total portfolio value and cash balance
{
	double tot_bal, bal;
	ifstream fin("tot_acc_bal.txt", ios::in);
	fin >> tot_bal >> bal;
	portfolio_val = tot_bal;
	cash_bal = bal;
	fin.close();
	
}

void Account:: write_bank_trns(string w_d, double amount)
{
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	int year = (now->tm_year + 1900);
	int month = (now->tm_mon + 1);
	int day = now->tm_mday;

	ofstream fout("bank_transaction.txt", ios::app);// store the event, amount withdrawn/deposited, date and cash balance
	fout << w_d << "/t/t" << "\t" << amount << "\t" << month << "/" << day << "/" << year << "\t" << cash_bal<<endl;
	fout.close();


}

void Account::openfiles()
{
	ofstream fout("tot_acc_bal.txt",ios::app);
	fout.close();

	ofstream fout2("bank_transaction.txt",ios::app);
	fout.close();

	ofstream fout3("portfolio.txt", ios::app);
	fout3.close();

	ofstream fout4("stock_transaction.txt", ios::app);
	fout4.close();

	ofstream fout5("portfolio_history.txt", ios::app);
	fout5.close();


	int no_of_shares;
	double price, tot_price;
	string  event1, symbol, time;
	ifstream fin("stock_transaction_history.txt", ios::in);
	fin >> event1 >> symbol >> no_of_shares >> price >> tot_price >> time;

	double amount, balance;
	string event2, date;
	ifstream fin2("bank_transaction.txt", ios::in);
	fin2 >> event2 >> amount >> date >> balance;

	if (fin2.eof())
	{
		portfolio_val = 10000;
		cash_bal = 10000;
		write_cash_bal();
		write_bank_trns("Credit", cash_bal);

	}

}

/*
void Account::put_graph_values()
{
	
	ifstream get("tot_acc_bal.txt", ios::in);
	double totalAmount, amount;
	get >> totalAmount >> amount;

	// get the current time and convert time to local time
	time_t currentTime;
	struct tm *localTime;
	time(&currentTime); // get the current time
	localTime = localtime(&currentTime); // convert the current time to the local time
	int day = localTime->tm_mday;
	int month = localTime->tm_mon + 1;
	int year = localTime->tm_year + 1900;
	int hour = localTime->tm_hour;
	int min = localTime->tm_min;
	int sec = localTime->tm_sec;

	// store the total portfolio value, cash balance, date and time in portfolio_history.txt
	ofstream put("portfolio_history.txt", ios::app);
	put << totalAmount << "\t\t" << amount << "\t\t" << month << "/" << day << "/" << year << "\t\t" << hour << min << endl;
	put.close();

	// thank you note while exiting
	cout << "\nThank you for using your Accounts!\n";
	Time *timeone;
	int amPM;
	if (hour > 12 && hour < 23) amPM = 1;
	else amPM = 0;
	timeone = new CivilianTime(hour, min, amPM);
	timeone->tell();
	cout << endl;
}
*/

