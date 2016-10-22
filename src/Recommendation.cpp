#include <iostream>
#include <vector>
#include <map>
#include <locale>
#include <string>
#include <algorithm>

#include "Recommendation.hpp"
#include "Customer.hpp"
#include "Transaction.hpp"
#include "Product.hpp"
#include "Menu.hpp"

using namespace std;


/******************************************************/
/*             RECOMMENDATION FUNCTIONS               */
/******************************************************/

bool verifyIdCustomer(const map<unsigned int, unsigned int> &customerIdMap, unsigned int &id)
{
   id = validatInputCustomer();

   if(id == 0)
   {
      cout << "Id not valid!" << endl << endl;
      return false;
   }
   else
   {
      map<unsigned int, unsigned int>::const_iterator pair = customerIdMap.find(id);
      if(pair == customerIdMap.end())
      {
   cout << endl << "Customer doesn't exist!";
   return false;
      }
      else
   return true;
   }
}


/* Returns the index of a product in the product map */
int getProductIndex(string product, const map<string, unsigned int> &productsMap)
{
   map<string, unsigned int>::const_iterator pair = productsMap.find(product);

   return pair->second;
}

/* computes how much two customers are similar (in terms of bought products) */
double computeMatchPercentage(vector<bool> customer_a, vector<bool> customer_b)
{
   int matches = 0;
   int boughtByA = 0; // number of products bought by customer A.

   for(size_t i = 0; i < customer_a.size(); i++)
   {
      if(customer_a[i] == true)
      {
   boughtByA++;
   if(customer_a[i] == customer_b[i])
      matches++;
      }
   }
   return (double)matches/boughtByA * 100;
}


/* Recommends products from customer b to customer a.
   If not repeated saves them in the recommendation vector */
void getRecommendation(map<string, unsigned int> &recommendation, const vector<Product> &products, vector<bool> customer_a, vector<bool> customer_b)
{
   for(size_t i = 0; i < customer_a.size(); i++)
   {
      if(customer_b[i] == true && customer_a[i] == false)
      {
   string prodName = products[i].getName();

   map<string, unsigned int>::const_iterator ret = recommendation.find(prodName);
   if(ret == recommendation.end())
      recommendation.insert(pair<string, unsigned int> (prodName, 1));
   else
      recommendation[prodName]++;
      }
   }
}

/* Builds a boolean  matrix, where each line is a customer
and each column is a product.
A true means that customer i bought j */
vector<vector<bool> > getRecommendationMatrix(Supermarket& supermarket)
{
   unsigned int nrows = verifyMaximum(supermarket.getCustomers(), supermarket.getTransactions()); // number maximum of id's
   unsigned int ncols = supermarket.getProducts().size();
   vector<Transaction> transactions = supermarket.getTransactions();
   map<string, unsigned int> productsMap = supermarket.getProductsMap();

   vector<vector<bool> > customersProductsMatrix(nrows, vector<bool>(ncols, false));

   for(size_t i = 0; i < transactions.size(); i++)
   {
      for(size_t j = 0; j < transactions[i].getProducts().size(); j++)
      {
   int row = transactions[i].getId() - 1;
   int col = getProductIndex(transactions[i].getProducts()[j], productsMap);
   customersProductsMatrix[row][col] = true;
      }
   }
   return customersProductsMatrix;
}

/* display the most recommended products */
void displayMostCommonProduct(map<string, unsigned int> recommendedProds)
{
   unsigned int maxOccurrences = 0;
   for(auto i = recommendedProds.begin() ; i != recommendedProds.end(); i++)
      if(i->second > maxOccurrences)
   maxOccurrences = i->second;

   for(auto i = recommendedProds.begin() ; i != recommendedProds.end(); i++)
      if(i->second == maxOccurrences)
      {
   cout << i->first << endl;
      }
}


/* main funtion for the recommendation */
void makeRecommendationId(Supermarket &supermarket)
{
   double matchPercentage = 60;
   unsigned int id = 0;
   map<string, unsigned int> recommendation;
   vector<Product> products = supermarket.getProducts();

   vector<vector<bool> > customersProductsMatrix = getRecommendationMatrix(supermarket);

   if(verifyIdCustomer(supermarket.getCustomersIdMap(), id))
   {
      for(unsigned int i = 0; i < customersProductsMatrix.size(); i++)
      {
   if(i != id-1)
   {
      double result = computeMatchPercentage(customersProductsMatrix[id - 1], customersProductsMatrix[i]);

      if(result >= matchPercentage)
         getRecommendation(recommendation, products, customersProductsMatrix[id - 1], customersProductsMatrix[i]);
   }
      }

      if(recommendation.size() == 0)
   cout << endl << "Without possible recommendation for this customer." << endl;
      else
      {
   cout << endl <<  "Recommendation for this customer: " << endl;
   displayMostCommonProduct(recommendation);
      }

      cout << endl << endl;
   }
}





