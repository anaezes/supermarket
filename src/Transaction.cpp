#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>    // std::sort
#include <fstream>
#include <utility>

#include "Supermarket.hpp"
#include "Transaction.hpp"
#include "Customer.hpp"
#include "Menu.hpp"
#include "Date.hpp"
#include "Product.hpp"

using namespace std;


/******************************************************/
/*           TRANSACTIONS CLASS FUNCTIONS             */
/******************************************************/

Transaction::Transaction()
{
  setId(0);
  setDate(Date("1/1/1970"));
}


Transaction::Transaction(unsigned int id, string date)
{
  setId(id);
  setDate(date);
}


Transaction::Transaction(unsigned int id, string date, vector<string> products)
{
  setId(id);
  setDate(date);
  setProducts(products);
}


void Transaction::setId(unsigned int id)
{
  this->id = id;
}


void Transaction::setDate(Date date)
{
  this->date = date;
}


void Transaction::setProducts(vector<string> products)
{
  this->products = products;
}


void Transaction::addProduct(string product)
{
  products.push_back(product);
}


unsigned int Transaction::getId() const
{
  return id;
}


Date Transaction::getDate() const
{
  return date;
}


vector<string> Transaction::getProducts() const
{
  return products;
}


void Transaction::showProductsTransaction() const    
{
  for(size_t j = 0; j < products.size(); j++)
    {
      cout << products[j];

      if(j != products.size() - 1)
	cout << ", ";
    }
}


/******************************************************/
/*         TRANSACTIONS GENERAL FUNCTIONS             */
/******************************************************/


/* 
   Sort transactions by increasing date 
*/
bool compareByDate(const Transaction &date1, const Transaction &date2)
{
  return !(date1.getDate() >= date2.getDate());
}


/* 
   Shows transactions from a customer 
   whose id was given 
*/
void showCustomerTransactionsId(const vector<Transaction> &transactions, const multimap<unsigned int, unsigned int> &transactionsMap, const unsigned int idCustomer)
{
  cout << endl << "Show costumer transaction: " << endl << endl; 
  
  if(idCustomer == 0)
    cout << endl << "ID not valid!" << endl << endl;
  else
    {
      auto ret = transactionsMap.equal_range(idCustomer);

      if(ret.first == ret.second)
	cout << "Customer not found! ";
      else
	{
	  vector<Transaction> customerTransactions;
      
	  /* Find and print customer's transaction */
	  for(auto it = ret.first; it != ret.second; it++)
	    customerTransactions.push_back(transactions[it->second]);
	
	  std::sort(customerTransactions.begin(), customerTransactions.end(), compareByDate);

	  cout << endl << setw(10) << "Date" << "\t" << "Products" << endl;
	  cout << " -------------------------------------------------------------------------- " << endl;
	  for(size_t i = 0; i < customerTransactions.size(); i++)
	    {		 
	      cout <<  setw(11) << customerTransactions[i].getDate().asString() << "\t";
	      customerTransactions[i].showProductsTransaction();	    
	      cout << endl;
	    }
	}
      
      cout << endl << endl;
    }
}

/* 
   Shows transactions from a customer 
   whose name was given 
*/
void showCustomerTransactionsName(Supermarket &supermarket)
{
  const map<string, unsigned int> namesMap = supermarket.getCustomersNameMap();

  string name;
  cout << "Customer name: " ;
  cin.ignore();
  getline(cin, name);

  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  map<string, unsigned int>::const_iterator pair = namesMap.find(name);
  cout << pair->first << "=>" << pair->second << endl;      
  if(pair == namesMap.end())
    cout << endl << "Customer doesn't exist!";
  else
    {
      unsigned int id = supermarket.getCustomers()[pair -> second].getId();
      cout << "PIIIIIIM " << id; 
    showCustomerTransactionsId(supermarket.getTransactions(), supermarket.getTransactionsMap(), supermarket.getCustomers()[pair->second].getId());
  }
}


