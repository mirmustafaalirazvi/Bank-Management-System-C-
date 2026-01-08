#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Bank {
    int accNo;
    char name[50];
    double balance;
};

void createAccount() {
    Bank b;
    ofstream outFile("bank.dat", ios::binary | ios::app);

    cout << "\nEnter Account Number: ";
    cin >> b.accNo;
    cin.ignore();

    cout << "Enter Account Holder Name: ";
    cin.getline(b.name, 50);

    cout << "Enter Initial Balance: ";
    cin >> b.balance;

    outFile.write((char*)&b, sizeof(b));
    outFile.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts() {
    Bank b;
    ifstream inFile("bank.dat", ios::binary);

    cout << "\n--- Account Details ---\n";
    while (inFile.read((char*)&b, sizeof(b))) {
        cout << "\nAccount Number: " << b.accNo;
        cout << "\nName: " << b.name;
        cout << "\nBalance: " << b.balance << endl;
    }
    inFile.close();
}

void depositAmount() {
    Bank b;
    int acc;
    double amount;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> acc;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.accNo == acc) {
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            b.balance += amount;

            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));

            cout << "\nAmount Deposited Successfully!\n";
            file.close();
            return;
        }
    }
    cout << "\nAccount Not Found!\n";
    file.close();
}

void withdrawAmount() {
    Bank b;
    int acc;
    double amount;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> acc;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.accNo == acc) {
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            if (b.balance >= amount) {
                b.balance -= amount;
                file.seekp(-sizeof(b), ios::cur);
                file.write((char*)&b, sizeof(b));
                cout << "\nAmount Withdrawn Successfully!\n";
            } else {
                cout << "\nInsufficient Balance!\n";
            }
            file.close();
            return;
        }
    }
    cout << "\nAccount Not Found!\n";
    file.close();
}

void balanceEnquiry() {
    Bank b;
    int acc;
    ifstream inFile("bank.dat", ios::binary);

    cout << "\nEnter Account Number: ";
    cin >> acc;

    while (inFile.read((char*)&b, sizeof(b))) {
        if (b.accNo == acc) {
            cout << "\nAccount Number: " << b.accNo;
            cout << "\nName: " << b.name;
            cout << "\nBalance: " << b.balance << endl;
            inFile.close();
            return;
        }
    }
    cout << "\nAccount Not Found!\n";
    inFile.close();
}

int main() {
    int choice;

    do {
        cout << "\n==============================";
        cout << "\n BANK MANAGEMENT SYSTEM (C++) ";
        cout << "\n==============================";
        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Deposit Amount";
        cout << "\n4. Withdraw Amount";
        cout << "\n5. Balance Enquiry";
        cout << "\n6. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: depositAmount(); break;
            case 4: withdrawAmount(); break;
            case 5: balanceEnquiry(); break;
            case 6: cout << "\nThank You!\n"; break;
            default: cout << "\nInvalid Choice!\n";
        }
    } while (choice != 6);

    return 0;
}