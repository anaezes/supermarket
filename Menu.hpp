#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Supermarket.hpp"
#include "Customer.hpp"
#include "Transaction.hpp"
#include "Product.hpp"


using namespace std;

void showCustomersMenu();
void customersMenu(Supermarket&);
void showTransactionsMenu();
void transactionsMenu(Supermarket&);
void showLogo();
void showMainMenu();
void menuMain(Supermarket&);


