#pragma once

#ifndef BankAccount_Sankarasubramanian_h
#define BankAccount_Sankarasubramanian_h

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

#include "Account_Sankarasubramanian.h"

using namespace std;

class BankAccount : public Account
{

public :
	void disp_menu();
	void deposit();
	void withdraw();
	void view_balance();
	void trans_hist();
	};

class TimeImp
{
public:
	TimeImp(int h, int m)
	{
		hour = h;
		min = m;
	}
	virtual void tell()
	{
		cout << "Current time is " << hour << min << endl;
	}
protected:
	int hour, min;
};

class CivilianTimeImp : public TimeImp
{
public:
	CivilianTimeImp(int h, int m, int amPM) : TimeImp(h, m)
	{
		if (amPM) strcpy(thisOrThat, " PM");
		else strcpy(thisOrThat, " AM");
	}
	void tell()
	{
		cout << "You exited at " << hour << ":" << min << thisOrThat << endl;
	}
protected:
	char thisOrThat[4];
};

class Time
{
public:
	Time() {}
	Time(int h, int m)
	{
		imp = new TimeImp(h, m);
	}
	virtual void tell()
	{
		imp->tell();
	}
protected:
	TimeImp *imp;
};

class CivilianTime : public Time
{
public:
	CivilianTime(int h, int m, int amPM)
	{
		imp = new CivilianTimeImp(h, m, amPM);
	}
};
#endif