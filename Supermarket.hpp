#pragma once

#include <vector>
#include <map>

#include "Customer.hpp"
#include "Transaction.hpp"
#include "Product.hpp"
#include "Date.hpp"



using namespace std;

class Supermarket
{
public:
  Supermarket(string name, string customersFile, string transactionsFile, string productsFile);
  vector<Customer> getCustomers();
  vector<Transaction> getTransactions() const;
  vector<Product> getProducts() const;
  string getCustomersFileName() const;
  string getTransactionsFileName() const;
  string getProductsFileName() const;
  map<unsigned int, unsigned int> getCustomersIdMap() const;
  map<string, unsigned int> getCustomersNameMap() const;
  multimap<unsigned int, unsigned int> getTransactionsMap() const;
  map<string, unsigned int> getProductsMap() const;
  bool readCustomersFile();
  bool readTransactionsFile();
  bool readProductsFile();
  Customer addCustomer(unsigned int, string);
  Product addProduct(string, double);
  bool editCustomer(unsigned int);
  bool removeCustomer(unsigned int);
  Transaction newTransaction(unsigned int, Date, vector<string>, double);
  void showBottom10();
  vector<Customer> getBottom10();
  
private:
  string name;
  string customersFile;
  string transactionsFile;
  string productsFile;
  vector<Customer> customers;
  vector<Transaction> transactions;
  vector<Product> products;
  map<unsigned int,unsigned int> customersIdMap;
  map<string,unsigned int> customersNameMap;
  multimap<unsigned int, unsigned int> transactionsMap;
  map<string, unsigned int> productsMap;
  bool readFile(const string &, vector<string> &);
  void editCustomerName(Customer &);
  void editCustomerDate(Customer &);
};
