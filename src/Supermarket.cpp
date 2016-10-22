#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string.h>
#include <algorithm>    // std::sort
#include <utility>      


#include "Supermarket.hpp"

using namespace std;



/******************************************************/
/*            SUPERMARKET CLASS FUNCTIONS             */
/******************************************************/


Supermarket::Supermarket(string name, string customersFile, string transactionsFile, string productsFile)
{
  this->name = name;
  this->customersFile = customersFile;
  this->transactionsFile = transactionsFile;
  this->productsFile = productsFile;
}


vector<Customer> Supermarket::getCustomers()
{
  return customers;
}


vector<Transaction> Supermarket::getTransactions() const
{
  return transactions;
}


vector<Product> Supermarket::getProducts() const
{
  return products;
}


string Supermarket::getCustomersFileName() const
{
  return customersFile;
}


string Supermarket::getTransactionsFileName() const
{
  return transactionsFile;
}


string Supermarket::getProductsFileName() const
{
  return productsFile;
}


map<unsigned int, unsigned int> Supermarket::getCustomersIdMap() const
{
  return customersIdMap;
}


map<string, unsigned int> Supermarket::getCustomersNameMap() const
{
  return customersNameMap;
}


multimap<unsigned int, unsigned int> Supermarket::getTransactionsMap() const
{
  return transactionsMap;
}


map<string, unsigned int> Supermarket::getProductsMap() const
{
  return productsMap;
}


/* Insert new customer in vector of Customers and insert in the maps*/
Customer Supermarket::addCustomer(unsigned int id, string name)
{
  Customer newCustomer(id, name, realTime(), 0);  
  customers.push_back(newCustomer);

  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  customersNameMap.insert(pair<string, unsigned int> (name, customers.size()-1));
  customersIdMap.insert(pair<unsigned int, unsigned int> (id, customers.size()-1));

  return newCustomer;
}



Product Supermarket::addProduct(string name, double price)
{
  Product newProduct(name, price);
  products.push_back(newProduct);

  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  productsMap.insert(pair<string, double> (name, products.size()-1));

  return newProduct;
}



bool Supermarket::editCustomer(unsigned int id)
{
  char userChoice = '1';

  map<unsigned int, unsigned int>::const_iterator pair = customersIdMap.find(id);
  if(pair == customersIdMap.end())
    return false;
  else
    {
      cout << "Edit name? (y/n): ";
      cin >> userChoice;

      if(userChoice == 'y')
	editCustomerName(customers[pair->second]);

      cout << "Edit accession date? (y/n): ";
      cin >> userChoice;

      if(userChoice == 'y')
	editCustomerDate(customers[pair->second]);

      return true;
    }						
}



void Supermarket::editCustomerName(Customer &customer)
{
  string newName;

  cout << "New name: ";
  cin.ignore();
  getline(cin, newName);

  customer.setName(newName);
}



void Supermarket::editCustomerDate(Customer &customer)
{
  string date;

  cout << "Date (d/m/y): ";
  cin >> date;
  cout << endl;

  Date newDate(date);
  while(!newDate.isValid())
    {
      cout << "Date not valid! " << endl;
      cout << "Date (d/m/y): ";
      cin >> date;
      cout << endl;

      newDate.setDate(date);
    }
  customer.setJoinDate(newDate);
}



bool Supermarket::removeCustomer(unsigned int id)
{
  size_t i = 0;
  bool found = false;
  string name;
  
  while(i < customers.size() && !found)
    {
      if(customers[i].getId() == id)
	{
	  name = customers[i].getName();
	  customers.erase (customers.begin()+i);
	  found = true;
	  cout << endl << "Success, customer was removed! " << endl << endl;
	}
      i++;
    }

  customersIdMap.erase(id);
  customersNameMap.erase(name);
  
  return found;
}



Transaction Supermarket::newTransaction(unsigned int idCustomer, Date dateTransaction, vector<string> prods, double transactionAmount)
{
  /* update customer's amount*/
  bool found = false;
  size_t i = 0;
	
  while(i < customers.size() && !found)
    {
      if(customers[i].getId() == idCustomer)
	{
	  customers[i].setAmount(customers[i].getAmount()+transactionAmount);
	  cout << endl << "Amount of transaction: " << transactionAmount << "e" << endl;
	  found = true;
	}
      i++;
    }

  /* Create new transaction */
  Transaction newTransaction;

  newTransaction.setId(idCustomer);
  newTransaction.setDate(dateTransaction);
  newTransaction.setProducts(prods);

  transactions.push_back(newTransaction);
  transactionsMap.insert(pair<unsigned int, unsigned int>(idCustomer, transactions.size()-1));

  return newTransaction;
}


/*
  Reads a given file and separates it to a vector
  of its lines. Returns true if success.
*/
bool Supermarket::readFile(const string &fileName, vector<string> &fileLines)
{
  ifstream cFile;
  string line;

  /* try to open the file */
  cFile.open(fileName.c_str());

  if(!cFile.is_open())
    return false;
  else
    {
      /* Read file content */
      while(getline(cFile, line))
	fileLines.push_back(line); /*store line in the vector*/
      cFile.close();
      return true;
    }
}


