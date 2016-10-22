#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <string.h>
#include <fstream>

#include "Product.hpp"
#include "Supermarket.hpp"

using namespace std;


/******************************************************/
/*             PRODUCT CLASS FUNCTIONS               */
/******************************************************/

Product::Product()
{
  setName("");
  setPrice(0);
}


Product::Product(string name, double price)
{
  setName(name);
  setPrice(price);
}


void Product::setName(string name)
{
  this->name = name;
}


void Product::setPrice(double price)
{
  this->price = price;
}


string Product::getName() const
{
  return name;
}


double Product::getPrice() const
{
  return price;
}



/******************************************************/
/*             PRODUCTS CLASS FUNCTIONS               */
/******************************************************/

void showProducts(const vector<Product> &products)
{
  cout << endl << setw(20)<< "Product" << setw(17) << "Price" << endl;
  cout << " ------------------------------------- " << endl;
  
  for(size_t i = 0; i < products.size(); i++ )
    cout << setw(20) << products[i].getName() << setw(15) << products[i].getPrice() << " e" << endl;
   
  cout << endl;

}


void addProducts(Supermarket &supermarket)
{
  string name;
  cout << "Product's name: ";
  cin.ignore();
  getline(cin, name);

  double price;
  cout << "Price of product: ";
  cin >> price;

    while( cin.fail() || (cin.peek() != '\r' && cin.peek() != '\n'))
      {
        cout << "Invalid Input! Please input a numerical value." << endl;
        cin.clear();
        while( cin.get() != '\n' ); // or cin.ignore(1000, '\n');
	cout << "Price of product: ";
        cin >> price;
      }
    Product newProduct = supermarket.addProduct(name, price);

    saveProducts(supermarket.getProducts(), supermarket.getProductsFileName());

    cout << "Sucess, new product was added! " << endl << endl;
}


void saveProducts(const vector<Product> &products, const string &productsFile)
{
  ofstream c_file;
  c_file.open(productsFile);
     
  c_file << products.size() << endl;
 
  for(size_t i = 0; i < products.size() ; i++)
    c_file << products[i].getName() << " ; " << products[i].getPrice() << endl;
  c_file.close();
}


double getProductPrice(const vector<Product> &products, const string &product)
{
  size_t i = 0;
  double price;
  bool found = false;
  
  while(!found && i < products.size())
    {
      if(products[i].getName() == product)
	{
	  found = true;
	  price = products[i].getPrice();
	}
  i++;
    }

  return price;
}


bool productExists(const vector<Product> &products, const string &product)
{
  for(size_t i = 0; i < products.size(); i++)
    if(strcasecmp(products[i].getName().c_str(), product.c_str()) == 0)
      return true;
  
  return false;
}
