#include "function.hpp"


void showMenu() {
    clear();
    printw("------------------------------------------------\n");
    printw("|              GLOBAL BANK SYSTEM              |\n");
    printw("------------------------------------------------\n");
    printw("| 1. Create a new account                      |\n");
    printw("| 2. Show account details                      |\n");
    printw("| 3. Deposit / Withdraw                        |\n");
    printw("| 4. Count number of customers                 |\n");
    printw("| 5. Total amount in the bank                  |\n");
    printw("| 6. Delete an account                         |\n");
    printw("| 7. Update account information                |\n");  // New option for updating information
    printw("| 8. Exit                                      |\n");
    printw("------------------------------------------------\n");
    printw("Enter your choice: ");
    refresh();
}

void getPassword(std::string &password) {
    char ch;
    password = "";
    noecho();  // Turn off echoing
    while((ch = getch()) != '\n') {
        password.push_back(ch);
        printw("*");  // Print an asterisk for each character typed
    }
    echo();  // Turn echoing back on
    printw("\n");
}



int main() {
    initscr(); // Khởi tạo cửa sổ ncurses
    cbreak();  // Nhận đầu vào từ người dùng ngay khi họ nhập mà không cần nhấn Enter
    noecho();  // Không hiện thị ký tự người dùng nhập vào
    keypad(stdscr, TRUE); // Cho phép nhận các phím đặc biệt như mũi tên

    bank b;
    int option;
    int acno, bal_update, year;
    string pass, name, email, numb;

    do {
        showMenu();  // Hiển thị menu giao diện cơ bản
        scanw("%d", &option);

        node *n1 = new node();

        switch (option) {
            case 1:
                srand(time(NULL));
                acno = rand() % 9000 + 1000;
                printw("Account Number: %d\n", acno);
                printw("Enter a password: ");
                echo();
                char pw[20];
                scanw("%s", pw);
                pass = pw;
                noecho();
                printw("Enter Account holder's name: ");
                char nameBuf[50];
                echo();
                scanw("%s", nameBuf);
                name = nameBuf;
                noecho();
                printw("Enter email: ");
                char emailBuf[50];
                scanw("%s", emailBuf);
                email = emailBuf;
                printw("Enter phone number: ");
                char phoneBuf[20];
                scanw("%s", phoneBuf);
                numb = phoneBuf;
                printw("Enter your year of birth: ");
                scanw("%d", &year);

                n1->account_Number = acno;
                n1->name = name;
                n1->password = pass;
                n1->phone_no = numb;
                n1->email = email;
                n1->balance = 500;
                n1->age = year;

                b.createAccount(n1);
                break;
                
            case 2:
                printw("Enter your account number: ");
                        scanw("%d", &acno);
                        printw("Enter your password: ");
                        getPassword(pass);  // Use getPassword to input password
                        b.showAcc(acno, pass);
                        break;
            case 3:
                printw("Enter your account number: ");
                scanw("%d", &acno);
                printw("Enter your password: ");
                echo();
                scanw("%s", pw);
                pass = pw;
                noecho();
                printw("Enter the amount to deposit/withdraw (use negative for withdrawal): ");
                scanw("%d", &bal_update);
                b.Add_sub_balance(bal_update, acno, pass);
                break;

            case 4:
                b.totalUser();
                break;

            case 5:
                b.totalAmount();
                break;

            case 6:
                printw("Enter your account number: ");
                scanw("%d", &acno);
                printw("Enter your password: ");
                echo();
                scanw("%s", pw);
                pass = pw;
                noecho();
                b.deleteAccount(acno, pass);
                break;

                
            case 7:
                         printw("Enter your account number: ");
                         scanw("%d", &acno);
                         printw("Enter your password: ");
                         echo();
                         scanw("%s", pw);
                         pass = pw;
                         noecho();
                         b.updateAccount(acno, pass);
                         break;
                
            case 8:
                printw("Exiting...\n");
                break;

            default:
                printw("Invalid choice. Please try again.\n");
        }

        printw("\nPress any key to continue...");
        refresh();
        getch(); // Đợi người dùng nhấn phím để tiếp tục
    } while (option != 7);

    endwin(); // Kết thúc ncurses
    return 0;
}
