#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "Net.h"

int Net::count = 0;
double Net::totalmonthendbalance = 0;

Net::Net(CString& lname, double pe, double ps, double cs)
{
	lastname = lname;
	previousbalance = pe;
	payments = ps;
	charges = cs;

	compute();

}

void Net::compute()
{
	newbalance = previousbalance - payments;
	financecharge = newbalance * .12;
	monthendbalance = newbalance + financecharge;

	count = count + 1;
	totalmonthendbalance += monthendbalance;

}

ostream& operator<<(ostream& cout, const Net* p)
{
	cout << setw(15) << p->lastname << setw(15) << p->previousbalance
		<< setw(15) << p->payments
		<< setw(15) << p->charges << setw(15) << p->newbalance
		<< setw(15) << p->financecharge << setw(15) << p->monthendbalance << endl;

	return cout;
}

void Net::printtotals()
{
	cout << endl;
	cout << "Total month end balance" << totalmonthendbalance << endl;
	cout << "Number of objects created" << count << endl;
}

int Net::getcount()
{
	return count;
}

int Net::operator > (Net* p)
{
	if (this->monthendbalance > p->monthendbalance)
		return 1;
	else
		return 0;
}

bool Net::operator==(CString s)
{
	if (lastname == s)
		return true;
	else
		return false;
}

bool Net::operator >= (Net* person)
{
	if (lastname >= person->lastname)
		return true;
	else
		return false;
}