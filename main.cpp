#include <SFML/Graphics.hpp>
#include <sstream>
#include "Product.h"
#include <iostream>
#include <optional>

using namespace std;

sf::Sprite ReadInSprite(sf::Texture& texture, const std::filesystem::path& filename, int x, int y) {
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename.string());
    }
    sf::Sprite sprite(texture);
    sprite.setPosition(sf::Vector2f(x, y));
    return sprite;
}

struct Button {
    sf::RectangleShape buttonBox;
    sf::Text label;
    bool selected = false;

    Button(const string& text, const sf::Font& font, const sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Vector2f labelPosition) : label(font){
        buttonBox.setSize(size);
        buttonBox.setPosition(position);
        buttonBox.setFillColor(color);
        buttonBox.setOutlineColor(sf::Color::Black);
        buttonBox.setOutlineThickness(3);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(15);
        label.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = label.getGlobalBounds();
        label.setPosition(labelPosition);
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
        sf::Color lightBlue = sf::Color(180, 225, 255);
        if (selected) {
            buttonBox.setFillColor(lightBlue);
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
        sf::Color purple = sf::Color(119, 0, 200);
        title.setFillColor(purple);


        sf::Vector2f buttonSize = {189, 30};
        float spacing = 10;

        for(size_t i = 0; i < values.size(); i++) {
            sf::Vector2f buttonPos = {position.x, position.y + 40 + i * (buttonSize.y + spacing)};
            sf::Vector2f labelPos = {position.x + 5, position.y + 45 + i * (buttonSize.y + spacing)};
            buttons.emplace_back(values[i], font, buttonSize, buttonPos, sf::Color::White, labelPos);
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

bool allFourOptionsChosen(const vector<Category>& categories) {
    for (const auto& category : categories) {
        if (category.getSelectedValue().empty()) {
            return false;
        }
    }
    return true;
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
    sf::RenderWindow Results;

    sf::Font titleFont;
    if (!titleFont.openFromFile("../Title2.ttf")) {
        cout << "Error loading Title2.ttf" << endl;
    }
    sf::Texture giftTexture;
    sf::Sprite giftIcon = ReadInSprite(giftTexture, "../Gifty.png", 410, 80);
    giftIcon.setScale(sf::Vector2f(0.09f, 0.09f));

    sf::Text title(titleFont);
    title.setCharacterSize(75);
    title.setString("Gift Wrapped");
    sf::FloatRect bounds = title.getLocalBounds();
    title.setOrigin({bounds.position.x + bounds.size.x/2.0f, bounds.position.y + bounds.size.x});
    title.setStyle(sf::Text::Bold);
    title.setPosition({500, 430});
    title.setFillColor(sf::Color::White);

    sf::Font font;
    if (!font.openFromFile("../Options.ttf")) {
        cout << "Error loading Options.ttf" << endl;
    }
    sf::Text chooseText(font);
    chooseText.setCharacterSize(25);
    chooseText.setString("Choose one option from each category!");
    sf::FloatRect chooseBounds = chooseText.getLocalBounds();
    chooseText.setOrigin({chooseBounds.position.x + chooseBounds.size.x/2.0f, chooseBounds.position.y + chooseBounds.size.x});
    chooseText.setStyle(sf::Text::Bold);
    chooseText.setPosition({500, 775});
    chooseText.setFillColor(sf::Color::Black);


    //Placeholder text
    vector<Category> categories;

    vector<string> interests = {"Cars", "Crafts", "Beauty", "Electronics","Fashion", "Health & Wellness", "Home Decor/Care", "Home Improvement", "Industrial","Pets", "Sports/Outdoors", "Travel"};
    categories.emplace_back("Interest", interests, font, sf::Vector2f(100, 275));

    vector<string> prices = {"Under $10", "Under $25", "Under $50", "Under $100", "Under $200", "Any Price"};
    categories.emplace_back("Price Range", prices, font, sf::Vector2f(300, 275));

    vector<string> ages = {"Baby", "Toddler", "Child", "Teen/Young Adult", "Adult", "Senior"};
    categories.emplace_back("Age Group", ages, font, sf::Vector2f(500, 275));

    vector<string> relations = {"Friend", "Sibling", "Mother", "Father", "Sister", "Son", "Daughter",
        "Significant Other", "Coworker"};

    categories.emplace_back("Relationship", relations, font, sf::Vector2f(700, 275));
    //vector<Product> products;

    // for (const auto& fileName : fileNames) {
    //     vector<Product> partial = readProductsFromFile(fileName);
    //     products.insert(products.end(), partial.begin(), partial.end());
    // }

    sf::Color pink = sf::Color(255, 197, 211);
    sf::Color purple = sf::Color(219, 165, 255);


    Button generateButton("Generate \n Results!", font, {180, 60}, {440, 670}, purple, {490, 682});
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

                        if (generateButton.contains(mousePos)) {
                            if (allFourOptionsChosen(categories)) {
                                cout << "Generate button clicked!" << endl;
                                window.close();
                                Results.create(sf::VideoMode({1000, 800}), "Gift Wrapped");

                                while (Results.isOpen()) {
                                    while (const optional event = Results.pollEvent()) {
                                        if (event->is<sf::Event::Closed>()) {
                                            Results.close();
                                        }
                                    }
                                    Results.clear(pink);
                                    Results.draw(title);
                                    Results.draw(giftIcon);
                                    Results.display();
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear(pink);


        window.draw(title);
        window.draw(giftIcon);
        window.draw(chooseText);
        generateButton.draw(window);
        for (auto& category : categories) {
            category.draw(window);
        }
        window.display();
    }
    return 0;
}