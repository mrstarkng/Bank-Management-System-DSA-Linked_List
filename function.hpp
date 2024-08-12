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


class node
{
public:
    int account_Number;
    int age;
    double balance;
    double loanRecieveBOX;
    double loanReturnBOX;
    double fixedDeposite;
    double goldInterest;
    unsigned int time;
    short int duration;
    string name;
    string phone_no;
    string email;
    string password;
    bool isLocked; // New variable to indicate if the account is locked
    int failedAttempts; // Track the number of failed login attempts
    node *next;

    node();
    node(int acno, double bal, double LRcB, double LReB, double FD, double GI, unsigned int tm, short drtin, int year, string nam, string num, string eml, string pass);
};


class bank {
public:
    node *head;

    bank();
    bank(node *n);

    node *accExist(int acno1);
    void createAccount(node *n);
    void Add_sub_balance(int bal_update, int acno, string pass);
    void showAcc(int acno, const std::string& inputPass);
    void deleteAccount(int acno, string pass);
    void totalUser();
    void totalAmount();
    void updateAccount(int acno, const std::string& inputPass);

};

#endif // BANK_H
