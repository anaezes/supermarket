#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>

#include "Supermarket.hpp"
#include "Menu.hpp"
#include "Customer.hpp"
#include "Transaction.hpp"
#include "Product.hpp"

using namespace std;

int main()
{
  string nameStore;
  string customersFile;
  string transactionsFile;
  string productsFile;

  cout << "Supermarket name: ";
  cin >> nameStore;
  cout << "Customers file name: ";
  cin >> customersFile;
  cout << "Transactions file name: ";
  cin >> transactionsFile;
  cout << "Products file name: ";
  cin >> productsFile;

  Supermarket supermarket(nameStore, customersFile, transactionsFile, productsFile);
  
  bool customersSuccess = supermarket.readCustomersFile();
  bool transactSuccess = supermarket.readTransactionsFile();
  bool productsSuccess = supermarket.readProductsFile();

  if(!(customersSuccess && transactSuccess && productsSuccess))
    {
      cout << "Error while reading a file" << endl;
      return -1;
    }
  else
    {  
      cout << endl << endl << setw(10) << "Computer says welcome to program!" << endl;
      menuMain(supermarket);
    }

  return 0;
}
