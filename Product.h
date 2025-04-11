#ifndef PRODUCT_H
#define PRODUCT_H

#endif //PRODUCT_H
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

};

vector<Product> readProductsFromFile(string& filename);

struct Category {
    int id;
    std::string category_name;
};
