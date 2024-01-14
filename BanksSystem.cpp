#include "BanksSystem.h"
#pragma warning(disable : 4996)  //disable safety warning

//TRANSACTION CLASS DEFINITION
Transaction::Transaction()
{
	tranID = 0;
    transTime = "";
	transDate = "";
	type = '\0'; //null char
	transferredAmount = "";
	senderAccountNum = -1;
}

Transaction::Transaction(int id, string time, string date, char ty, string ta, int sNum)
{
	tranID = id;
	transTime = time;
	transDate = date;
	type = ty;
	transferredAmount = ta;
	senderAccountNum = sNum;
}

bool Transaction::operator==(Transaction& t)
{
	return (tranID == t.tranID);
}

bool Transaction::operator!=(Transaction& t)
{
	return !(tranID == t.tranID);
}

bool Transaction::operator>(Transaction& t)
{
	if (tranID > t.tranID) {
		return true;
	}
	return false;
}

bool Transaction::operator<(Transaction& t)
{

	if (tranID < t.tranID) {
		return true;
	}
	return false;
}

bool Transaction::operator>=(Transaction& t)
{
	if (tranID >= t.tranID) {
		return true;
	}
	return false;
}

bool Transaction::operator<=(Transaction& t)
{
	if (tranID <= t.tranID) {
		return true;
	}
	return false;
}

ostream& operator<<(ostream& out, Transaction& t)
{
	out << "ID: " << t.tranID;
	out << "\nTime: "<< t.transTime;
	out << "\nDate: "<< t.transDate;
	out << "\nType: "<< t.type;
	out << "\nAmount: "<< t.transferredAmount;
	out << "\nSender's account number: "<< t.senderAccountNum << endl;
	return out;
}

template<> //specialized function template for the sort function
void DList<Transaction>::sort() {
	DNode* tmp = head, * innerTemp, * innerTempNext, * finalVal = nullptr;
	bool noMoreSwaps = false;

	while (tmp != tail && !noMoreSwaps) {
		noMoreSwaps = true;
		innerTemp = head;
		while (innerTemp->next != nullptr ) {
			//works on tha basis of transaction ids
			if (((innerTemp->data).getTransactionID()) > ((innerTemp->next->data)).getTransactionID()) { //swap
				if (tmp == innerTemp) {
					tmp = tmp->next;
				}
				else if (tmp == innerTemp->next) {
					tmp = innerTemp;
				}
				innerTempNext = innerTemp->next; //as we are passing by ref to the nodes so need to ensure we are passing the address of the real variable rather than of the next pointer
				swapDNodes(innerTemp, innerTempNext); 
				noMoreSwaps = false;
			}
			else { //noswap
				innerTemp = innerTemp->next;
			}
		}
		if (!finalVal)
			finalVal = tail;
		else
			finalVal = finalVal->prev;
		tmp = tmp->next;
	}

}




//ACCOUNT CLASS DEFINITION
Account::Account()
{
	accountNum = 0;
	accountTitle = "";
	accountBalance = "";
}

Account::Account(int an, string at, string ab)
{
	accountNum = an;
	accountTitle = at;
	accountBalance = ab;
}

void Account::addMoney(string amount, int tranSerial)
{
	//second parameter takes the serial of transcation from bank class
	if (stoi(amount) > 0) {
		accountBalance = to_string(stoi(accountBalance) + stoi(amount));
		const time_t t = time(0);
		tm* tp = localtime(&t);
		string transTIme = to_string(tp->tm_hour) + ":" + to_string(tp->tm_min) + ":" + to_string(tp->tm_sec);
		string transDate = to_string(tp->tm_mday) + "/" + to_string(tp->tm_mon + 1) + "/20" + to_string(tp->tm_year - 100);
		Transaction* T = new Transaction(tranSerial, transTIme, transDate, 'C', amount, accountNum);
		this->transHistory.insertAtEnd(*T);
	}
	else {
		cout << "Cannot add invalid amount to the account!\n";
	}
}

void Account::withdrawMoney(string amount, int tranSerial)
{
	if (accountBalance >= amount) {
		accountBalance = to_string(stoi(accountBalance) - stoi(amount));
		const time_t t = time(0);
		tm* tp = localtime(&t);
		string transTIme = to_string(tp->tm_hour) + ":" + to_string(tp->tm_min) + ":" + to_string(tp->tm_sec);
		string transDate = to_string(tp->tm_mday) + "/" + to_string(tp->tm_mon + 1) + "/20" + to_string(tp->tm_year - 100);
		Transaction* T = new Transaction(tranSerial, transTIme, transDate, 'D', amount, accountNum);
		transHistory.insertAtEnd(*T);
	}
	else {
		cout << "Insufficient amount available!\n";
	}
}

