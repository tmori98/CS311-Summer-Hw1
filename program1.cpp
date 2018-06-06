#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>

using namespace std;

// Define structs below
struct  Money
{
    int dollars;
    int cents;
};
struct  Account 
{
	Money	balance;
	double	rate;
	string name;
};
// Declare functions to do with Accounts and Money
Account	createAccount(string	name);
Account createAccount(string name, double rate, Money balance);
Account deposit(Account account, Money deposit);
Money withdraw(Account &account, Money withdraw);
void accrue(Account &account);
void print(Money account);
void print(Account account);

// TEST HELPER FUNCTIONS -- DO NOT ALTER
int makePennies(Money m);
Money makeMoney(int p);
bool isNegative(Money m);
bool operator<(const Money& lhs, const Money& rhs);

// TEST FUNCTIONS -- DO NOT ALTER
bool testCreateAccountFile(bool n);
bool testCreateAccountParams();
bool testDeposit(Money dep);
bool testWithdraw(Money w);
bool testAccrue();
void testPrint(bool type, bool sign);

int main()
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	// DO *NOT* ALTER THE MAIN FUNCTION
	int width = 50;
	char prev = std::cout.fill('.');
	std::cout << "\n--- Homework 1 Tests ---\n";
	std::cout << std::setw(width) << std::left << "createAccount(filename)" << testCreateAccountFile(true) << std::endl;
	std::cout << std::setw(width) << std::left << "createAccount(bad filename)" << testCreateAccountFile(false) << std::endl;
	std::cout << std::setw(width) << std::left << "createAccount(parameters)" << testCreateAccountParams() << std::endl;
	std::cout << "\n--- Begin Depost Testing ---\n";
	std::cout << std::setw(width) << std::left << "Deposit Message"; bool temp = testDeposit({10, 0});
	std::cout << std::setw(width) << std::left << "deposit()" << temp << std::endl;
	std::cout << std::setw(width) << std::left << "\nDeposit Message"; temp = testDeposit({0, -75});
	std::cout << std::setw(width) << std::left << "deposit() (negative deposit)" << temp << std::endl;
	std::cout << "--- End Deposit Testing ---\n\n";
	std::cout << "\n--- Begin Withdraw Testing---\n";
	std::cout << std::setw(width) << std::left << "Withdrawl Message"; temp = testWithdraw({10, 36});
	std::cout << std::setw(width) << std::left << "withdraw()" << temp << std::endl;
	std::cout << std::setw(width) << std::left << "\nWithdrawl Message"; temp = testWithdraw({60, 10});
	std::cout << std::setw(width) << std::left << "withdraw() (partial overdraft)" << temp << std::endl;
	std::cout << std::setw(width) << std::left << "\nWithdrawl Message"; temp = testWithdraw({200, 78});
	std::cout << std::setw(width) << std::left << "withdraw() (full overdraft)" << temp << std::endl;
	std::cout << std::setw(width) << std::left << "\nWithdrawl Message"; temp = testWithdraw({-3, -50});
	std::cout << std::setw(width) << std::left << "withdraw() (negative withdraw)" << temp << std::endl;
	std::cout << "--- End Withdraw Testing---\n\n";
	std::cout << "\n--- Begin Accrue Test ---\n";
	std::cout << std::setw(width) << std::left << "Accrue Message"; temp = testAccrue(); std::cout << std::endl;
	std::cout << std::setw(width) << std::left << "accrue()" << temp << std::endl;
	std::cout << "--- End Accrue Test ---\n\n";
	std::cout << std::setw(width) << std::left << "print() (Money) [Expect $567.32]"; testPrint(false, true); std::cout << std::endl;
	std::cout << std::setw(width) << std::left << "print() (Money) (negative) [Expect ($567.32)]"; testPrint(false, false); std::cout << std::endl;
	std::cout << std::setw(width) << std::left << "print() (Account) [Expect $567.32]"; testPrint(true, true); std::cout << std::endl;
	std::cout << std::setw(width) << std::left << "print() (Account) (negative) [Expect ($567.32)]"; testPrint(true, false); std::cout << std::endl;

	std::cout.fill(prev);

	return 0;
}

