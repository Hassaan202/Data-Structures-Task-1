#include "BanksSystem.h"
#include <Windows.h>
#pragma warning(disable : 4996)

int main() {
	Bank HBL;
	system("color 0B");
	cout << "|-------------------------------------------------|\n";
	cout << "|-----------------Banking System------------------|\n";
	cout << "|-------------------------------------------------|\n";
	while (true) {
		cout << "\nSelect the operation:\n1-Add account\n2-Remove account\n3-Perform Transaction\n4-Merge accounts\n5-Print account details\n6-Exit\n";
		int a = 0;
		cin >> a;
		while (a < 1 && a>6) {
			cout << "Select a number between 1 and 5:";
			cin >> a;
		}
		switch (a) {
		case 1:
			HBL.addAccount();
			break;
		case 2:
			int num;
			cout << "Enter the account number to delete:\n";
			cin >> num;
			HBL.removeAccount(num);
			break;
		case 3:
			HBL.performTrans();
			break;
		case 4:
			int num1, num2;
			cout << "Enter the account number 1:\n";
			cin >> num1;
			cout << "Enter the account number 2:\n";
			cin >> num2;
			HBL.merge(num1, num2);
			break;
		case 5:
			HBL.printAccountDetails();
			break;
		case 6:
			cout << "Exiting...........\n";
			return 0;
		}		
	}
}