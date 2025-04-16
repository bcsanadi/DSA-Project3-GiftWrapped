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
};

#endif //PRODUCT_H
