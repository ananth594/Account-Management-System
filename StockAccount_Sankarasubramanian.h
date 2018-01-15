#pragma once

#ifndef StockAccount_Sankarasubramanian_h
#define StockAccount_Sankarasubramanian_h

#include "Account_Sankarasubramanian.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

class results
{
public:
	string symbol[50];
	double price[50];
	string date[50];
	void data(string);
	
};

class node
{
	friend class StockAccount;

private:
		node *next; //pointer to the previous node
		node *prev;//pointer to the next node
		string symbol;
		int no_of_shares;

public:
	node() // constructor to initialize any new node
	{
		prev = next = NULL;

	}

};


class StockAccount : public Account
{
private:

	node *head;
	node *tail;

public:
	StockAccount();
	void stock_menu(results r1 , results r2, results r3, results r4);
	results random_file(results, results, results, results);
	void display_stock_price(results);
	void add_node(node *);
	int  search_add_node(node *);
	void  write_trns_history(string, string, int, double, double);
	void read_trns_history();
	void from_portfolio_to_Dll();
	void write_current_portfolio(results);
	void read_current_portfolio(results);
	void bubble_sort(results);
	void buy(results);
	void sell(results);
	//void plot_graph();
};

#endif