/* 
   Show all transactions 
*/
void showAllTransactions(const vector<Transaction> &vectorTransactions)
{
  vector<Transaction> transactions = vectorTransactions;
  std::sort(transactions.begin(), transactions.end(), compareByDate);

  cout << setw(5) << "ID" << setw(20) << "Date" << "\t" << "Products" << endl;
  cout << " -------------------------------------------------------------------------- " << endl;
  for(size_t i = 0; i < transactions.size() ; i++)
    {
      cout << setw(5) << transactions[i].getId();
      cout << setw(20) << transactions[i].getDate().asString() << "\t";
     
      transactions[i].showProductsTransaction();

      cout << endl;
    }
  cout << endl << endl;
}


/* 
   Show transactions of a given day 
*/
void showDayTransactions(const vector<Transaction> &vectorTransactions)
{
  vector<Transaction> transactions = vectorTransactions;
  std::sort(transactions.begin(), transactions.end(), compareByDate);

  string date_tmp;
  bool found = false;
  
  cout << "Date (d/m/y): ";
  cin >> date_tmp;
  cout << endl;

  Date choosen_date(date_tmp);
  
  if(!choosen_date.isValid())
    cout << "ERROR: Date " << date_tmp << " not valid! " << endl << endl;
  else
    {
      /* Find if there transactions in the given day */
      for(size_t i = 0; i < transactions.size() ; i++)
     	{
	  if (transactions[i].getDate() == choosen_date)
	    {
	      if(!found)
		{
		  cout << endl << setw(4) << "ID" << "\t" << "Products" << endl;
		  cout << " -------------------------------------------------------------------------- " << endl;
		  found = true;
		}

	      cout <<  setw(4) << transactions[i].getId() << "\t";

	      /* Print transactions from the chosen day */
	      transactions[i].showProductsTransaction();

	  
	      cout << endl;
	    }
	}
      if(!found)
	cout << "Transactions not found! " ;
      cout << endl << endl;
    }
}


/*
  Shows transactions between two dates 
*/
void showTransactBetwDays(const vector<Transaction> &vectorTransactions)
{
  vector<Transaction> transactions = vectorTransactions;
  std::sort(transactions.begin(), transactions.end(), compareByDate);

  string date1_tmp;
  string date2_tmp;
  bool found = false;

  cout << "Date one (d/m/y): ";
  cin >> date1_tmp;
  cout << "Date two (d/m/y): ";
  cin >> date2_tmp;
  cout << endl;

  Date date1(date1_tmp);
  Date date2(date2_tmp);

  if(!date1.isValid() || !date2.isValid())
    cout << "ERROR: One or more dates are not valid! " << endl << endl;
  else 
    {
     
      /* Find and print transactions between given dates */
      for(size_t i = 0; i < transactions.size() ; i++)
	{
	  if((transactions[i].getDate() <= date2) && (transactions[i].getDate() >= date1))
	    {
	      if(!found)
		{
		  cout << endl << setw(5) << "Id" << setw(15) << "Date" << "\t" << "Products" << endl;
		  cout << " -------------------------------------------------------------------------- " << endl;
		  found = true;
		}

	      cout <<  setw(5) << transactions[i].getId()<< setw(15) << transactions[i].getDate().asString() << "\t";
	      
	      transactions[i].showProductsTransaction();

	      cout << endl;
	    }
	}
     
      if(!found)
	cout << "Transactions not found! " << endl << endl;
    }
}