/******************************************************/
/*          BOTTOM 10 RECOMENDATION FUNCTIONS         */
/******************************************************/



/* Merge all the customers of bottom10 in one, and
   creates a matrix line with the commom products */
vector<unsigned int> getCommonProducts(vector<vector<bool> > customersProductsMatrix)
{
   unsigned int nProds = customersProductsMatrix[0].size();
   vector<unsigned int> matrixLine(nProds, 0);

   /* go through clients */
   for(size_t i = 0; i < customersProductsMatrix.size(); i++)
   {
     for(size_t j = 0; j < nProds ; j++)
       {
   if(customersProductsMatrix[i][j] == true)
     matrixLine[j] += 1;
       }
   }
   return matrixLine;
}


/* Build a matrix of boolean for the bottom 10 customers */
vector<vector<bool> > getBottom10Matrix(const Supermarket &supermarket, vector<Customer> &bottom10)
{
   unsigned int nrows = bottom10.size();
   unsigned int ncols = supermarket.getProducts().size();
   vector<Transaction> transactions = supermarket.getTransactions();
   multimap<unsigned int, unsigned int> transactionsMap = supermarket.getTransactionsMap();
   map<string, unsigned int> productsMap = supermarket.getProductsMap();

   vector<vector<bool> > bottom10Matrix(nrows, vector<bool>(ncols, false));

   for(size_t i = 0; i < bottom10.size(); i++)
   {
      unsigned int idCustomer = bottom10[i].getId();
      auto ret = transactionsMap.equal_range(idCustomer);

      if(ret.first != ret.second)
      {
     for(auto it = ret.first; it != ret.second; it++)
     {
     vector<string> transactionProds = supermarket.getTransactions()[it->second].getProducts();
        for(size_t j = 0; j < transactionProds.size(); j++)
        {
           int col = getProductIndex(transactionProds[j], productsMap);
           bottom10Matrix[i][col] = true;
        }
     }
      }
   }

   return bottom10Matrix;
}


/* verify if a customer bought at least the  same products + 1 as bottom10  */
bool isInterestingCustomers(vector<unsigned int> commonProducts, vector<bool> customerProducts, unsigned int nCommon, unsigned int bottom10Size)
{
  bool hasCommonProds = true;
  unsigned int nBoughtProds = 0;
  size_t i = 0;

  while(i < commonProducts.size() && hasCommonProds)
    {
      if(commonProducts[i] == bottom10Size && customerProducts[i] == false)
  hasCommonProds = false;
      else if(customerProducts[i] == true)
  nBoughtProds++;
      i++;
    }

  return (nBoughtProds > nCommon) && hasCommonProds;
}


/* get recommend products from the interesting customers.
returns a vector with their quantities */
vector<unsigned int> getInterestingProducts(vector<unsigned int> commonProducts, unsigned int nCommon, vector<vector<bool> > allCustomersMatrix, vector<Customer> bottom10)
{
  vector<unsigned int> interestingProds(commonProducts.size(), 0);

  for(size_t i = 0; i < allCustomersMatrix.size(); i++)
    {
      if(isInterestingCustomers(commonProducts, allCustomersMatrix[i], nCommon, bottom10.size()))
  {
    for(size_t j = 0; j < interestingProds.size(); j++)
      {
        if(allCustomersMatrix[i][j] == true)
    interestingProds[j]++;
      }
  }
    }
  return interestingProds;
}


/* main function of recommendation for bottom10 */
void makeRecommendationBottom10(Supermarket &supermarket)
{
   vector<Customer> bottom10 = supermarket.getBottom10();
   //unsigned int nCols = supermarket.getProducts().size();

   vector<vector<bool> > customersProductsMatrix = getBottom10Matrix(supermarket, bottom10);
   vector<unsigned int> commonProducts = getCommonProducts(customersProductsMatrix);
   vector<vector<bool> > allCustomersMatrix = getRecommendationMatrix(supermarket);

   //count number of commom products
   unsigned int nCommon = count(commonProducts.begin(), commonProducts.end(), bottom10.size());


   if(nCommon == 0)
     cout << endl << "Not enough commom products to recommended anything.. " << endl;
   else
     {
       vector<unsigned int> interestingProds = getInterestingProducts(commonProducts, nCommon, allCustomersMatrix, bottom10);

       unsigned int max = 0;
       unsigned int posMax = 0;

       for(size_t i = 0; i < interestingProds.size(); i++)
   {
     if(commonProducts[i] != bottom10.size())
       {
         unsigned int tmp = interestingProds[i] - commonProducts[i];
         if(tmp > max)
     {
       max = tmp;
       posMax = i;
     }
       }
   }


       if(max > 0)
   {
     cout << endl <<  "Recommendation for bottom10: " << endl;
     cout << " > " <<supermarket.getProducts()[posMax].getName() << endl << endl;
   }
       else
   {
     cout << "There isn't a possible recommendation.. " << endl << endl;
   }
     }
}
