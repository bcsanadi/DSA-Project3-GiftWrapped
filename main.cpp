#include <SFML/Graphics.hpp>
#include <sstream>
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

    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Gift Wrapped");
    window.setFramerateLimit(60);

    while (window.isOpen()){
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        sf::Color pink = sf::Color(255, 197, 211);
        window.clear(pink);

        // Draw your graph or sprites here

        window.display();
    }
    return 0;
}