/*
  Reads the customers file, stores their information
  in objects of class Customer. All the customers are
  stored in the vector customers passed by reference.
  Returns true if success.
*/
bool Supermarket::readCustomersFile()
{
  vector<string> customersLines;

  /* try to get the file lines */
  if(!readFile(customersFile, customersLines))
    return false;
  else
    {
      int nCostumers;
      stringstream ss(customersLines[0]);
      ss >> nCostumers;

      for(int i = 1; i <= nCostumers ; i++)
	{
	  size_t pos;
	  size_t j = 0;
	  string substring;
	  string line = customersLines[i];

	  unsigned int id;
	  string name;
	  string joinDate;
	  double amount;

	  pos = line.find(';');
	  while(pos != string::npos)
	    {
	      substring = line.substr( 0, pos-1);
	      if(j == 0)
		{
		  stringstream ss(substring);
		  int tmp;
		  ss >> tmp;
		  id = tmp;
		}
	      else if(j == 1)
		name = substring;
	      else
		joinDate = substring;

	      line = line.substr(pos + 2, line.length());
	      pos = line.find(';');
	      j++;
	    }

	  stringstream ss(line);
	  double tmp;
	  ss >> tmp;
	  amount = tmp;

	  Customer newCustomer(id, name, joinDate, amount);

	  customers.push_back(newCustomer);
	   
	  customersIdMap.insert(pair<unsigned int, unsigned  int> (id, customers.size()-1));

	  /* store name as lowercase */
	  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	  customersNameMap.insert(pair<string, unsigned int> (name, customers.size()-1));
	}
    } 

  return true;
}



/*
  Reads the transactions file, stores its information
  in objects of class Transactions. All the transactions
  are stored in the vector transactions passed by reference.
  Returns true if success.
*/
bool Supermarket::readTransactionsFile()
{
  vector<string> transactionsLines;

  if(!readFile(transactionsFile, transactionsLines))
    return false;
  else
    {
      int nTransactions;
      stringstream ss(transactionsLines[0]);
      ss >> nTransactions;

      for(int j = 1; j <= nTransactions; j++)
	{
	  size_t pos;
	  size_t i = 0;
	  unsigned int id;
	  string substring;
	  Transaction newTransaction;
	  string line = transactionsLines[j];

	  pos = line.find(';');

	  while(pos != string::npos)
	    {
	      substring = line.substr(0, pos-1);
	      if(i == 0)
		{
		  stringstream ss(substring);
		  ss >> id;
		  newTransaction.setId(id);
		}
	      else
		{
		  Date newDate(substring);
		  newTransaction.setDate(newDate);
		}
	    
	      line = line.substr(pos + 2, line.length());
	      pos = line.find(';');
	      i++;
	    }

	  /* parse products */
	  pos = line.find(',');
	  vector<string> products;

	  while(pos != string::npos)
	    {
	      substring = line.substr(0, pos);
	      newTransaction.addProduct(substring);
	      //products.push_back(substring);

	      line = line.substr(pos + 2, line.length());
	      pos = line.find(',');
	    }

	  substring = line.substr(0, line.length());
	  //products.push_back(substring);
	  newTransaction.addProduct(substring);
	  //newTransaction.setProducts(products);

	  transactions.push_back(newTransaction);

	  transactionsMap.insert(pair<unsigned int, unsigned int> (id, transactions.size()-1));
	}
    }

  return true;
}


/*
  Reads the products file, stores its information
  in objects of class Products. All the products
  are stored in the vector products passed by reference.
  Returns true if success.
*/
bool Supermarket::readProductsFile()
{
  vector<string> productsLines;

  if(!readFile(productsFile, productsLines))
    return false;
  else
    {
      int nProducts;
      stringstream ss(productsLines[0]);
      ss >> nProducts;
       
      for(int j = 1; j <= nProducts; j++) 	
	{
 	  string line = productsLines[j];
 	  size_t pos = line.find(';');
	  Product newProduct;
	  string name = line.substr(0, pos-1);
	  
 	  newProduct.setName(name);
 	  line = line.substr(pos + 2, line.length());

 	  /* string to double */
 	  stringstream ss(line);
	  double tmp;

 	  ss >> tmp;
	  newProduct.setPrice(tmp);
	  
 	  products.push_back(newProduct);
	  productsMap.insert(pair<string, unsigned int> (name, products.size()-1));
 	}
    }

  return true;
}


/*
  Sort Customers by amount (increasing)
  and select the first 10.
*/

void Supermarket::showBottom10()
{
  vector <Customer> vectorBottom10 = getBottom10();
  
  cout << endl << "Show the bottom 10 customers" << endl << endl; 
  cout << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Accession date" << setw(15) << "Amount" << endl;
  cout << " ------------------------------------------------------------- " << endl;
 
  showCustomers(vectorBottom10);

  cout << endl << endl;

}


/**/
vector<Customer> Supermarket::getBottom10()
{
  vector<Customer> sortedCustomers = this->customers;
  std::sort(sortedCustomers.begin(), sortedCustomers.end(), compareByAmount);

  vector <Customer> vectorBottom10;
  size_t i = 0;

  while(i < 5 && i < sortedCustomers.size())
    {
      vectorBottom10.push_back(sortedCustomers[i]);
      i++;
    }

  return vectorBottom10;
}