// IMPLEMENT YOUR FUNCTIONS HERE
Account	createAccount(string name)
{
	ofstream fout;
	ifstream fin;
	
	fout.open(name);

	if(!fout.good())
	{
	Account temp;
		temp.name = "Savings";
		temp.balance.dollars = 100;
		temp.balance.cents = 0;
		temp.rate = .01;

	}
	else
	{
		for(int x = 0; x < 1; x++)
		{
		Account temp;
		double temp1;
		int dollar;
		int cents;
		dollar = temp1;
		cents = (temp1 - dollar) * 100;
		fin.ignore(1000, '\n');
		getline(fin, temp.name);
		fin >> temp1;
		fin >> temp.rate;
		temp.balance.dollars = dollar;
		temp.balance.cents = cents ;
		return temp;
		}
		
	}
	fout.close();
	
}
Account createAccount(string name, double rate, Money balance)
{
	Account temp;
		temp.name = name;
		temp.balance = balance;
		temp.rate = rate;
		return temp;
}
Account deposit(Account account, Money deposit)
{
	
	
	
	if(isNegative(deposit))
	{
		cout << "balance was negative, so orignal account was returned."
			 << endl;
		return	account;
	}
	else
	{
		account.balance.dollars += deposit.dollars;
		account.balance.cents += deposit.cents;
		
		cout << "$" << deposit.dollars	<< "." << deposit.cents << " deposited into" << account.name	<< endl;
	}
}
Money withdraw(Account &account, Money withdraw)
{
	if( isNegative(withdraw) || ((withdraw.dollars + withdraw.cents) > 50.00) )
	{
		Money temp;
		temp.dollars = 0;
		temp.cents = 0;
		cout << "balance was negative, so orignal account was returned."
			 << "$" << temp.dollars << "." << temp.cents << endl;
		return	account.balance;
	}
	else
	{
		int temp = makePennies(withdraw);
		int dollars = temp;
		double temp1 = temp / 100;
		account.balance.dollars -= withdraw.dollars;
		account.balance.cents -= withdraw.cents;
		
		cout << "$" << temp1 << " withdraw from" << account.name << endl;
	}
}
void accrue(Account &account)
{
	
	Money temp;
	temp.dollars = account.balance.dollars;
	temp.cents = account.balance.cents;
	double temp2 = temp.dollars + temp.cents;
	
	cout << "At" << account.rate	<< "%, " << account.name << "$" << temp2 << endl;
}
void print(Money account)
{
	double temp1;
		temp1 = account.dollars + account.cents;
		
	if (isNegative(account))
	{
		
		cout << "$(" <<  temp1 << ")" << endl;
	}
	else
	{
		cout << "$" <<  temp1 << endl;
	}
	
}
void print(Account account)
{
	Money temp;
		temp.dollars = account.balance.dollars;
		temp.cents = account.balance.cents;
	double temp1;
		temp1 = account.balance.dollars + account.balance.cents;
	if (isNegative(temp))
	{
		
		cout<< "$(" <<  temp1 << ")" << endl;
	}
	else
	{
		cout << "$" <<  temp1 << endl;
	}
}
// HELPER FUNCTION IMPLEMENTATIONS -- DO NOT ALTER
int makePennies(Money m)
{
	return (m.dollars * 100) + m.cents;
}

Money makeMoney(int p)
{
	return Money{p / 100, p % 100};
}

bool isNegative(Money m)
{
	if (m.dollars < 0 || m.cents < 0)
		return true;
	else
		return false;
}

bool operator<(const Money& lhs, const Money& rhs)
{
	int leftPennies = makePennies(lhs);
	int rightPennies = makePennies(rhs);

	return leftPennies < rightPennies;
}
// DO *NOT* ALTER THESE FUNCTION IMPLEMENTATIONS
bool testCreateAccountFile(bool n)
{
	std::string fn;
	if (n)
		fn = "inputs";
	else
		fn = "garbage";
	
	Account acc = createAccount(fn);

	if (acc.name == "Saving for college" && acc.rate == 0.01 && acc.balance.dollars == 4321 && acc.balance.cents == 98)
		return true;
	else if (fn == "garbage" && acc.name == "Savings" && acc.rate == 0.01 && acc.balance.dollars == 100 && acc.balance.cents == 0)
		return true;
	else
		return false;
}

bool testCreateAccountParams()
{
	Account t = createAccount("Roth IRA", 0.055, {1234, 56});
	if (t.name == "Roth IRA" && t.rate == 0.055 && t.balance.dollars == 1234 && t.balance.cents == 56)
		return true;
	else
		return false;
}

bool testDeposit(Money dep)
{
	Account t = createAccount("Checking", 0.005, {50, 0});
	int dollars = dep.dollars;
	int cents = dep.cents;

	t = deposit(t, dep);

	if (t.balance.dollars == 50 + dollars && t.balance.cents == 0 + cents) {
		return true;
	} else if (isNegative(dep)) {
		if (t.balance.dollars == 50 && t.balance.cents == 0) {
			return true;
		}
	} else {
		return false;
	}

	return false;
}

// USE AS DEBUGGER EXAMPLE
bool testWithdraw(Money w)
{
	Account t = createAccount("Index Fund", 0.06, {50, 0});
	Money overdrawLimit{t.balance.dollars + 50, t.balance.cents};

	Money amount = withdraw(t, w);

	if (isNegative(w)) {
		if (amount.dollars == 0 && amount.cents == 0) {
			return true;
		}
		return false;
	} else if (w < t.balance) {
		if (w.dollars == amount.dollars && w.cents == amount.cents) {
			return true;
		}
		return false;
	} else if (w < overdrawLimit) {
		if (w.dollars == amount.dollars && w.cents == amount.cents) {
			return true;
		}
		return false;
	} else {
		if (amount.dollars == overdrawLimit.dollars && amount.cents == overdrawLimit.cents) {
			return true;
		}
		return false;
	}

	return false;
}

bool testAccrue()
{
	Account t = {{48, 31}, 0.02, "Savings"};

	accrue(t);

	if (t.balance.dollars == 49 && t.balance.cents == 28)
		return true;
	else
		return false;
}

void testPrint(bool type, bool sign)
{
	Account a;
	Money m;

	if (type) {
		if (sign) {
			a = createAccount("CD", 0.03, {567, 32});
		} else {
			a = createAccount("CD", 0.03, {-567, -32});
		}
		print(a);
		return;
	} else {
		if (sign) {
			m = {567, 32};
		} else {
			m = {-567, -32};
		}
		print(m);
		return;
	}
}
