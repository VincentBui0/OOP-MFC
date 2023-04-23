#include <iostream>
#include <string>

using namespace std;

#include "stdafx.h"


#pragma once

#ifndef NET_H
#define NET_H

class Net :public CObject
{
public:
	Net(CString&, double, double, double);
	friend ostream& operator<<(ostream&, const Net*);

	int operator > (Net* p);

	bool operator==(CString s);
	bool operator >=(Net* p);

	static int getcount();

	static void printtotals();

private:
	CString lastname;
	double previousbalance, payments, charges;
	double newbalance, financecharge, monthendbalance;


	static double totalmonthendbalance;
	static int count;

	void compute();

};
#endif