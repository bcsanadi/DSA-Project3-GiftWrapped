#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <optional>
#include "Product.h"
#include "Graph.h"

using namespace std;
using namespace sf;

// loads texture from file and sets position
Sprite ReadInSprite(Texture& texture, const filesystem::path& filename, int x, int y) {
    if (!texture.loadFromFile(filename))
        throw runtime_error("Failed to load texture: " + filename.string());
    Sprite sprite(texture);
    sprite.setPosition(Vector2f(x, y));
    return sprite;
}

// button UI
struct Button {
    RectangleShape buttonBox;
    Text label;
    bool selected = false;

    // constructor initializes button box and label
    Button(const string& text, const Font& font, const Vector2f size, Vector2f position, Color color, Vector2f labelPosition) : label(font){
        buttonBox.setSize(size);
        buttonBox.setPosition(position);
        buttonBox.setFillColor(color);
        buttonBox.setOutlineColor(Color::Black);
        buttonBox.setOutlineThickness(3);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(15);
        label.setFillColor(Color::Black);
        FloatRect textBounds = label.getGlobalBounds();
        label.setPosition(labelPosition);
    }

    // renders button and label
    void draw(RenderWindow& window) {
        window.draw(buttonBox);
        window.draw(label);
    }

    // checks if button contains given point
    bool contains(Vector2f point) const {
        return buttonBox.getGlobalBounds().contains(point);
    }

    // updates visual appearance based on selection state
    void setSelected(bool state) {
        selected = state;
        Color lightBlue = Color(180, 225, 255);
        if (selected)
            buttonBox.setFillColor(lightBlue);
        else
            buttonBox.setFillColor(Color::White);
    }
};

// represents category containing list of selectable buttons
struct Category {
    string name;
    vector<Button> buttons;
    int selectedIndex = -1;
    Font font;
    Text title;

    // constructor to build title and dynamically place buttons
    Category(const string& name, const vector<string>& values, const Font& font, Vector2f position) : name(name) , title(font) {
        title.setFont(font);
        title.setString(name);
        title.setCharacterSize(24);
        title.setPosition(position);
        Color purple = Color(119, 0, 200);
        title.setFillColor(purple);

        Vector2f buttonSize = {189, 30};
        float spacing = 10;

        for(size_t i = 0; i < values.size(); i++) {
            Vector2f buttonPos = {position.x, position.y + 40 + i * (buttonSize.y + spacing)};
            Vector2f labelPos = {position.x + 5, position.y + 45 + i * (buttonSize.y + spacing)};
            buttons.emplace_back(values[i], font, buttonSize, buttonPos, Color::White, labelPos);
        }
    }

    // renders title and buttons
    void draw(RenderWindow& window) {
        window.draw(title);
        for (auto& button : buttons)
            button.draw(window);
    }

    // handles mouse clicks to select a button within a category
    void handleClick(Vector2f mousePos) {
        for (int i = 0; i < buttons.size(); i++) {
            if (buttons[i].contains(mousePos)) {
                if (selectedIndex != -1)
                    buttons[selectedIndex].setSelected(false);
                selectedIndex = i;
                buttons[i].setSelected(true);
            }
        }
    }

    // returns selected button's label
     string getSelectedValue() const {
        if (selectedIndex != -1)
            return buttons[selectedIndex].label.getString();
        return "";
    }
};

// checks if every category has a selected value
bool allFourOptionsChosen(const vector<Category>& categories) {
    for (const auto& category : categories) {
        if (category.getSelectedValue().empty())
            return false;
    }
    return true;
}

