#include "Product.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

// based on user interests
map<string, vector<string>> interestToCategory = {
    {"Cars", {"Cars"}},
    {"Crafts", {"Crafts"}},
    {"Beauty", {"Beauty/Wellness"}},
    {"Electronics", {"Electronics", "Video Games"}},
    {"Fashion", {"Men's Fashion", "Women's Fashion", "Children's Fashion"}},
    {"Health/Wellness", {"Health/Wellness"}},
    {"Home", {"Home", "Home Improvement"}},
    {"Industrial", {"Industrial"}},
    {"Pets", {"Pets"}},
    {"Sports/Outdoors", {"Sports/Outdoors"}},
    { "Toys/Games", {"Kids' Toys", "Video Games"}},
    {"Travel", {"Travel"}},
};

map<string, vector<string>> AgeToCategory = {
    {"Baby", {"Baby/Maternity"}},
    {"Toddler", {"Baby/Maternity", "Kids' Toys"}},
    {"Child", {"Children's Fashion", "Kids' Toys"}},
    {"Teen/Young Adult", {"Men's Fashion", "Women's Fashion", "Cars", "Crafts", "Beauty/Wellness", "Electronics", "Video Games", "Health/Wellness", "Home", "Industrial", "Pets", "Sports/Outdoors", "Travel"}},
    {"Adult", {"Men's Fashion", "Women's Fashion", "Cars", "Crafts", "Beauty/Wellness", "Electronics", "Video Games", "Health/Wellness", "Home", "Industrial", "Pets", "Sports/Outdoors", "Travel"}},
    {"Senior", {"Men's Fashion", "Women's Fashion", "Cars", "Crafts", "Beauty/Wellness", "Electronics", "Video Games", "Health/Wellness", "Home", "Industrial", "Pets", "Sports/Outdoors", "Travel"}},
};

map<string, vector<string>> RelationshipToCategory = {
    {"Friend", {"Women's Fashion", "Men's Fashion"}},
    {"Mother", {"Women's Fashion"}},
    {"Father", {"Men's Fashion"}},
    {"Sister", {"Women's Fashion"}},
    {"Brother", {"Men's Fashion"}},
    {"Son", {"Men's Fashion"}},
    {"Daughter", {"Women's Fashion"}},
    {"Significant Other", {"Women's Fashion", "Men's Fashion"}},
    {"Coworker", {"Women's Fashion", "Men's Fashion"}},
};

string getCategoryName(int categoryID) {
  if (
      (categoryID >= 1 && categoryID <= 13) || categoryID == 137 || categoryID == 177
  ) return "Crafts";
  else if (categoryID >= 14 && categoryID <= 28)
    return "Cars";
  else if (
      (categoryID >= 29 && categoryID <= 44) || categoryID == 264 || categoryID == 129
  ) return "Baby/Maternity";
  else if (
      (categoryID >= 45 && categoryID <= 53)
  ) return "Beauty/Wellness";
  else if (categoryID >= 54 && categoryID <= 83)
    return "Electronics";
  else if (
      (categoryID >= 84 && categoryID <= 98) || categoryID == 265
  ) return "Children's Fashion";
  else if (categoryID >= 99 && categoryID <= 109)
    return "Travel";
  else if (
      (categoryID == 110 || categoryID == 111 || categoryID == 112 || categoryID == 113 || categoryID == 114)
  ) return "Men's Fashion";
  else if (
      (categoryID == 116 || categoryID == 118 || categoryID == 120 || categoryID == 121 || categoryID == 122 || categoryID == 123)
  ) return "Women's Fashion";
  else if (categoryID >= 138 && categoryID <= 162)
    return "Industrial";
  else if (
      categoryID == 124 || (categoryID >= 163 && categoryID <= 176) || (categoryID >= 185 && categoryID <= 197)
  ) return "Home";
  else if (
      (categoryID >= 201 && categoryID <= 215)
  ) return "Home Improvement";
  else if (
      (categoryID >= 178 && categoryID <= 184)
  ) return "Pets";
  else if (
      categoryID == 198 || categoryID == 199 || categoryID == 200 || categoryID == 132 || categoryID == 136
  ) return "Sports/Outdoors";
  else if (
      (categoryID >= 126 && categoryID <= 131) || categoryID == 133 || categoryID == 134 || categoryID == 135
  ) return "Health/Wellness";
  else if (
      categoryID == 217 || categoryID == 218 || (categoryID >= 220 && categoryID <= 240) || categoryID == 266
  ) return "Kids' Toys";
  else if (
      (categoryID >= 240 && categoryID <= 263)
  ) return "Video Games";

  return "Invalid Category";
}

void Product::readProductsFromFile(const std::string& filename, std::vector<Product>& output) {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            vector<string> fields;
            string field;
            bool inQuotes = false;

            for (size_t i = 0; i < line.size(); i++) {
                char c = line[i];

                if (c == '"')
                    inQuotes = !inQuotes;
                else if (c == ',' && !inQuotes) {
                    fields.push_back(field);
                    field.clear();
                }
                else
                    field += c;
            }
            fields.push_back(field);

            if (fields.size() != 6) {
                continue;
            }

            try {
                double price = std::stod(fields[4]);
                Product product(fields[0], fields[1], fields[2], fields[3], price, fields[5]);
                output.push_back(product);
            } catch (exception& e) {
            }
        }
    }


string getInterestFromCategoryID(int categoryID) {
    // find the category name based on the category Id
    string categoryName = getCategoryName(categoryID);

    // find which interest group it belongs to
    for (const auto& [interest, categories] : interestToCategory) {
        if (find(categories.begin(), categories.end(), categoryName) != categories.end())
            return interest;
    }
}

// filter the graph based on user inputted price range, interests, age, and relationships
vector<Product> Product::filterProducts(const vector<Product>& products, const string& interest, const string& price, const string& age, const string& relationship) {
    vector<Product> filtered;

    vector<string> interestCategories;
    if (interestToCategory.find(interest) != interestToCategory.end())
        interestCategories = interestToCategory[interest];

    vector<string> ageCategories;
    if (AgeToCategory.find(age) != AgeToCategory.end())
        ageCategories = AgeToCategory[age];

    string catName;
    for (const auto& p : products) {
        try {
            catName = getCategoryName(stoi(p.categoryID));
        } catch (exception& e) {
            continue;
        }

        bool matchesInterest = (find(interestCategories.begin(), interestCategories.end(), catName) != interestCategories.end());
        bool matchesAge = (find(ageCategories.begin(), ageCategories.end(), catName) != ageCategories.end());
        bool matchesPrice = false;
        if (price == "Under $10" && p.price < 10) {
            matchesPrice = true;
        } else if (price == "Under $25" && p.price < 25) {
            matchesPrice = true;
        } else if (price == "Under $50" && p.price < 50) {
            matchesPrice = true;
        } else if (price == "Under $100" && p.price < 100) {
            matchesPrice = true;
        } else if (price == "Under $200" && p.price < 200) {
            matchesPrice = true;
        } else if (price == "Any Price") {
            matchesPrice = true;
        }


        if (interest == "Fashion") {
            vector<string> validCategories = RelationshipToCategory[relationship];
            bool matchesRelationship = (find(validCategories.begin(), validCategories.end(), catName) != validCategories.end());
            if (matchesRelationship && matchesPrice) {
                filtered.push_back(p);
            }
        }

        else if (matchesInterest && matchesAge && matchesPrice) {
            filtered.push_back(p);
        }
    }
    return filtered;
}
