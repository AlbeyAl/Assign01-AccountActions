#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <string>

using namespace std;

char getActionCodes();
void displayBalance();
void recordAction(char);
double getActionAmount(char);
void writeAction(char, double);
void listActions();
string getActionLabel(char);

int main()
{
	cout << fixed << setprecision(2);

	char answer = getActionCodes();

	while (answer != 'Q' && answer != 'q')
	{
		switch (answer)
		{
		case 'B':
		case 'b':
			displayBalance();
			break;

		case 'C':
		case 'c':
			recordAction('C');
			break;

		case 'D':
		case 'd':
			recordAction('D');
			break;

		case 'W':
		case 'w':
			recordAction('W');
			break;

		case 'L':
		case 'l':
			listActions();
			break;
		}

		cout << '\n';
		system("pause");

		answer = getActionCodes();
	}

    return 0;
}

char getActionCodes()
{
	system("CLS");

	cout << "Enter B  Show Balance ... " << endl
		<< "      C  Record Check ... " << endl
		<< "      D  Make Deposit ... " << endl
		<< "      W  Withdrawal   ... " << endl
		<< "      L  List Actions ... " << endl
		<< "      Q  Quit Program:    ";
	
	char answer = ' ';
	cin >> answer;

	cout << string(2, '\n');

	return answer;
}

void recordAction(char c)
{
	switch (c)
	{
	case 'C':
		writeAction(c, getActionAmount(c));
		break;

	case 'D':
		writeAction(c, getActionAmount(c));
		break;

	case 'W':
		writeAction(c, getActionAmount(c));
		break;
	}
}

string getActionLabel(char c)
{
	string value = "";

	switch (c)
	{
	case 'C':
		value = "check";
		break;

	case 'D':
		value = "deposit";
		break;

	case 'W':
		value = "withdrawal";
		break;
	}

	return value;
}

double getActionAmount(char c)
{
	double value = 0.0;
	cout << "Please enter amount for " + getActionLabel(c) + ": ";
	
	cin >> value;

	return value;
}

void listActions()
{
	// Prime:
	ifstream file;
	file.open("AccountActions.txt");
	
	if (!file.is_open())
	{
		cout << "Please make an initial deposit first..." << '\n';
		return;
	}

	char c = ' ';
	double amount = 0.0;

	file >> c >> amount;

	while (!file.eof())
	{
		string value = "";
		
		switch (c)
		{
		case 'C':
			value = "check";
			value += string(25 - value.length(), ' ') + "-  ";
			break;
		
		case 'D':
			value = "deposit";
			value += string(25 - value.length(), ' ') + "+  ";
			break;
		
		case 'W':
			value = "withdrawal";
			value += string(25 - value.length(), ' ') + "-  ";
			break;
		}

		cout << endl << value << setw(10) << fixed << setprecision(2) <<amount << endl;

		file >> c >> amount;
	}

	displayBalance();
}

void displayBalance()
{
	ifstream file;
	file.open("AccountActions.txt");

	char c = ' ';
	double balance = 0.0;
	double amount = 0.0;

	// Prime:
	file >> c >> amount;

	while (!file.eof())
	{
		string value = "";

		switch (c)
		{
		case 'C':
			balance -= amount;
			break;

		case 'D':
			balance += amount;
			break;

		case 'W':
			balance -= amount;
			break;
		}

		file >> c >> amount;
	}

	string value = "BALANCE of account";
	cout << endl << value << string(25 - value.length(), ' ') + "$  " << setw(10) << fixed << setprecision(2) << balance << endl;
}

void writeAction(char actionCode, double amount)
{
	ofstream file;
	file.open("AccountActions.txt", ios::app);

	file << right << fixed << setprecision(2) << actionCode << setw(10) << amount << '\n';

	file.close();
}