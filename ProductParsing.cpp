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

string getCategoryName(int categoryID) {
  if (
      (categoryID >= 1 && categoryID <= 13) || categoryID == 137 || categoryID == 177
  ) return "Crafts";
  else if (categoryID >= 14 && categoryID <= 28)
    return "Cars";
  else if (
      (categoryID >= 29 && categoryID <= 44) || categoryID == 264 || categoryID == 129
  ) return "Baby/Maternity";
  else if (
      (categoryID >= 45 && categoryID <= 53) || (categoryID >= 126 && categoryID <= 136)
  ) return "Beauty/Wellness";
  else if (categoryID >= 54 && categoryID <= 83)
    return "Electronics";
  else if (
      (categoryID >= 84 && categoryID <= 98) || categoryID == 265
  ) return "Children's Fashion";
  else if (categoryID >= 99 && categoryID <= 109)
    return "Travel";
  else if (
      (categoryID >= 110 && categoryID <= 123)
  ) return "Adult Fashion";
  else if (categoryID >= 138 && categoryID <= 162)
    return "Industrial";
  else if (
      categoryID == 124 || (categoryID >= 163 && categoryID <= 176) || (categoryID >= 185 && categoryID <= 197)
  ) return "Home Decor/Care";
  else if (
      (categoryID >= 201 && categoryID <= 215)
  ) return "Home Improvement";
  else if (
      (categoryID >= 178 && categoryID <= 184)
  ) return "Pets";
  else if (
      categoryID == 198 || categoryID == 199 || categoryID == 200 || categoryID == 132 || categoryID == 136
  ) return "Sports/Outdoors";
  else if (
      (categoryID >= 126 && categoryID <= 131) || categoryID == 133 || categoryID == 134 || categoryID == 135
  ) return "Health and Wellness";
  else if (
      categoryID == 217 || categoryID == 218 || (categoryID >= 220 && categoryID <= 240) || categoryID == 266
  ) return "Kids Toys";
  else if (
      (categoryID >= 240 && categoryID <= 263)
  ) return "Video Games";

  return "Invalid Category";
}
