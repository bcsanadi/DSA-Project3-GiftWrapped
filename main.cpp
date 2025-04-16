#include <iostream>
#include <sstream>
#include "ProductParsing.cpp"
#include "Product.h"
#include "Graph.cpp"
//#include <SFML/Graphics.hpp>


using namespace std;

int main() {
    cout << "Hello World!" << endl;

    string fileName = "amazon_split_aa";
    vector<Product> products = readProductsFromFile(fileName);

    Graph graph;

    return 0;
}
