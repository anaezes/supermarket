#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Supermarket;

class Product
{
public:
  Product();
  Product(string name, double price);
  void setName(string name);
  void setPrice(double price);
  string getName() const;
  double getPrice() const;

private:
  string name;
  double price;
};

void showProducts(const vector<Product>&);

void addProducts(Supermarket &);

void saveProducts(const vector<Product>&, const string&);

double getProductPrice(const vector<Product>&, const string&);

bool productExists(const vector<Product>&, const string&);
