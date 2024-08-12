#include "function.hpp"
#include <iostream>
#include <ctime>
#include <cmath>

node::node() {
    account_Number = 0;
    age = 0;
    balance = 0.0;
    loanRecieveBOX = 0.0;
    loanReturnBOX = 0.0;
    fixedDeposite = 0.0;
    goldInterest = 0.0;
    time = 0;
    duration = 0;
    name = "NULL";
    phone_no = "NULL";
    email = "NULL";
    password = "NULL";
    isLocked = false;
    failedAttempts = 0;
    next = NULL;
}

node::node(int acno, double bal, double LRcB, double LReB, double FD, double GI, unsigned int tm, short drtin, int year, std::string nam, std::string num, std::string eml, std::string pass) {
    account_Number = acno;
    balance = bal;
    loanRecieveBOX = LRcB;
    loanReturnBOX = LReB;
    fixedDeposite = FD;
    goldInterest = GI;
    time = tm;
    duration = drtin;
    age = year;
    name = nam;
    phone_no = num;
    email = eml;
    password = pass;
    isLocked = false;
    failedAttempts = 0;
    next = NULL;
}

bank::bank() {
    head = NULL;
}

bank::bank(node *n) {
    head = n;
}

node *bank::accExist(int acno1) {
    node *temp = NULL;
    node *ptr = head;
    while (ptr != NULL) {
        if (ptr->account_Number == acno1) {
            temp = ptr;
        }
        ptr = ptr->next;
    }
    return temp;
}

void bank::createAccount(node *n) {
    time_t t = time(NULL);
    tm *const pTInfo = localtime(&t);
    int b = 1900 + pTInfo->tm_year;

    int age = abs(n->age - b);

    if (accExist(n->account_Number) != NULL) {
        std::cout << "ERROR: Account number already exists. Please enter a UNIQUE account number.\n";
    } else if (age < 18) {
        std::cout << "ERROR: The minimum age to open a bank account is 18 years.\n";
    } else {
        if (head == NULL) {
            head = n;
            std::cout << "Account Created Successfully!\n";
        } else {
            node *ptr = head;
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = n;
            std::cout << "Account Created Successfully!\n";
        }
    }
}

void bank::Add_sub_balance(int bal_update, int acno, std::string pass) {
    node *temp = accExist(acno);

    if (temp == NULL || temp->password != pass) {
        std::cout << "ERROR: Wrong account number or password.\n";
    } else {
        temp->balance = temp->balance + bal_update;

        std::cout << "Total balance = " << temp->balance << "\n";

        if (bal_update >= 0) {
            std::cout << bal_update << " amount added to account " << temp->account_Number << " of " << temp->name << "\n";
        } else {
            std::cout << -bal_update << " amount withdrawn from account " << temp->account_Number << " of " << temp->name << "\n";
        }
        std::cout << "Total balance left = " << temp->balance << "\n";
    }
}

void bank::showAcc(int acno, const std::string& inputPass) {
    node *temp = accExist(acno);

    if (temp == NULL) {
        std::cout << "ERROR: No account found.\n";
    } else if (temp->isLocked) {
        std::cout << "ERROR: This account is locked due to too many incorrect password attempts.\n";
    } else if (temp->password != inputPass) {
        temp->failedAttempts++;
        if (temp->failedAttempts >= 3) {
            temp->isLocked = true;
            std::cout << "ERROR: Account has been locked due to 3 incorrect password attempts.\n";
        } else {
            std::cout << "ERROR: Incorrect password. You have " << 3 - temp->failedAttempts << " attempt(s) left before the account is locked.\n";
        }
    } else {
        temp->failedAttempts = 0; // Reset failed attempts on successful login
        std::cout << "Account Number: " << temp->account_Number << "\n";
        std::cout << "Balance: " << temp->balance << "\n";
        std::cout << "Account Holder Name: " << temp->name << "\n";
        std::cout << "Phone Number: " << temp->phone_no << "\n";
        std::cout << "Email: " << temp->email << "\n";
        std::cout << "Fixed Deposit Balance: " << temp->fixedDeposite << "\n";
        std::cout << "Loan Received: " << temp->loanRecieveBOX << "\n";
        std::cout << "Loan Returned: " << temp->loanReturnBOX << "\n";
    }
}

void bank::deleteAccount(int acno, std::string pass) {
    if (head == NULL) {
        std::cout << "ERROR: No accounts available to delete.\n";
        return;
    }

    if (head->account_Number == acno && head->password == pass) {
        node* temp = head;
        head = head->next;
        delete temp;
        std::cout << "Account deleted successfully.\n";
        return;
    }

    node *prev = head;
    node *current = head->next;

    while (current != NULL) {
        if (current->account_Number == acno && current->password == pass) {
            prev->next = current->next;
            delete current;
            std::cout << "Account deleted successfully.\n";
            return;
        }
        prev = current;
        current = current->next;
    }

    std::cout << "ERROR: Account not found or password incorrect.\n";
}

void bank::totalUser() {
    int count = 0;
    node *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    std::cout << "Total active users: " << count << "\n";
}

void bank::totalAmount() {
    double totalBalance = 0;
    node *temp = head;

    while (temp != NULL) {
        totalBalance += temp->balance;
        temp = temp->next;
    }

    std::cout << "Total amount of money in the bank: " << totalBalance << "\n";
}

void bank::updateAccount(int acno, const std::string& inputPass) {
    node *temp = accExist(acno);

    if (temp == NULL) {
        std::cout << "ERROR: No account found.\n";
    } else if (temp->isLocked) {
        std::cout << "ERROR: This account is locked due to too many incorrect password attempts.\n";
    } else if (temp->password != inputPass) {
        temp->failedAttempts++;
        if (temp->failedAttempts >= 3) {
            temp->isLocked = true;
            std::cout << "ERROR: Account has been locked due to 3 incorrect password attempts.\n";
        } else {
            std::cout << "ERROR: Incorrect password. You have " << 3 - temp->failedAttempts << " attempt(s) left before the account is locked.\n";
        }
    } else {
        temp->failedAttempts = 0; // Reset failed attempts on successful login

        int choice;
        std::cout << "Select the information you want to update:\n";
        std::cout << "1. Name\n";
        std::cout << "2. Phone Number\n";
        std::cout << "3. Email\n";
        std::cout << "4. Password\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer

        switch (choice) {
            case 1: {
                std::string newName;
                std::cout << "Enter new name: ";
                std::getline(std::cin, newName);
                temp->name = newName;
                std::cout << "Name updated successfully.\n";
                break;
            }
            case 2: {
                std::string newPhone;
                std::cout << "Enter new phone number: ";
                std::getline(std::cin, newPhone);
                temp->phone_no = newPhone;
                std::cout << "Phone number updated successfully.\n";
                break;
            }
            case 3: {
                std::string newEmail;
                std::cout << "Enter new email: ";
                std::getline(std::cin, newEmail);
                temp->email = newEmail;
                std::cout << "Email updated successfully.\n";
                break;
            }
            case 4: {
                std::string newPassword;
                std::cout << "Enter new password: ";
                std::getline(std::cin, newPassword);
                temp->password = newPassword;
                std::cout << "Password updated successfully.\n";
                break;
            }
            default:
                std::cout << "Invalid choice. No changes made.\n";
                break;
        }
    }
}
