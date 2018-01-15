#pragma once

#ifndef Account_Sankarasubramanian_h
#define Account_Sankarasubramanian_h

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

class Account
{
public:
	double cash_bal = 0;
	double portfolio_val;
	void read_cash_bal();
	void write_cash_bal();
	void write_bank_trns(string,double);
	void openfiles();
	//void put_graph_values();


};

#endif;