/* 
   Receive and validate the id and date for a new transaction 
*/
bool getTransactionParams(const vector<Customer> &customers, unsigned int &idCustomer, Date &dateTransaction)
{
  string date;

  bool isValid = false;
  bool isAfterToday = true;
  
  while(!isValid || isAfterToday)
    {
      cout << endl << "Date of transaction (d/m/y): ";
      cin >> date;

      dateTransaction.setDate(date);
  
      isValid = dateTransaction.isValid();
      isAfterToday = dateTransaction.isAfter(realTime());

      cin.clear();
      
      if(!isValid)
	cout << "Date not valid! Try again... " << endl << endl;
      else if(isAfterToday)
	cout << "Date not allowed! Try again... " << endl << endl;

    
    }
  
  idCustomer = validatInputCustomer();
 
  while(idCustomer == 0) //verify if ID is valid
    {
      cout << "ID not valid! Try again..." << endl << endl;
      idCustomer = validatInputCustomer();
    }
	
     
  bool found = false;
  size_t i = 0;
	  	  
  while(i < customers.size() && !found)
    {
      //verify if customers exist
      if(customers[i].getId() == idCustomer)
	found = true;
      i++;	  	       
    }

  if(!found)//if customer not exists
    {
      cout << "Customer ID not found! " << endl << endl;
      return false;
    }
  else
    return true; 
}


/* 
   Get Products for new transaction 
*/
bool getTransactionProducts(const vector<Product> &products, vector<string> &transactionProds, double &transactionAmount)
{
  int quantity;
  string input;

  cout << endl << "Products available: " << endl ;
  showProducts(products);

  cout << "How many products: ";
  cin >> input;

  std::stringstream convertor(input);

  if(convertor.fail())
    {
      cout << "Quantity of products not valid!" << endl << endl;
      return false;
    }
  else
    {
      if(convertor >> quantity)
	{
	
	  cin.ignore();
      
	  for(int i = 0; i < quantity; i++)
	    {
	      string tmpProduct;
	 
	      cout << "Product " << (i + 1) << " : " ;
	      getline (cin,tmpProduct);

	      if(productExists(products, tmpProduct))
		{
		  transactionAmount += getProductPrice(products, tmpProduct);
		  transactionProds.push_back(tmpProduct);	      
		}
	      else
		cout << "Info : product " << tmpProduct << " not added because doesn't exist." << endl;
	    }
	  return true;
	}
      else
	cout << "Quantity of products not valid!" << endl << endl;;
      return false;
      
    }
}


/*
  Building a new transaction 
*/
void addTransaction(Supermarket &supermarket)
{
  Date dateTransaction;
  unsigned int idCustomer = 0;
  double transactionAmount = 0;
  vector<string> transactionProds;

  /* Verify if transaction is valid  */
  bool transactionSuccess = getTransactionParams(supermarket.getCustomers(), idCustomer, dateTransaction) && getTransactionProducts(supermarket.getProducts(), transactionProds, transactionAmount);
  
  if(transactionSuccess)
    { 
      Transaction newTransaction = supermarket.newTransaction(idCustomer, dateTransaction, transactionProds, transactionAmount);
	
      saveCustomers(supermarket.getCustomers(), supermarket.getCustomersFileName());
      saveTransaction(supermarket.getTransactions(), supermarket.getTransactionsFileName());

      cout << endl << "Success, new transaction was added! " << endl << endl;
      cout << "ID: " << newTransaction.getId() << endl;
      cout << "Date: " << newTransaction.getDate().asString() << endl;
      cout << "Products:  ";

      for(size_t i = 0; i < newTransaction.getProducts().size(); i++)
	{
	  cout << newTransaction.getProducts()[i];

	  if(i != newTransaction.getProducts().size() - 1)
	    cout << ", ";
	}
      cout << endl << endl;
    }
}


/* 
   Save all transactions 
*/
void saveTransaction(const vector<Transaction> &transactions, const string &transactionFile)
{
  ofstream t_file;
  t_file.open(transactionFile);
     
  t_file << transactions.size() << endl;
 
  for(size_t j = 0; j < transactions.size() ; j++)
    {
      t_file << transactions[j].getId() << " ; " << transactions[j].getDate().asString() << " ; ";

      for(size_t i = 0; i < transactions[j].getProducts().size(); i++)
	{
	  t_file << transactions[j].getProducts()[i];

	  if(i != transactions[j].getProducts().size() - 1)
	    t_file << ", ";
	}

      t_file << endl;
    }

  t_file.close();
}
