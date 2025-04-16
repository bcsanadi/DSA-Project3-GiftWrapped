#include <iostream>
#include <sstream>
#include "ProductParsing.cpp"
#include "Product.h"
#include "Graph.cpp"
//#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    vector<string> fileNames = {
        "amazon_split_aa",
        "amazon_split_ab",
        "amazon_split_ac",
        "amazon_split_ad"
    };

    vector<Product> products;

    for (const auto& fileName : fileNames) {
        vector<Product> partial = readProductsFromFile(fileName);
        products.insert(products.end(), partial.begin(), partial.end());
    }
}
