#include "Product.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

// Based on user Interests
map<string, vector<string>> interestToCategory = {
    {"Cars", {"Cars"}},
    {"Crafts", {"Crafts"}},
    {"Beauty", {"Beauty/Wellness"}},
    {"Electronics", {"Electronics", "Video Games"}},
    {"Fashion", {"Men's Fashion", "Women's Fashion", "Children's Fashion"}},
    {"Health and Wellness", {"Health and Wellness"}},
    {"Home Decor and Care", {"Home Decor/Care"}},
    {"Home Improvement", {"Home Improvement"}},
    {"Industrial", {"Industrial"}},
    {"Pets", {"Pets"}},
    {"Sports and Outdoors", {"Sports/Outdoors"}},
    {"Travel", {"Travel"}},
};

map<string, vector<string>> AgeToCategory = {
    {"Baby", {"Baby/Maternity"}},
    {"Toddler", {"Baby/Maternity", "Kids' Toys"}},
    {"Child", {"Children's Fashion", "Kids' Toys"}},
    {"Teen/Young Adult", {"Adult Fashion"}},
    {"Adult", {"Adult Fashion"}},
    {"Senior", {"Adult Fashion"}},
};

map<string, vector<string>> RelationshipToCategory = {
    {"Friend", {"Women's Fashion", "Men's Fashion"}},
    {"Mother", {"Women's Fashion"}},
    {"Father", {"Men's Fashion"}},
    {"Sister", {"Women's Fashion"}},
    {"Brother", {"Men's Fashion"}},
    {"Son", {"Men's Fashion"}},
    {"Daughter", {"Women's Fashion"}},
    {"Significant Other", {"Women's Fashion", "Men's Fashion"}},
    {"Coworker", {"Women's Fashion", "Men's Fashion"}},
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
      (categoryID == 110 || categoryID == 111 || categoryID == 112 || categoryID == 113 || categoryID == 114)
  ) return "Men's Fashion";
  else if (
      (categoryID == 116 || categoryID == 118 || categoryID == 120 || categoryID == 121 || categoryID == 122 || categoryID == 123)
  ) return "Women's Fashion";
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
  ) return "Kids' Toys";
  else if (
      (categoryID >= 240 && categoryID <= 263)
  ) return "Video Games";

  return "Invalid Category";
}

vector<Product> readProductsFromFile(const string& fileName){
    vector<Product> products;
    ifstream file(fileName);
    if(!file.is_open())
        cout<<"File does not exist"<<endl;
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

        if(product.price <= 10) {
            product.priceRange = "Under $10";
        } else if  (product.price <= 25) {
            product.priceRange = "Under $25";
        } else if  (product.price <= 50) {
            product.priceRange = "Under $50";
        } else if  (product.price <= 100) {
            product.priceRange = "Under $100";
        } else if  (product.price <= 200) {
            product.priceRange = "Under $200";
        } else {
            product.priceRange = "Any Price";
        }

        try {
            product.interest = getCategoryName(stoi(product.categoryID));
        }  catch (...) {
            product.interest = "Unknown";
        }

        // placeholder for relationship
        product.relationship = "Friend";

        products.push_back(product);
    }
    return products;
};

//
string getInterestFromCategoryID(int categoryID) {
    // find the category name based on the category Id
    string categoryName = getCategoryName(categoryID);

    // find which intrest group it belongs to
    for (const auto& [interest, categories] : interestToCategory) {
        if (find(categories.begin(), categories.end(), categoryName) != categories.end()) {
            return interest;
        }
    }
}