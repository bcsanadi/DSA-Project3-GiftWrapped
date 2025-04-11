//
// Created by Olivia Farino on 4/10/25.
//
#include "product.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<Product> readProductsFromFile(string& fileName){
  vector<Product> products;
  ifstream file(fileName);
  if(!file.is_open()){
    cout<<"File does not exist"<<endl;
  }
  string line;
  getline(file,line);

while(getline(file,line)){
  istringstream ss(line);
  string tokenPrice;
  string tokenListPrice;
  Product product;
  getline(ss, product.asin, ',');
  getline(ss, product.title, ',');
  getline(ss, product.imgurl, ',');
  getline(ss, product.productURL, ',');
  getline(ss, product.stars, ',');
  getline(ss, product.reviews, ',');
  getline(ss, tokenPrice, ',');
  try{
    product.price = stod(tokenPrice);
  }
  catch(exception& e){}
  getline(ss, tokenListPrice, ',');
  try{
    product.listPrice = stod(tokenListPrice);
  }
  catch(exception& e){}
  getline(ss, product.categoryID, ',');
  getline(ss, product.isBestSeller, ',');
  getline(ss, product.boughtInLastMonth, ',');
  products.push_back(product);
}
return products;

};