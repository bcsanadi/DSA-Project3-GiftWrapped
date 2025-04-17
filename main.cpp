#include <SFML/Graphics.hpp>
#include <sstream>
#include "Product.h"
#include <iostream>
#include <optional>

using namespace std;

struct Button {
    sf::RectangleShape buttonBox;
    sf::Text label;
    bool selected = false;

    Button(const string& text, const sf::Font& font, const sf::Vector2f size, sf::Vector2f position) : label(font){
        buttonBox.setSize(size);
        buttonBox.setPosition(position);
        buttonBox.setFillColor(sf::Color::White);
        buttonBox.setOutlineColor(sf::Color::Black);
        buttonBox.setOutlineThickness(3);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(15);
        label.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = label.getGlobalBounds();
        label.setPosition(position + size / 2.f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(buttonBox);
        window.draw(label);
    }

    bool contains(sf::Vector2f point) const {
        return buttonBox.getGlobalBounds().contains(point);
    }

    void setSelected(bool state) {
        selected = state;
        if (selected) {
            buttonBox.setFillColor(sf::Color::Black);
        } else {
            buttonBox.setFillColor(sf::Color::White);
        }
    }
};

struct Category {
    string name;
    vector<Button> buttons;
    int selectedIndex = -1;
    sf::Font font;
    sf::Text title;

    Category(const string& name, const vector<string>& values, const sf::Font& font, sf::Vector2f position) : name(name) , title(font) {
        title.setFont(font);
        title.setString(name);
        title.setCharacterSize(24);
        title.setPosition(position);

        sf::Vector2f buttonSize = {150, 30};
        float spacing = 10;

        for(size_t i = 0; i < values.size(); i++) {
            sf::Vector2f buttonPos = {position.x, position.y + 40 + i * (buttonSize.y + spacing)};
            buttons.emplace_back(values[i], font, buttonSize, buttonPos);
        }
    }
    void draw(sf::RenderWindow& window) {
        window.draw(title);
        for (auto& button : buttons) {
            button.draw(window);
        }
    }

    void handleClick(sf::Vector2f mousePos) {
        for (int i = 0; i < buttons.size(); i++) {
            if (buttons[i].contains(mousePos)) {
                if (selectedIndex != -1)
                    buttons[selectedIndex].setSelected(false);
                selectedIndex = i;
                buttons[i].setSelected(true);
            }
        }
    }
     string getSelectedValue() const {
        if (selectedIndex != -1) {
            return buttons[selectedIndex].label.getString();
        }
        return "";
    }
};

int main() {
    vector<string> fileNames = {
        "amazon_split_aa",
        "amazon_split_ab",
        "amazon_split_ac",
        "amazon_split_ad"
    };
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Gift Wrapped");
    window.setFramerateLimit(60);

sf::Font font;
if (!font.openFromFile("../MagazineBold-3zolZ.ttf")) {
    cout << "Error loading Magazine.ttf" << endl;
}

    sf::Text title(font);
    title.setCharacterSize(50);
    title.setString("Gift Wrapped");
    sf::FloatRect bounds = title.getLocalBounds();
    title.setOrigin({bounds.position.x + bounds.size.x/2.0f, bounds.position.y + bounds.size.x});
    title.setStyle(sf::Text::Bold);
    title.setPosition({500, 400});
    title.setFillColor(sf::Color::White);



    //Placeholder text
    vector<Category> categories;
    vector<string> interests = {"Books", "Tech", "Fashion"};
    categories.emplace_back("Interest", interests, font, sf::Vector2f(100, 150));
    vector<string> prices = {"$0-25", "$25-50", "$50-100"};
    categories.emplace_back("Price Range", prices, font, sf::Vector2f(300, 150));
    vector<string> ages = {"Kids", "Teens", "Adults"};
    categories.emplace_back("Age Group", ages, font, sf::Vector2f(500, 150));
    vector<string> relations = {"Family", "Friend", "Partner"};
    categories.emplace_back("Relationship", relations, font, sf::Vector2f(700, 150));
    //vector<Product> products;

    // for (const auto& fileName : fileNames) {
    //     vector<Product> partial = readProductsFromFile(fileName);
    //     products.insert(products.end(), partial.begin(), partial.end());
    // }



    while (window.isOpen()){
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
            const sf::Event::MouseButtonPressed* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent) {
                    if (mouseEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mouseEvent->position);
                        for (auto& category : categories) {
                            category.handleClick(mousePos);
                        }
                    }
                }
            }
        }

        sf::Color pink = sf::Color(255, 197, 211);
        window.clear(pink);

        // Draw your graph or sprites here
        window.draw(title);
        for (auto& category : categories) {
            category.draw(window);
        }
        window.display();
    }
    return 0;
}