void Account::displayAccountDetails()
{
	cout << "Account Number: " << accountNum;
	cout << "\nAccount Title: " << accountTitle;
	cout << "\nAccount Balance: " << accountBalance;
	if (!(transHistory.isEmpty())) {
		cout << "\nTransactions:\n";
		transHistory.printList();
	}
	else {
		cout << "\nNo transaction available!\n";
	}
}


ostream& operator<<(ostream& out, Account& a)
{
	out << "Account Number: " << a.accountNum;
	out << "\nAccount Title: " << a.accountTitle;
	out << "\nAccount Balance: " << a.accountBalance;
	if (!(a.transHistory.isEmpty())) {
		out << "\nTransactions:\n";
		a.transHistory.printList();
	}
	else {
		out << "\nNo transaction available!\n";
	}
	out << endl;
	return out;
}




//BANK CLASS DEFINITION
Bank::Bank()
{
	accSerial = 0;
	transSerial = 0;
}

void Bank::addAccount()
{
	string title, openingBalance;
	cout << "Enter the account details:\n";
	cout << "Account Title: ";
	cin >> title;
	cout << "Opening Balance: ";
	cin >> openingBalance;
	//adding account in the linked list and updating the serial number
	Account a1(accSerial++, title, openingBalance);
	accounts.insertAtEnd(a1);
}

void Bank::removeAccount(int num)
{
	bool found = false;
	//using iterators to loop through the list
	DList<Account>::iterators it = accounts.begin();
	while (it != nullptr && !found) {
		if ((*it).getAccNum() == num) {
			found = true;
			break;
		}
		++it;
	}
	if ((*it).getAccNum() == num) {
		found = true;
	}
	if (found) {
		accounts.deleteNode(it);
	}
	else {
		cout << "Unable to find the acount!\n";
	}
}

Account Bank::merge(int a1, int a2)
{
	bool found1 = false;
	DList<Account>::iterators it1 = accounts.begin();
	while (it1 != accounts.end() && !found1) {
		if ((*it1).getAccNum()  == a1) {
			found1 = true;
			break;
		}
		++it1;
	}
	if ((*it1).getAccNum() == a1) {
		found1 = true;
	}
	bool found2 = false;
	DList<Account>::iterators it2 = accounts.begin();
	while (it2 != accounts.end() && !found2) {
		if ((*it2).getAccNum() == a2) {
			found2 = true;
			break;
		}
		++it2;
	}
	if ((*it2).getAccNum() == a2) {
		found2 = true;
	}

	if (found1 && found2) {
		string name;
		cout << "Enter the name of the new account: ";
		cin >> name;
		Account a3(accSerial++, name, (to_string(stoi((*it1).accountBalance) + stoi((*it2).accountBalance))));
		a3.transHistory = (*it1).transHistory.merge((*it2).transHistory);
		//sort the transcation history
		a3.transHistory.sort();  

		cout << "Account merging succesful!\n";
		accounts.deleteNode(it1);   //delete the merged accounts
		accounts.deleteNode(it2);
		accounts.insertAtEnd(a3); 	//adds the new account to the list
		return a3;
	}
	else {
		cout << "Unable to find the accounts!\n";
		Account dummy;
		return dummy;
	}
}

void Bank::performTrans()
{
	int  accNum = -1;
	string amount;
	char tranType = '\0';
	//data input
	while (accNum < 0) {
		cout << "Enter the account number to find: ";
		cin >> accNum;
	}
	cout << "Debit(D) or Cedit(C): ";
	cin >> (tranType);
	tranType = toupper(tranType);
	while (tranType != 'C' && tranType != 'D') {
		cout << "Enter a correct transaction to perform!";
		cin >> tranType;
		tranType = toupper(tranType);
	}
	cout << "Enter the amount:";
	cin >> amount;
	while (stoi(amount) <= 0) {
		cout << "Enter a valid amount: ";
		cin >> amount;
	}
	//iterating through the list to find the account with specific number
	bool found = false;
	DList<Account>::iterators it = accounts.begin();

	while (it != accounts.end() && !found) {
		if ((*it).getAccNum() == accNum) {
			found = true;
			break;
		}
		++it;
	}
	if ((*it).getAccNum() == accNum) {
		found = true;
	}
	if (found) {
		if (tranType == 'D') { //Debit 
			if (stoi(amount) <= stoi((*it).accountBalance)) { //transcation possible
				(*it).withdrawMoney(amount, transSerial++);
				cout << "The new amount is: " << (*it).accountBalance << ".\n";
			}
			else { 
				cout << "The amount entered is not available in your account!\n";
			}
		}
		else { //Credit
			(*it).addMoney(amount, transSerial++);
			cout << "The new amount is: " << (*it).accountBalance << ".\n";
		}
	}
	else {
		cout << "Unable to find the acount number in bank records. Please contact customer service for help!\n";
	}

}

void Bank::printAccountDetails()
{
	//uses the linked list method to print the accounts
	accounts.printList();
}
