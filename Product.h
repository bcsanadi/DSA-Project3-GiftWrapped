#ifndef PRODUCT_H
#define PRODUCT_H
#pragma once
#include <string>
#include <vector>

using namespace std;

struct Product {
    string asin;
    string title;
    string imgurl;
    string productURL;
    string stars;
    string reviews;
    double price;
    double listPrice;
    string categoryID;
    string isBestSeller;
    string boughtInLastMonth;

    // fields based on user interface
    string priceRange;
    string ageGroup;
    string interest;
    string relationship;

     vector<Product> filterProducts(const vector<Product>& products, const string& interest, const string& price, const string& age, const string& relationship);
     vector<Product> readProductsFromFile(const string& fileName);
};

#endif //PRODUCT_H
