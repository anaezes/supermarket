#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>

#include "Menu.hpp"
#include "Recommendation.hpp"

using namespace std;


/******************************************************/
/*               CUSTOMERS MENU                       */
/******************************************************/

void showCustomersMenu()
{
  cout << endl << endl;
  cout << "    Select our choice: " << endl;
  cout << " --------------------------------------" << endl; 
  cout << "    1 : Show customer's info by id" << endl;
  cout << "    2 : Show customer's info by name" << endl;
  cout << "    3 : Show all customers' info" << endl;
  cout << "    4 : Add customer" << endl;
  cout << "    5 : Edit customer" << endl;
  cout << "    6 : Remove customer" << endl;
  cout << " --------------------------------------" << endl << endl;
  cout << "    0 : Back" << endl << endl; 
  cout << " > " ;
}


void customersMenu(Supermarket &supermarket)
{
  char userChoice = '1';

  while(userChoice != '0')
    {
      showCustomersMenu();
      cin >> userChoice;
      cout << endl << endl;

      if(!isdigit(userChoice) || userChoice > '6' || userChoice < '0')
	cout << endl << "ERROR: Computer says no! Wrong option, try again." << endl << endl;
      else
	{
	  if(userChoice == '1')
	    {
	      cout << endl << "Show customer's information by id: " << endl << endl;
	      showCustomerInfoId(supermarket.getCustomersIdMap(), supermarket.getCustomers());
	    }
	  else if(userChoice == '2')
	    {
	      cout << endl << "Show customer's information by name: " << endl << endl;
	      showCustomersInfoName(supermarket.getCustomersNameMap(), supermarket.getCustomers());
	    }
	  else if(userChoice == '3')
	    {
	      cout << endl << "Show all customers information: " << endl << endl; 
	      showAllCustomersInfo(supermarket.getCustomers());
	    }
	  else if(userChoice == '4')
	    {
	      cout << endl << "Add new customer:  " << endl << endl;
	      addCustomer(supermarket);
	    }
	  else if(userChoice == '5')
	    {
	      cout << endl << "Edit customer information: " << endl << endl;
	      editCustomer(supermarket);
	    }
	  else if(userChoice == '6')
	    {
	      cout << endl << "Remove customer: " << endl << endl;
	      removeCustomer(supermarket);
	    }

	  if(userChoice != '0')
	    {
	      cout << endl << "Press ENTER to continue...";
	      if(userChoice != '2' && userChoice != '4')
		getchar();
	      getchar();
	    }  
	}
    }
}


/******************************************************/
/*             TRANSACTIONS MENU                      */
/******************************************************/

void showTransactionsMenu()
{
  cout << endl;
  cout << "    Select our choice: " << endl;
  cout << " --------------------------------------" << endl; 
  cout << "    1 : Show customer's transactions by Id" << endl;
  cout << "    2 : Show customer's transactions by Name" << endl;
  cout << "    3 : Show all transactions" << endl;
  cout << "    4 : Show transactions of a given day" << endl;
  cout << "    5 : Show transactions between days" << endl;
  cout << "    6 : Add transaction" << endl;
  cout << " --------------------------------------" << endl << endl;
  cout << "    0 : Back" << endl << endl; 
  cout << " > " ;
}


/* transactions menu */
void transactionsMenu(Supermarket &supermarket)
{
  char userChoice = '1';

  while(userChoice != '0')
    {
      showTransactionsMenu();
      cin >> userChoice;
      cout << endl << endl;

      if(!isdigit(userChoice) || userChoice > '6' || userChoice < '0')
	cout << endl << "ERROR: Computer says no! Wrong option, try again." << endl << endl;
      else
	{
	  if(userChoice == '1')
	    {
	      cout << endl << "Show customer transaction by id: " << endl << endl;
	      unsigned int idCustomer = validatInputCustomer();
	      showCustomerTransactionsId(supermarket.getTransactions(), supermarket.getTransactionsMap(), idCustomer);
	    }
	  else  if(userChoice == '2')
	    {
	      cout << endl << "Show customer transaction by name: " << endl << endl;
	      showCustomerTransactionsName(supermarket);
	    }
	  else if(userChoice == '3')
	    {
	      cout << endl << "Show all transactions: " << endl << endl; 
	      showAllTransactions(supermarket.getTransactions());
	    }
	  else if(userChoice == '4')
	    {
	      cout << endl << "Show day transactions: " << endl << endl; 
	      showDayTransactions(supermarket.getTransactions());
	    }
	  else if(userChoice == '5')
	    {
	      cout << endl << "Show transactions between days: " << endl << endl; 
	      showTransactBetwDays(supermarket.getTransactions());
	    }
	  else if(userChoice == '6')
	    {
	      cout << endl << "Add new transaction: " << endl << endl;
	      addTransaction(supermarket);
	    }

	  if(userChoice != '0')
	    {
	      cout << endl << "Press ENTER to continue...";
	      if(userChoice != '2' && userChoice != '6')
		getchar();
	      getchar();
	    }
	}
    }
}



