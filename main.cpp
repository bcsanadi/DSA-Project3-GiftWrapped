#include <SFML/Graphics.hpp>
#include <sstream>
#include "ProductParsing.cpp"
#include "Product.h"
#include <iostream>

using namespace std;

int main() {
    vector<string> fileNames = {
        "amazon_split_aa",
        "amazon_split_ab",
        "amazon_split_ac",
        "amazon_split_ad"
    };

    vector<Product> products;

    // for (const auto& fileName : fileNames) {
    //     vector<Product> partial = readProductsFromFile(fileName);
    //     products.insert(products.end(), partial.begin(), partial.end());
    // }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Product Graph");
    window.setFramerateLimit(60);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw your graph or sprites here

        window.display();
    }
    return 0;
}
