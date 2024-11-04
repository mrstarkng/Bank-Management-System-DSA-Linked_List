//
//  function.hpp
//  BankManagementSystem
//
//  Created by Tony Nguyễn on 10/08/2024.
//

#ifndef function_hpp
#define function_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <ncurses.h>


using namespace std;


class node {
public:
    int account_Number;
    int age;
    double balance;
    double loanRecieveBOX;
    double loanReturnBOX;
    double fixedDeposite;
    double goldInterest;
    unsigned int time;
    short duration;
    std::string name;
    std::string phone_no;
    std::string email;
    std::string password;
    bool isLocked;
    int failedAttempts;
    node* next;

    node();
    node(int acno, double bal, double LRcB, double LReB, double FD, double GI, unsigned int tm, short drtin, int year, std::string nam, std::string num, std::string eml, std::string pass);
};

class bank {
private:
    node* head;

public:
    bank();
    bank(node* n);
    node* accExist(int acno1);
    void createAccount(node* n);
    void Add_sub_balance(int bal_update, int acno, std::string pass);
    void showAcc(int acno, const std::string& inputPass);
    void deleteAccount(int acno, std::string pass);
    void totalUser();
    void totalAmount();
    void updateAccount(int acno, const std::string& inputPass);
};

#endif // BANK_H
