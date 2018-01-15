#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <time.h>
#include <string.h>
#include <random>

#include "StockAccount_Sankarasubramanian.h"


/*
#include<engine.h>
#include<yvals.h>
#if(_MSC_VER>=1600)
#define __STDC_UTF_16__
#endif
#include <mex.h>


#pragma comment(lib, "libmat.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmex.lib")
#pragma comment(lib, "libeng.lib")
*/



using namespace std;

void results::data(string file)
// function to store information in file to data structure

{
	string s1, s2;
	double amount1;
	ifstream get(file, ios::in);
	int i = 0;
	int j = 0;
	int k = 0;

	while (!get.eof())
	{
		get >> s1 >> amount1 >> s2;
		symbol[i++] = s1;
		price[j++] = amount1;
		date[k++] = s2;
	}
	get.close();
}

StockAccount::StockAccount()// constructor that initializes head and tail to NULL
{
	head = NULL;
	tail = NULL;

}

void StockAccount::stock_menu(results r1, results r2, results r3, results r4)// stock account main menu
{
	int ch, flag = 0;
	read_cash_bal();
	cout << "Stock Portfolio Account" << endl;
	do
	{
		cout << endl;
		results r = random_file(r1, r2, r3, r4);
		cout << "Please select an option:" << endl;
		cout << "1.Display the price for a stock symbol" << endl;
		cout << "2.Display the current portfolio" << endl;
		cout << "3.Buy Shares" << endl;
		cout << "4.Sell shares" << endl;
		cout << "5.View a graph for a portfolio value" << endl;
		cout << "6.View Transaction history" << endl;
		cout << "7.Return to previopus menu" << endl;

		cin >> ch;
		switch (ch)
		{
		case 1:
		{
			display_stock_price(r);// display the price of a stock
			break;
		}
		case 2:
		{
			read_current_portfolio(r);// display the current portfolio
			break;
		}
		case 3:
		{
			buy(r); // buy shares
			break;
		}
		case 4:
		{
			sell(r); // sell shares
			break;
		}
		case 5:
		{
			//plot_graph();
				break;
		}
		
		case 6:
		{
			read_trns_history(); // print the stock transaction history
			break;
		}
		case 7:
		{
			write_cash_bal(); //update total portfolio value and cash balance and then break from loop
			flag = 1;
			break;

		}

		}
	} while (flag == 0);
}

