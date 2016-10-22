#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Customer.hpp"
#include "Product.hpp"

using namespace std;

class Supermarket;

class Transaction
{
public:
  Transaction();
  Transaction(unsigned int id, string date);
  Transaction(unsigned int id, string date, vector<string> products);
  void setId(unsigned int id);
  void setDate(Date date);
  void setProducts(vector<string> products);
  unsigned int getId() const;
  Date getDate() const;
  vector<string> getProducts() const;
  void addProduct(string product);
  void showProductsTransaction() const;
  bool compareByDate(const Transaction &, const Transaction &);
    
private:
  unsigned int id;
  Date date;
  vector<string> products;
};

void showCustomerTransactionsId(const vector<Transaction>&, const multimap<unsigned int, unsigned int> &, const unsigned int);

void showCustomerTransactionsName(Supermarket&);

void showAllTransactions(const vector<Transaction>&);

void showDayTransactions(const vector<Transaction>&);

void showTransactBetwDays(const vector<Transaction>&);

void addTransaction(Supermarket &);

void saveTransaction(const vector<Transaction> &, const string &);