/******************************************************/
/*                PRODUCTS MENU                       */
/******************************************************/

void showProductsMenu()
{
  cout << endl << endl;
  cout << "    Select our choice: " << endl;
  cout << " --------------------------------------" << endl; 
  cout << "    1 : Show products available" << endl;
  cout << "    2 : Add products" << endl;
  cout << " --------------------------------------" << endl << endl;
  cout << "    0 : Back" << endl << endl; 
  cout << " > " ;
}


void productsMenu(Supermarket &supermarket)
{
  char userChoice = '1';

  while(userChoice != '0')
    {
      showProductsMenu();
      cin >> userChoice;
      cout << endl << endl;

      if(!isdigit(userChoice) || userChoice > '2' || userChoice < '0')
	cout << endl << "ERROR: Computer says no! Wrong option, try again." << endl << endl;
      else
	{
	  if(userChoice == '1')
	    {
	      cout << endl << "Show products & prices: " << endl << endl; 
	      showProducts(supermarket.getProducts());
	    }
	  else if(userChoice == '2')
	    {
	      cout << endl << "Add new product: " << endl << endl;
	      addProducts(supermarket);
	    }

	  if(userChoice != '0')
	    {
	      cout << endl << "Press ENTER to continue...";
	      if(userChoice != '2')
		getchar();
	      getchar();
	    }  
	}
    }
}



/******************************************************/
/*                GENERAL MENU                        */
/******************************************************/

void showLogo()
{ 
  cout << endl << endl << endl;
  cout <<"              __                                       " << endl;
  cout <<"  /\\/\\  _   _/ _\\_   _ _ __   ___ _ __  _     _     " << endl;
  cout <<" /    \\| | | \\ \\| | | | '_ \\ / _ | '___| |_ _| |_  " << endl;
  cout <<"/ /\\/\\ | |_| _\\ | |_| | |_) |  __| | |_   _|_   _|  " << endl;
  cout <<"\\/    \\/\\__, \\__/\\__,_| .__/ \\___|_|   |_|   |_| " << endl;
  cout <<"        |___/         |_|                             " << endl;
}


void showMainMenu()
{
  showLogo();

  cout << endl << endl;
  cout << "    Select our choice: " << endl;
  cout << " --------------------------------------" << endl; 
  cout << "    1 : Show customers menu" << endl;
  cout << "    2 : Show transactions menu" << endl;
  cout << "    3 : Show products menu" << endl;
  cout << "    4 : Bottom10" << endl << endl;
  cout << "    5 : Make recommendation - Customer's Id" << endl;
  cout << "    6 : Make recommendation - Botom10" << endl << endl;
  cout << " --------------------------------------" << endl << endl;
  cout << "    0 : Exit" << endl << endl; 
  cout << " > " ;
}


/* menu main */
void menuMain(Supermarket &supermarket)
{
  char userChoice = '1';

  while(userChoice != '0')
    {
      showMainMenu();
      cin >> userChoice;

      if(!isdigit(userChoice) || userChoice > '6' || userChoice < '0')
	cout << endl << "ERROR: Computer says no! Wrong option, try again." << endl << endl;
      else
	{
	  if(userChoice =='0')
	    cout << "Computer says good bye!" << endl;
	  else if(userChoice == '1')
	    customersMenu(supermarket);
	  else if(userChoice == '2')
	    transactionsMenu(supermarket);
	  else if(userChoice == '3')
	    productsMenu(supermarket);
	  else if(userChoice =='4')
	    supermarket.showBottom10();
	  else if(userChoice == '5')
	    makeRecommendationId(supermarket);
	  else 
	    makeRecommendationBottom10(supermarket);

	  if(userChoice > '3')
	    {
	      cout << "Press ENTER to continue...";
	      getchar();
	      getchar();
	    }
	  
	}
    }
}
