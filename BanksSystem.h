#pragma once
#include "DList.h"
#include <string>
#include <ctime>

class Bank;
class Account;
class Transaction;


//BANK CLASS DECLARATION
class Bank {
	DList<Account> accounts;
	int accSerial;
	int transSerial;

public:
	Bank();
	void addAccount();
	void removeAccount(int);
	Account merge(int, int);
	void performTrans();
	void printAccountDetails();
};


//ACCOUNT CLASS DECLARATION
class Account {
	friend class Bank;
	int accountNum;
	string accountTitle;
	string accountBalance;
	DList<Transaction> transHistory;

public:
	Account();
	Account(int, string, string); //overloaded constructor
	/*Account(Account&);*/
	int getAccNum() { return accountNum; }
	void addMoney(string, int);
	void withdrawMoney(string, int);
	void displayAccountDetails();
	friend ostream& operator<<(ostream&, Account&);
	//Account& operator=(const Account&);
	//copy constructor and assignment operator check
	/*~Account();*/
};


//TRANSACTION CLASS DECLARATION
class Transaction {
	friend class Account;
	int tranID;
	string transTime;
	string transDate;
	char type;
	string transferredAmount;
	int senderAccountNum;

public:
	Transaction();
	Transaction(int, string, string, char, string, int); //overloaded constructor
	friend ostream& operator<<(ostream&, Transaction&);  //overload stream insertion operator to make it compatible with list class methods
	bool operator==(Transaction&);
	bool operator!=(Transaction&);
	bool operator>(Transaction&);
	bool operator<(Transaction&);
	bool operator>=(Transaction&);
	bool operator<=(Transaction&);
	int getTransactionID() { return tranID; }
};



