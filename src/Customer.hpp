#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Date.hpp"

class Supermarket;
class Transaction;

using namespace std;

class Customer
{
public:
  Customer();
  Customer(unsigned int id, string name, string joinDate, double amount);
  void setId(unsigned int id);
  void setName(string name);
  void setJoinDate(Date joinDate);
  void setAmount(double amount);
  unsigned int getId() const;
  string getName() const;
  Date getJoinDate() const;
  double getAmount() const;

private:
  unsigned int id;
  string name;
  Date joinDate;
  double amount;
};


int validatInputCustomer();

void showCustomerInfoId(const map<unsigned int, unsigned int> &, const vector<Customer>&);

void showCustomersInfoName(const map<string, unsigned int> &, const vector<Customer>&);

void showAllCustomersInfo(const vector<Customer>&);

 /* Returns the current maximum customer id */
unsigned int verifyMaximum(const vector<Customer>&,const vector<Transaction>&);

void addCustomer(Supermarket &);

void editCustomer(Supermarket &);

void removeCustomer(Supermarket &);

 /*  Saves the customer vector to its file */
void saveCustomers(const vector<Customer>&, const string&);

void bottom10(vector<Customer>);

void showCustomers(const vector<Customer>&);

bool compareByAmount(const Customer &amountCostumer1, const Customer &amountCostumer2);
