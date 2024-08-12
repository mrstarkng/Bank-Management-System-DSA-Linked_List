#include "function.hpp"



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
    isLocked = false; // Account is initially unlocked
    failedAttempts = 0; // No failed attempts initially
    next = NULL;
}

node::node(int acno, double bal, double LRcB, double LReB, double FD, double GI, unsigned int tm, short drtin, int year, string nam, string num, string eml, string pass) {
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
        printw("ERROR: Account number already exists. Please enter a UNIQUE account number.\n");
    } else if (age < 18) {
        printw("ERROR: The minimum age to open a bank account is 18 years.\n");
    } else {
        if (head == NULL) {
            head = n;
            printw("Account Created Successfully!\n");
        } else {
            node *ptr = head;
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = n;
            printw("Account Created Successfully!\n");
        }
    }
    refresh();
}

void bank::Add_sub_balance(int bal_update, int acno, string pass) {
    node *temp = accExist(acno);

    if (temp == NULL || temp->password != pass) {
        printw("ERROR: Wrong account number or password.\n");
    } else {
        temp->balance = temp->balance + bal_update;

        printw("Total balance = %.2f\n", temp->balance);

        if (bal_update >= 0) {
            printw("%d amount added to account %d of %s\n", bal_update, temp->account_Number, temp->name.c_str());
        } else {
            printw("%d amount withdrawn from account %d of %s\n", -bal_update, temp->account_Number, temp->name.c_str());
        }
        printw("Total balance left = %.2f\n", temp->balance);
    }
    refresh();
}

void bank::showAcc(int acno, const std::string& inputPass) {
    node *temp = accExist(acno);

    if (temp == NULL) {
        printw("ERROR: No account found.\n");
    } else if (temp->isLocked) {
        printw("ERROR: This account is locked due to too many incorrect password attempts.\n");
    } else if (temp->password != inputPass) {
        temp->failedAttempts++;
        if (temp->failedAttempts >= 3) {
            temp->isLocked = true;
            printw("ERROR: Account has been locked due to 3 incorrect password attempts.\n");
        } else {
            printw("ERROR: Incorrect password. You have %d attempt(s) left before the account is locked.\n", 3 - temp->failedAttempts);
        }
    } else {
        temp->failedAttempts = 0; // Reset failed attempts on successful login
        printw("Account Number: %d\n", temp->account_Number);
        printw("Balance: %.2f\n", temp->balance);
        printw("Account Holder Name: %s\n", temp->name.c_str());
        printw("Phone Number: %s\n", temp->phone_no.c_str());
        printw("Email: %s\n", temp->email.c_str());
        printw("Fixed Deposit Balance: %.2f\n", temp->fixedDeposite);
        printw("Loan Received: %.2f\n", temp->loanRecieveBOX);
        printw("Loan Returned: %.2f\n", temp->loanReturnBOX);
    }
    refresh();
}

void bank::deleteAccount(int acno, string pass) {
    if (head == NULL) {
        printw("ERROR: No accounts available to delete.\n");
        return;
    }

    if (head->account_Number == acno && head->password == pass) {
        head = head->next;
        printw("Account deleted successfully.\n");
        return;
    }

    node *prev = head;
    node *current = head->next;

    while (current != NULL) {
        if (current->account_Number == acno && current->password == pass) {
            prev->next = current->next;
            delete current;
            printw("Account deleted successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printw("ERROR: Account not found or password incorrect.\n");
    refresh();
}

void bank::totalUser() {
    int count = 0;
    node *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    printw("Total active users: %d\n", count);
    refresh();
}

void bank::totalAmount() {
    double totalBalance = 0;
    node *temp = head;

    while (temp != NULL) {
        totalBalance += temp->balance;
        temp = temp->next;
    }

    printw("Total amount of money in the bank: %.2f\n", totalBalance);
    refresh();
}

void bank::updateAccount(int acno, const std::string& inputPass) {
    node *temp = accExist(acno);

    if (temp == NULL) {
        printw("ERROR: No account found.\n");
    } else if (temp->isLocked) {
        printw("ERROR: This account is locked due to too many incorrect password attempts.\n");
    } else if (temp->password != inputPass) {
        temp->failedAttempts++;
        if (temp->failedAttempts >= 3) {
            temp->isLocked = true;
            printw("ERROR: Account has been locked due to 3 incorrect password attempts.\n");
        } else {
            printw("ERROR: Incorrect password. You have %d attempt(s) left before the account is locked.\n", 3 - temp->failedAttempts);
        }
    } else {
        temp->failedAttempts = 0; // Reset failed attempts on successful login

        int choice;
        printw("Select the information you want to update:\n");
        printw("1. Name\n");
        printw("2. Phone Number\n");
        printw("3. Email\n");
        printw("4. Password\n");
        printw("Enter your choice: ");
        scanw("%d", &choice);

        switch (choice) {
            case 1:
                char newName[50];
                printw("Enter new name: ");
                echo();
                scanw("%s", newName);
                temp->name = newName;
                printw("Name updated successfully.\n");
                noecho();
                break;
            case 2:
                char newPhone[20];
                printw("Enter new phone number: ");
                echo();
                scanw("%s", newPhone);
                temp->phone_no = newPhone;
                printw("Phone number updated successfully.\n");
                noecho();
                break;
            case 3:
                char newEmail[50];
                printw("Enter new email: ");
                echo();
                scanw("%s", newEmail);
                temp->email = newEmail;
                printw("Email updated successfully.\n");
                noecho();
                break;
            case 4:
                char newPassword[20];
                printw("Enter new password: ");
                echo();
                scanw("%s", newPassword);
                temp->password = newPassword;
                printw("Password updated successfully.\n");
                noecho();
                break;
            default:
                printw("Invalid choice. No changes made.\n");
                break;
        }
    }
    refresh();
}


