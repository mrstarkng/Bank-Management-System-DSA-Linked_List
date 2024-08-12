#include "function.hpp"
#include <iostream>
#include <limits>

void showMenu() {
    std::cout << "------------------------------------------------\n";
    std::cout << "|              GLOBAL BANK SYSTEM              |\n";
    std::cout << "------------------------------------------------\n";
    std::cout << "| 1. Create a new account                      |\n";
    std::cout << "| 2. Show account details                      |\n";
    std::cout << "| 3. Deposit / Withdraw                        |\n";
    std::cout << "| 4. Count number of customers                 |\n";
    std::cout << "| 5. Total amount in the bank                  |\n";
    std::cout << "| 6. Delete an account                         |\n";
    std::cout << "| 7. Update account information                |\n";
    std::cout << "| 8. Exit                                      |\n";
    std::cout << "------------------------------------------------\n";
    std::cout << "Enter your choice: ";
}

int main() {
    bank b;
    int option;
    int acno, bal_update, year;
    std::string pass, name, email, phone;

    do {
        showMenu();
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer

        node *n1 = new node();

        switch (option) {
            case 1: {
                srand(time(NULL));
                acno = rand() % 9000 + 1000;
                std::cout << "Account Number: " << acno << "\n";
                std::cout << "Enter a password: ";
                std::getline(std::cin, pass);
                std::cout << "Enter Account holder's name: ";
                std::getline(std::cin, name);
                std::cout << "Enter email: ";
                std::getline(std::cin, email);
                std::cout << "Enter phone number: ";
                std::getline(std::cin, phone);
                std::cout << "Enter your year of birth: ";
                std::cin >> year;

                n1->account_Number = acno;
                n1->name = name;
                n1->password = pass;
                n1->phone_no = phone;
                n1->email = email;
                n1->balance = 500;
                n1->age = year;

                b.createAccount(n1);
                break;
            }
            case 2: {
                std::cout << "Enter your account number: ";
                std::cin >> acno;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
                std::cout << "Enter your password: ";
                std::getline(std::cin, pass);
                b.showAcc(acno, pass);
                break;
            }
            case 3: {
                std::cout << "Enter your account number: ";
                std::cin >> acno;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
                std::cout << "Enter your password: ";
                std::getline(std::cin, pass);
                std::cout << "Enter the amount to deposit/withdraw (use negative for withdrawal): ";
                std::cin >> bal_update;
                b.Add_sub_balance(bal_update, acno, pass);
                break;
            }
            case 4:
                b.totalUser();
                break;
            case 5:
                b.totalAmount();
                break;
            case 6: {
                std::cout << "Enter your account number: ";
                std::cin >> acno;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
                std::cout << "Enter your password: ";
                std::getline(std::cin, pass);
                b.deleteAccount(acno, pass);
                break;
            }
            case 7: {
                std::cout << "Enter your account number: ";
                std::cin >> acno;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
                std::cout << "Enter your password: ";
                std::getline(std::cin, pass);
                b.updateAccount(acno, pass);
                break;
            }
            case 8:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Pause until user presses Enter
    } while (option != 8);

    return 0;
}