int main() {

    Graph graph;
    Product product;

    // loads product data from CSV files
    vector<string> fileNames = {
        "../amazon_split_aa_new.csv",
        "../amazon_split_ab_new.csv",
        "../amazon_split_ac_new.csv",
        "../amazon_split_ad_new.csv",
    };

    vector<Product> allProducts;
    for (const auto& fileName : fileNames)
        product.readProductsFromFile(fileName, allProducts);
    cout << allProducts.size() << endl;

    // creates main selection window
    RenderWindow window(VideoMode({1000, 800}), "Gift Wrapped");
    window.setFramerateLimit(60);
    RenderWindow Results;

    // title setup
    Font titleFont;
    if (!titleFont.openFromFile("../Title2.ttf"))
        cout << "Error loading Title2.ttf" << endl;

    // loads and sets gift icon
    Texture giftTexture;
    :Sprite giftIcon = ReadInSprite(giftTexture, "../Gifty.png", 410, 80);
    giftIcon.setScale(Vector2f(0.09f, 0.09f));

    // title text
    Text title(titleFont);
    title.setCharacterSize(75);
    title.setString("Gift Wrapped");
    FloatRect bounds = title.getLocalBounds();
    title.setOrigin({bounds.position.x + bounds.size.x/2.0f, bounds.position.y + bounds.size.x});
    title.setStyle(Text::Bold);
    title.setPosition({500, 430});
    title.setFillColor(Color::White);

    // subtitle text
    Font font;
    if (!font.openFromFile("../Options.ttf"))
        cout << "Error loading Options.ttf" << endl;

    Text chooseText(font);
    chooseText.setCharacterSize(25);
    chooseText.setString("Choose one option from each category!");
    FloatRect chooseBounds = chooseText.getLocalBounds();
    chooseText.setOrigin({chooseBounds.position.x + chooseBounds.size.x/2.0f, chooseBounds.position.y + chooseBounds.size.x});
    chooseText.setStyle(Text::Bold);
    chooseText.setPosition({500, 775});
    chooseText.setFillColor(Color::Black);

    // creates categories and options
    vector<Category> categories;

    vector<string> interests = {"Cars", "Crafts", "Beauty", "Electronics","Fashion", "Health/Wellness", "Home", "Industrial","Pets", "Sports/Outdoors", "Toys/Games", "Travel"};
    categories.emplace_back("Interest", interests, font, Vector2f(100, 275));

    vector<string> prices = {"Under $10", "Under $25", "Under $50", "Under $100", "Under $200", "Any Price"};
    categories.emplace_back("Price Range", prices, font, Vector2f(300, 275));

    vector<string> ages = {"Baby", "Toddler", "Child", "Teen/Young Adult", "Adult", "Senior"};
    categories.emplace_back("Age Group", ages, font, Vector2f(500, 275));

    vector<string> relations = {"Friend", "Mother", "Father", "Sister", "Brother", "Daughter", "Son",
        "Significant Other", "Coworker"};
    categories.emplace_back("Relationship", relations, font, Vector2f(700, 275));

    // creates generate button
    Color pink = Color(255, 197, 211);
    Color purple = Color(219, 165, 255);
    Button generateButton("Generate \n Results!", font, {180, 60}, {440, 670}, purple, {490, 682});

    // main event loop for selection window
    while (window.isOpen()){
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();

            // handles mouse click
            if (event->is<Event::MouseButtonPressed>()) {
            const Event::MouseButtonPressed* mouseEvent = event->getIf<Event::MouseButtonPressed>();
                if (mouseEvent) {
                    if (mouseEvent->button == Mouse::Button::Left) {
                        Vector2f mousePos = window.mapPixelToCoords(mouseEvent->position);

                        // checks category button clicks
                        for (auto& category : categories)
                            category.handleClick(mousePos);

                        // handles generate button
                        if (generateButton.contains(mousePos)) {
                            if (allFourOptionsChosen(categories)) {
                                window.close();
                                Results.create(VideoMode({1000, 800}), "Gift Wrapped");

                                // retrieves selections
                                string selectedInterest = categories[0].getSelectedValue();
                                string selectedPrice = categories[1].getSelectedValue();
                                string selectedAge = categories[2].getSelectedValue();
                                string selectedRelation = categories[3].getSelectedValue();

                                vector<string> categoryIDs;

                                // filters products based on selected criteria
                                vector<Product> filtered = Product::filterProducts(allProducts, selectedInterest, selectedPrice, selectedAge, selectedRelation);

                                // traverses graph to get related product titles
                                vector<string> filteredASINs;
                                for (const auto& p : filtered)
                                    filteredASINs.push_back(p.asin);

                                vector<Product> relatedTitles = graph.traverse(filteredASINs);
                                for (const Product& p : relatedTitles)
                                    cout << p.title << endl;

                                // setup product text display
                                vector<Text> productTexts;
                                int maxProductsToShow = 200;
                                float yStart = 250;
                                for (int i = 0; i < min((int)filtered.size(), maxProductsToShow); ++i) {
                                    Text productText(font);
                                    productText.setString(filtered[i].title);
                                    productText.setCharacterSize(15);
                                    productText.setFillColor(Color::Black);
                                    productText.setPosition({50.f, yStart + static_cast<float>(i) * 40.f});
                                    productTexts.push_back(productText);
                                }

                                // setup scroll control values
                                float scrollOffset = 0.f;
                                float xOffset = 0.f;
                                const float scrollStep = 40.f;
                                const float maxScroll = static_cast<float>(max(0, (int)filtered.size() - maxProductsToShow)) * scrollStep;
                                const float xScrollStep = 40.f;

                                // displays results window
                                while (Results.isOpen()) {
                                    while (const optional event = Results.pollEvent()) {
                                        if (event->is<Event::Closed>())
                                            Results.close();

                                        // handles mouse wheel scrolling
                                        if (event->is<Event::MouseWheelScrolled>()) {
                                            auto scroll = event->getIf<Event::MouseWheelScrolled>();
                                            if (scroll) {
                                                float delta = scroll->delta;
                                                scrollOffset -= delta * scrollStep;

                                                // vertical scroll
                                                if (scroll->wheel == Mouse::Wheel::Vertical)
                                                    scrollOffset -= delta * scrollStep;
                                                if (scrollOffset < 0.f) scrollOffset = 0.f;
                                                if (scrollOffset > maxScroll) scrollOffset = maxScroll;

                                                // horizontal scroll
                                                else if (scroll->wheel == Mouse::Wheel::Horizontal)
                                                    xOffset -= delta * xScrollStep;
                                                if (xOffset < 0.f) xOffset = 0.f;
                                            }
                                        }
                                    }

                                    // clears results window
                                    Results.clear(pink);

                                    // draws title and gift icon
                                    Results.draw(title);
                                    Results.draw(giftIcon);

                                    // loops through filtered products and draw with adjusted scroll positions
                                    for (size_t i = 0; i < productTexts.size(); ++i) {
                                        Text text = productTexts[i];

                                        // gets original position and applies scroll offsets
                                        Vector2f pos = text.getPosition();
                                        pos.y = 250 + static_cast<float>(i) * 40.f - scrollOffset;
                                        pos.x -= xOffset;
                                        text.setPosition(pos);

                                        // draws text if it is within the visible screen area
                                        if (pos.y > 200 && pos.y < 800)
                                            Results.draw(text);
                                    }

                                    // displays final frame
                                    Results.display();
                                }
                            }
                        }
                    }
                }
            }
        }

        // clears screen
        window.clear(pink);

        // draws UI elements
        window.draw(title);
        window.draw(giftIcon);
        window.draw(chooseText);
        generateButton.draw(window);

        // draws category buttons
        for (auto& category : categories)
            category.draw(window);

        // displays everything
        window.display();
    }

    return 0;
}
