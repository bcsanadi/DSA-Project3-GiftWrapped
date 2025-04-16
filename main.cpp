#include <sstream>
#include "ProductParsing.cpp"
#include "Product.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

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

    RenderWindow window(VideoMode(800, 600), "Product Graph");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        // Draw your graph or sprites here

        window.display();
    }
    return 0;
}
