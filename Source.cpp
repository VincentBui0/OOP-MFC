#include <iostream>
#include <iomanip>
using namespace std;

#include "afxwin.h"

#include <afxdb.h>

#include "Net.h"

void printheading();
void printreport(Net* person[]);
void printhighest(Net* person[]);
void getsearch(Net* person[]);
void getsort(Net* person[]);

int main()
{
	system("cls");
	system("Color 70");

	CString Connection;
	CDatabase database;

	CString username;
	CString password;

	username = "MSI\\SQLSERVEREXPRESS\\Vincent Bui";

	Connection = _T("Driver={SQL Server Native Client 11.0};Server=MSI\\SQLSERVEREXPRESS;AttachDbFilename=C:\\VisualStudio\\DataBases\\MonthEndBalance\\MonthEndBalanceSQL.mdf;Trusted_Connection=Yes;Uid=")
		+ username + _T(";Pwd=") + password + _T(";");
	

	database.OpenEx(Connection, CDatabase::useCursorLib);

	const int size = 10;

	Net* person[size];

	int i = 0;

	CString query = "SELECT LastName, PreviousBalance, Payments, Charges from MonthEndTable";

	CRecordset recordset(&database);
	CString temp, record;
	recordset.Open(CRecordset::forwardOnly, query, CRecordset::readOnly);

	CString lastname, spreviousbalance, spayments, scharges;

	double previousbalance, payments, charges;

	while (!recordset.IsEOF())
	{
		record = _T("");
		register int len = recordset.GetODBCFieldCount();

		recordset.GetFieldValue("LastName", lastname);
		recordset.GetFieldValue("PreviousBalance", spreviousbalance);
		recordset.GetFieldValue("Payments", spayments);
		recordset.GetFieldValue("Charges", scharges);

		previousbalance = atof(spreviousbalance);
		payments = atof(spayments);
		charges = atof(scharges);

		person[i++] = new Net(lastname, previousbalance, payments, charges);

		recordset.MoveNext();

	}

	printheading();
	printreport(person);
	printhighest(person);
	getsearch(person);
	getsort(person);
	printreport(person);
	cout << endl << endl;
	return 0;

}

void printheading()
{
	cout << setw(30) << "Month End Balance Report" << endl;
	cout << setw(12) << "LastName" << setw(12) << "PreviousBalance" << setw(12)
		<< "Payments" << setw(12) << "Charges" << endl << endl;
}

void printreport(Net* person[])
{
	int num = Net::getcount();

	for (int st = 0; st < num;st++)
	{
		cout << person[st];
	}

	Net::printtotals();
}

void printhighest(Net* person[])
{
	int num;

	num = Net::getcount();
	Net* top = person[0];

	for (int st = 1; st < num; st++)
	{
		if (*person[st] > top)
			top = person[st];

	}
	cout << "\nThe person with the highest pieces:\n";
	cout << top;
}

void getsearch(Net* person[])
{
	int num, index = 0;
	char name[20];

	CString namsearch;
	cout << "\nEnter the name to search";
	cin >> name;

	namsearch = CString(name);
	bool found = false;

	num = Net::getcount();
	int x = 0;

	while ((found != true) && (x <= num))
	{
		if (*person[x] == namsearch)
		{
			cout << person[x];
			found = true;
		}
		x++;
	}
	if (found == false)
		cout << "Object not found" << endl;
}

void getsort(Net* person[])
{
	cout << "Sorted" << endl;
	Net* temp;
	int num = Net::getcount();
	for (int pass = 1; pass < num;pass++)
	{
		for (int i = 0; i < num - 1;i++)
		{
			if (*person[i] >= person[i + 1])
			{
				temp = person[i];
				person[i] = person[i + 1];
				person[i + 1] = temp;
			}
		}
	}
}