results StockAccount::random_file(results r1, results r2, results r3, results r4)
{
	srand(time(NULL));
int random = rand() % 4 + 1;
	switch (random)
	{
			case 1: return r1;
				break;
			case 2: return r2;
				break;
			case 3: return r3;
				break;
			case 4:return r4;
				break;
	}
}
void StockAccount::display_stock_price(results r) // function to display price of a stock
{
	cout << endl;
	string s;
	int flag = 0;

	cout << " Enter the Symbol of the stock:" << endl;
	cin >> s;
	for (int i = 0; i < 49; i++)
	{
		if (s.compare(r.symbol[i]) == 0)// check if symbol in file equal to symbol entered by user
		{
			cout << "Company Symbol" << "\t\t" << "Price Per Share" << endl;
			cout << r.symbol[i] << "\t\t\t\t" << r.price[i] << endl;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		cout << "Symbol not found!" << endl;
	}
	cout << endl;
}

void StockAccount::add_node(node * ptr)// function to add a new node to the doubly linked list
{
	if (head == NULL && tail == NULL)
	{
		ptr->prev = NULL;
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->prev = tail;
		tail->next = ptr;
		tail = ptr;
	}

}
int  StockAccount::search_add_node(node * ptr)
{
	// function to search the doubly linked list to find if a node was previouly added

	string s;
	s = ptr->symbol;
	if (head != NULL && tail != NULL)
	{
		node*temp = head;
		while (temp != NULL)
		{
			if (s.compare(temp->symbol) == 0)// Check if Present
			{
				temp->no_of_shares = temp->no_of_shares + ptr->no_of_shares; //add number of shares to that
				return 1;

			}
			temp = temp->next;
		}
		delete temp;
	}
	return 0;
}

void StockAccount::read_trns_history() // function to read the stock transaction history
{
	cout << endl;
	string event3, symbol, time;
	int num_of_shares;
	double amt, tot_amt;
	ifstream fin("stock_transaction.txt", ios::in);
		fin >> event3 >> symbol >> num_of_shares >> amt >> tot_amt>>time;
		if (!fin.eof())
		{
			cout << "Event" << "\t" << "Company-Symbol" <<"\t\t" <<"  Number of Shares" << "\t" << "Price per Share" << "\t\t" << "Total Price" << "\t\t" << "Time" << endl;
			while (!fin.eof())
			{
				cout << setw(4) << event3 << "\t\t";
				cout << setw(4) << symbol << "\t\t\t";
				cout << setw(4) << num_of_shares << "\t\t" << setw(4) << amt << "\t\t\t" << setw(4) << tot_amt << "\t\t\t" << setw(4) << time << endl;
				fin >> event3 >> symbol >> num_of_shares >> amt >> tot_amt>>time;

			}
			fin.close();
		}
		else 
			cout << "Stock transaction History Unavailable!" << endl;
		cout << endl;

}

void StockAccount::write_trns_history(string b_s, string s, int num_of_shares, double price, double totalPrice)
{	

	// get the current time and convert time to local time
	time_t currentTime;
	struct tm *localTime;
	time(&currentTime); 
	localTime = localtime(&currentTime); 
	int hour = localTime->tm_hour;
	int min = localTime->tm_min;
	int sec = localTime->tm_sec;



	
	ofstream fout("stock_transaction.txt", ios::app);
	fout << " " << b_s << "\t\t\t" << s << "\t\t\t" << num_of_shares << "\t\t " << price << "\t\t " << totalPrice << "\t   " << hour << ":" << min << ":" << sec << endl;
	fout.close();
}

void StockAccount::from_portfolio_to_Dll()// function to copy information from current_portfolio.txt to the doubly linked list
{
	string s;
	int num_of_shares;
	double price, tot_price;
	ifstream fin("portfolio.txt", ios::in);
	fin >> s >> num_of_shares >> price >> tot_price;
	while (!fin.eof())
	{
		node * ptr = new node;
		ptr->symbol = s;
		ptr->no_of_shares = num_of_shares;
		add_node(ptr);
		fin >> s >> num_of_shares >> price >> tot_price;

	}
	fin.close();
}

void StockAccount::write_current_portfolio(results r)// function to store the current portfolio
{
	cout << endl;
	portfolio_val = cash_bal;
	node *temp = head;
	ofstream fout("portfolio.txt", ios::trunc);
	while (temp != NULL)
	{
		fout << temp->symbol << "\t\t" << temp->no_of_shares;
		int flag = 0;
		for (int i = 0; i < 49; i++)
		{
			if (temp->symbol.compare(r.symbol[i]) == 0)
			{
				double tot_price = r.price[i] * temp->no_of_shares;
				fout << "\t\t" << r.price[i] << "\t\t" << tot_price << endl;
			}
		}
		temp = temp->next;
	}
	fout.close();

	cout << endl;
}

void StockAccount::read_current_portfolio(results r)// function to read the current portfolio
{
	cout << endl;
	string s;
	int num_of_shares;
	double price, tot_price;
	double tot_port_val = 0;
	if (head != NULL)
	{
		cout << endl;
		cout << "Current Portfolio" << endl;
		cout << "Cash Balance" << cash_bal << endl;
		cout << "Company-Symbol" << "\t\t" << "Number of Shares" << "\t\t" << "Price per share" << "\t\t" << "Total Value" << endl;
		ifstream fin("portfolio.txt", ios::in);
		fin >> s >> num_of_shares >> price >> tot_price;
		
		while (!fin.eof())
		{	
			tot_port_val += tot_price;
			cout << setw(4) << s << "\t\t\t";
			cout << setw(4) << num_of_shares << "\t\t\t\t" << setw(4) << price << "\t\t\t" << setw(4) << tot_price << endl;
			fin >> s >> num_of_shares >> price >> tot_price;
			

		}
		fin.close();
		cout << "Total Portfolio Value: " << tot_port_val << endl;
	}

	else
		cout << "No shares held!" << endl;
	cout << endl;
}

void StockAccount::bubble_sort(results r)// function to keep the doubly linked list sorted at all times using bubble sort
{
	if (head == NULL)
		return;
	if (head->next == NULL)
		return;

	node *temp = new node;
	node *temp2 = new node;
	int ct = 1;
	double n1, n2;
	while (ct)
	{
		ct = 0;
		temp = head;
		while (temp->next != NULL)
		{
			int flag = 0;
			for (int i = 0; i < 49; i++)
			{
				if (flag == 0)
				{
					if (temp->symbol.compare(r.symbol[i]) == 0)
					{
						n1 = temp->no_of_shares * r.price[i];
						flag = 1;

					}

				}
			}
			flag = 0;
			for (int i = 0; i < 49; i++)
			{
				if (flag == 0)
				{
					if (temp->next->symbol.compare(r.symbol[i]) == 0)
					{
						n2 = temp->next->no_of_shares*r.price[i];
						flag = 1;

					}
				}
			}
				if (n1 < n2)
				{
					ct = 1;
					temp2->symbol = temp->symbol;
					temp->symbol = temp->next->symbol;
					temp->next->symbol = temp2->symbol;

					temp2->no_of_shares = temp->no_of_shares;
					temp->no_of_shares = temp->next->no_of_shares;
					temp->next->no_of_shares = temp2->no_of_shares;

				}
				temp = temp->next;
			}

		
	}
}

void StockAccount::buy(results r)// function to enable user to buy stock
{
	node * ptr = new node;
	cout << "Enter the stock you wish to purchase:" << endl;
	cin >> ptr->symbol;
	cout << "Enter the Number of shares you wish to purchase" << endl;
	cin >> ptr->no_of_shares;
	cout << "Enter the maximum amount you are willing to pay per share :" << endl;
	int max;
	int flag = 0;
	cin >> max;

	if (max > cash_bal)// print error if insufficient funds
		cout << "Transaction Unsuccessful!Insufficient Funds." << endl;
	else
	{
		for (int i = 0; i < 49 && flag == 0; i++)
		{
			if (ptr->symbol.compare(r.symbol[i]) == 0)
			{
				if (r.price[i] > max)
				{
					cout << "Transaction failed! Cost per stock greater than max value." << endl;
					flag = 1;

				}
				else// the user purchases shares
				{
					double totalPrice = ptr-> no_of_shares * r.price[i];
					cout << "You have purchased " << ptr->no_of_shares << " share(s) of" << ptr->symbol << " at $ " << r.price[i] << " totalling  to $ " << totalPrice << endl;
					cash_bal = cash_bal - totalPrice;
					write_trns_history("Buy", ptr->symbol, ptr->no_of_shares, r.price[i], totalPrice);// write the transaction (Stock Side)
					write_bank_trns("Debit", totalPrice);// write the transaction(Bank Side)

					int z = search_add_node(ptr);// Search Existence of a node
					if (z == 0)
						add_node(ptr);
					else
						delete ptr;
					
														// bubble sort after each buy operation
					bubble_sort(r);
					
					write_current_portfolio(r);
					flag = 1;


				}
			}
		}
		if(flag ==0)
		{
			cout << "The stock is unavailable" << endl;
	}
}


}

void StockAccount::sell(results r)// function to enable user to sell stock
{
	string s;
	int num_of_shares;
	double min;

	cout << "Enter the ticker symbol of the stock you want to sell: "<<endl;// get input from user
	cin >> s;
	cout << "Enter the number of shares you want to sell: "<<endl;
	cin >> num_of_shares;
	cout << "Enter the minimum amount you want to sell each share of the stock for: $ "<<endl;
	cin >> min;
	int flag = 0;
	double price;
	node *temp = head;
	while (temp != NULL && flag == 0)
	{
		if (temp->symbol.compare(s) == 0)// check if the symbol entered by user is present in the doubly linked list
		{
			int flag1 = 0;
			for (int i = 0; i < 49 && flag1 == 0; i++)
			{
				if (temp->symbol.compare(r.symbol[i]) == 0)
				{
					price = r.price[i];
					flag1 = 1;
				}
			}

			// print error if actual price of a share is less than what the user is willing to pay
			if (price < min) cout << "\nTransaction failed! Price per share of the stock is lower than what you are willing to sell for.\n";

			
			else if (temp->no_of_shares < num_of_shares) cout << "\nTransaction failed! There are insufficient shares of " << s << ".\n";

			else//  user sell shares
			{
				double totalPrice = (num_of_shares * price);
				cash_bal += totalPrice;
				temp->no_of_shares -= num_of_shares;
								
				if (temp->no_of_shares == 0)
				{
					if (head == tail) head = tail = NULL;
					else if (temp == head)
					{
						head = head->next;
						head->prev = NULL;
					}
					else if (temp == tail)
					{
						tail = tail->prev;
						tail->next = NULL;
					}
					else
					{
						node *temp1 = temp->prev;
						node *temp2 = temp->next;
						temp2->prev = temp1;
						temp1->next = temp2;
					}
				}

				cout << "\nYou have sold " << num_of_shares << " share(s) of " << s << " at $" << price << " each for a total of $" << totalPrice << ".\n";
								
				write_trns_history("Sell", s, num_of_shares, price, totalPrice);// write the transaction (Stock Side)

				write_bank_trns("Credit", totalPrice);// write the transaction (Bank Side)

				
				bubble_sort(r);// bubble sort after each sell operation

			
				write_current_portfolio(r);// Update Current Portfolio
			}
			flag = 1;
		}
		temp = temp->next;
	}

	// print error if user is trying to sell a stock he/she doesn't have
	if (flag == 0) cout << "Transaction failed! You can't sell because you don't have shares of " << s << " at all!"<<endl;
	cout << endl;
}

/*
void StockAccount::plot_graph()
{
	double totalAmount, amount;
	int time1, n = 0;
	string date1;
	
	ifstream get("portfolio_history.txt", ios::in);
	get >> totalAmount >> amount >> date1 >> time1;
	if (!get.eof())
	{
		Engine *ep;
		ep = engOpen(NULL);
		if (ep == NULL)
		{
			cout << "\nError";
			exit(0);
		}

		double x[100];
		double y[100];
		int i = 0;
		while (!get.eof())
		{
			x[i] = time1;
			y[i] = totalAmount;
			get >> totalAmount >> amount >> date1 >> time1;
			i++;
		}
		get.close();

		mxArray* m_X;
		mxArray* m_Y;

		m_X = mxCreateDoubleMatrix(1, n, mxREAL);
		m_Y = mxCreateDoubleMatrix(1, n, mxREAL);

		memcpy((void*)mxGetPr(m_X), (void*)x, sizeof(double) * n);
		memcpy((void*)mxGetPr(m_Y), (void*)y, sizeof(double) * n);
		
		engPutVariable(ep, "x", m_X);
		engPutVariable(ep, "y", m_Y);
		
		engEvalString(ep, "plot(x,y);");
	}
	else cout << "\nNo portfolio history present to plot a graph!\n";
}
*/
