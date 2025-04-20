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
    double price;
    string categoryID;


    // fields based on user interface
    string priceRange;
    string ageGroup;
    string interest;
    string relationship;

     static vector<Product> filterProducts(const vector<Product>& products, const string& interest, const string& price, const string& age, const string& relationship);
     void readProductsFromFile(const std::string& filename, std::vector<Product>& output);
    Product(string asin, string title, string imgurl, string productURL, double price, string categoryID)
    : asin(asin), title(title), imgurl(imgurl), productURL(productURL) ,categoryID(categoryID), price(price) {}
    Product() = default;
};

#endif //PRODUCT_H
