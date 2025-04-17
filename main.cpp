#include <SFML/Graphics.hpp>
#include <sstream>
#include "Product.h"
#include <iostream>

using namespace std;

sf::Sprite ReadInSprite(sf::Texture& texture, const std::filesystem::path& filename, int x, int y) {
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename.string());
    }
    sf::Sprite sprite(texture);
    sprite.setPosition(sf::Vector2f(x, y));
    return sprite;
}


int main() {
    vector<string> fileNames = {
        "amazon_split_aa",
        "amazon_split_ab",
        "amazon_split_ac",
        "amazon_split_ad"
    };
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Gift Wrapped");
    window.setFramerateLimit(60);

   // sf::RenderWindow generatedWindow(sf::VideoMode({1000, 800}), "Gift Wrapped");
   // generatedWindow.setFramerateLimit(60);

sf::Font font;
if (!font.openFromFile("../MagazineBold-3zolZ.ttf")) {
    cout << "Error loading Magazine.ttf" << endl;
}
    sf::Texture giftTexture;
    sf::Sprite giftIcon = ReadInSprite(giftTexture, "../Gifty.png", 410, 90);
    giftIcon.setScale(sf::Vector2f(0.09f, 0.09f));

    sf::Text title(font);
    title.setCharacterSize(60);
    title.setString("Gift Wrapped");
    sf::FloatRect bounds = title.getLocalBounds();
    title.setOrigin({bounds.position.x + bounds.size.x/2.0f, bounds.position.y + bounds.size.x});
    title.setStyle(sf::Text::Bold);
    title.setPosition({500, 400});
    title.setFillColor(sf::Color::White);


    vector<Product> products;

    // for (const auto& fileName : fileNames) {
    //     vector<Product> partial = readProductsFromFile(fileName);
    //     products.insert(products.end(), partial.begin(), partial.end());
    // }



    while (window.isOpen()){
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        sf::Color pink = sf::Color(255, 197, 211);
        window.clear(pink);

        window.draw(title);
        window.draw(giftIcon);
        window.display();
    }
    return 0;
}