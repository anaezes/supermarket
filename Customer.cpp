#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>    // std::sort
#include <locale>       // std::tolower
#include <fstream>
#include <string.h>

#include "Supermarket.hpp"
#include "Customer.hpp"
#include "Transaction.hpp"
#include "Menu.hpp"


using namespace std;


/******************************************************/
/*             CUSTOMER CLASS FUNCTIONS               */
/******************************************************/

Customer::Customer()
{
  setId(-1);
  setName("");
  setJoinDate(Date("1/1/1970"));
  setAmount(0);
}


Customer::Customer(unsigned int id, string name, string joinDate, double amount)
{
  setId(id);
  setName(name);
  setJoinDate(joinDate);
  setAmount(amount);
}


void Customer::setId(unsigned int id)
{
  this->id = id;
}


void Customer::setName(string name)
{
  this->name = name;
}


void Customer::setJoinDate(Date joinDate)
{
  this->joinDate = joinDate;
}


void Customer::setAmount(double amount)
{
  this->amount = amount;
}


unsigned int Customer::getId() const
{
  return id;
}


string Customer::getName() const
{
  return name;
}


Date Customer::getJoinDate() const
{
  return joinDate;
}


double Customer::getAmount() const
{
  return amount;
}




/******************************************************/
/*           CUSTOMERS GENERAL FUNCTIONS              */
/******************************************************/


/* 
   Validates all id inputs customers 
*/
int validatInputCustomer()
{ 
  string input;
  unsigned int id;

  cout << "ID customer: ";
  cin >> input ;

  std::stringstream convertor(input);

  if(convertor.fail())
    return 0;
  else
    {
      if(convertor >> id)
	return id;
      else
	return 0;
    }
}


/* 
   Shows information from a customer whose id was given 
*/
void showCustomerInfoId(const map<unsigned int, unsigned int> &customerIdMap, const vector<Customer> &customers)
{
  unsigned int idCustomer = validatInputCustomer();
  
  if(idCustomer == 0)
    cout << endl << "ID not valid!" << endl << endl;
  else
    {
      map<unsigned int, unsigned int>::const_iterator pair = customerIdMap.find(idCustomer);
      if(pair == customerIdMap.end())
	cout << endl << "Customer doesn't exist!";
      else
	{
	  cout << endl << "Name: " << customers[pair->second].getName() << endl;
	  cout << "Accession Date: " << customers[pair->second].getJoinDate().asString() << endl;
	  cout << "Amount: " << customers[pair->second].getAmount() << "e" << endl;
	}
      cout << endl << endl;
    }
}


/* 
   Shows transactions from a customer 
   whose name was given 
*/
void showCustomersInfoName(const map<string, unsigned int> &customerNameMap, const vector<Customer> &customers)
{
  string name;

  cout << "Customer name: " ;
  cin.ignore();
  getline(cin, name);
  
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  map<string, unsigned int>::const_iterator pair = customerNameMap.find(name);
        
  if(pair == customerNameMap.end())
    cout << endl << "Customer doesn't exist!";
  else
    {
      cout << endl <<"Id: " << customers[pair->second].getId() << endl;
      cout << "Accession Date: " << customers[pair->second].getJoinDate().asString() << endl;
      cout << "Amount: " << customers[pair->second].getAmount() << "e" << endl;

    }
  cout << endl << endl;
    
}

/*
  Function used while sorting customers
  by name.
*/
bool compareByName(const Customer &name_a, const Customer &name_b)
{
  return name_a.getName() < name_b.getName();
}

/*
  Show all customers info
*/
void showAllCustomersInfo(const vector<Customer> &vectorCustomers)
{
  vector<Customer> customers = vectorCustomers;
  std::sort(customers.begin(), customers.end(), compareByName);

  cout << setw(5) << "ID" << setw(25) << "Name" << setw(20) << "Accession date" << setw(15) << "Amount" << endl;
  cout << " ---------------------------------------------------------------- " << endl;
  
  showCustomers(customers);

  cout << endl << endl;
}


/*
  Returns the current maximum customer id 
*/
unsigned int verifyMaximum(const vector<Customer> &customers,const vector<Transaction> &transactions)
{
  unsigned int idMax = 0;
  
  /* find the max id in customers list*/
  for(size_t i = 0; i < customers.size() ; i++)
    {
      if(customers[i].getId() > idMax)
	idMax = customers[i].getId();
    }

  /* check if any of the ids in the transactions is bigger than max */
  for(size_t j = 0; j < transactions.size(); j++)
    {
      if(transactions[j].getId() > idMax)
	idMax = transactions[j].getId();
    }

  return idMax;
}


/*
  Add new customer
*/
void addCustomer(Supermarket &supermarket)
{
  int idMax = verifyMaximum(supermarket.getCustomers(), supermarket.getTransactions());

  string name;
  cout << "Customer's name: ";
  cin.ignore();
  getline(std::cin, name);

  Customer newCustomer = supermarket.addCustomer(idMax + 1, name);

  //  ofstream c_file;
  
  saveCustomers(supermarket.getCustomers(), supermarket.getCustomersFileName());

  cout << endl << "Success, new customer was added! " << endl << endl;

  cout << "ID: " << newCustomer.getId() << endl;
  cout << "Name: " << newCustomer.getName() << endl;
  cout << "Accession Date: " << newCustomer.getJoinDate().asString() << endl;
  cout << "Amount:  " << newCustomer.getAmount() << "e" << endl << endl;
}


void editCustomer(Supermarket &supermarket)
{
  unsigned int idCustomer = validatInputCustomer();
  
  if(idCustomer == 0)
    cout << "ID not valid!" << endl << endl;
  else
    {
      if(supermarket.editCustomer(idCustomer))
	saveCustomers(supermarket.getCustomers(), supermarket.getCustomersFileName());
      else
	cout << "Not found customer!" << endl;
    }

}


/*
  Remove customer whose id is given 
*/
void removeCustomer(Supermarket &supermarket)
{  
  unsigned int idCustomer = validatInputCustomer();
  
  if(idCustomer == 0)
    cout << "ID not valid!" << endl << endl;
  else
    {
      if(supermarket.removeCustomer(idCustomer))
	saveCustomers(supermarket.getCustomers(), supermarket.getCustomersFileName());
      else
	cout << "Not found customer!" << endl;
    }
}


/*
  Save customers in file after modification
*/
void saveCustomers(const vector<Customer> &customers, const string &customersFile)
{
  ofstream c_file;
  c_file.open(customersFile);
     
  c_file << customers.size() << endl;
 
  for(size_t i = 0; i < customers.size() ; i++)
    c_file << customers[i].getId() << " ; " << customers[i].getName() << " ; " << customers[i].getJoinDate().asString() << " ; " << customers[i].getAmount() << endl;
  c_file.close();
}


/*
  Helper function to display customers
*/
void showCustomers(const vector<Customer> &costumers)
{
  for(size_t i = 0; i < costumers.size() ; i++)
    {
      cout << setw(5) << costumers[i].getId();
      cout << setw(25) << costumers[i].getName();
      cout << setw(20) << costumers[i].getJoinDate().asString();
      cout << setw(14) << costumers[i].getAmount() << "e" << endl;
    }
}


/* 
   Sort customers by increasing amount 
*/
bool compareByAmount(const Customer &amountCostumer1, const Customer &amountCostumer2)
{
  return amountCostumer1.getAmount() < amountCostumer2.getAmount();
}

