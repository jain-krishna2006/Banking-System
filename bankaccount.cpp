#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
public:
    string name;
    int accountNumber;
    float balance;

    void createAccount() {
        cin.ignore(); // To clear newline character from previous input
        cout << "Enter your name: ";
        getline(cin, name);

        cout << "Enter account number: ";
        cin >> accountNumber;

        balance = 0.0;
        cout << "Account created successfully!\n";

        ofstream file("accounts.txt", ios::app);
        file << name << " " << accountNumber << " " << balance << endl;
        file.close();
    }

    bool loadAccount(int accNo) {
        ifstream file("accounts.txt");
        string n;
        int a;
        float b;
        bool found = false;

        while (file >> n >> a >> b) {
            if (a == accNo) {
                name = n;
                accountNumber = a;
                balance = b;
                found = true;
                break;
            }
        }
        file.close();
        return found;
    }

    void saveAccount() {
        ifstream inFile("accounts.txt");
        ofstream outFile("temp.txt");

        string n;
        int a;
        float b;

        while (inFile >> n >> a >> b) {
            if (a == accountNumber) {
                outFile << name << " " << accountNumber << " " << balance << endl;
            } else {
                outFile << n << " " << a << " " << b << endl;
            }
        }

        inFile.close();
        outFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }

    void deposit() {
        float amount;
        cout << "Enter amount to deposit: Rs.";
        cin >> amount;
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        saveAccount();
        cout << "Rs." << amount << " deposited successfully.\n";
    }

    void withdraw() {
        float amount;
        cout << "Enter amount to withdraw: Rs.";
        cin >> amount;
        if (amount <= 0 || amount > balance) {
            cout << "Invalid or insufficient balance!\n";
            return;
        }
        balance -= amount;
        saveAccount();
        cout << "Rs." << amount << " withdrawn successfully.\n";
    }

    void displayInfo() {
        cout << "\n--- Account Information ---\n";
        cout << "Name: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: Rs." << balance << endl;
    }
};

void menuAfterLogin(BankAccount& account) {
    int choice;
    do {
        cout << "\n--- Banking Menu ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Display Info\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            account.deposit();
            break;
        case 2:
            account.withdraw();
            break;
        case 3:
            account.displayInfo();
            break;
        case 4:
            cout << "Logged out.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

int main() {
    int choice;
    BankAccount account;

    do {
        cout << "\n--- Welcome to the Bank ---\n";
        cout << "1. Register (New Account)\n";
        cout << "2. Login (Existing Account)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            account.createAccount();
            break;
        case 2: {
            int accNo;
            cout << "Enter your account number: ";
            cin >> accNo;
            if (account.loadAccount(accNo)) {
                cout << "Login successful!\n";
                menuAfterLogin(account);
            } else {
                cout << "Account not found!\n";
            }
            break;
        }
        case 3:
            cout << "Thank you for using our banking system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
