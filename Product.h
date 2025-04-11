//
// Created by Olivia Farino on 4/10/25.
//

#ifndef PRODUCT_H
#define PRODUCT_H

#endif //PRODUCT_H
#include <string>
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

};

vector<Product> readProductsFromFile(string& filename);