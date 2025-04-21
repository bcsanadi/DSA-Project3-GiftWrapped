#include "Graph.h"

// adds product as a node if it does not already exist
void Graph::addNode(const Product& product) {
    if (graph.find(product.asin) == graph.end())
        graph[product.asin] = Node{product};
}

// creates directed edge between two product nodes with a given weight
void Graph::addEdge(const string& from, const string& to, int weight) {
    if (graph.find(from) != graph.end() && graph.find(to) != graph.end()) {

        // checks if edge already exists to avoid duplicates
        for (const auto& neighbor : graph[from].relatedProducts) {
            if (neighbor.first == &graph[to])
                return;
        }

        // adds edge from "from" node to "to" node
        graph[from].relatedProducts.emplace_back(&graph[to], weight);
    }
}

// traverses graph starting from list of ASINs and return related products
vector<Product> Graph::traverse(const vector<string>& userInput) {
    vector<Product> result;
    unordered_set<string> visited;

    for (const string& asin : userInput) {
        if (graph.find(asin) != graph.end()) {
            for (const auto& neighbor : graph[asin].relatedProducts) {
                Node* node = neighbor.first;

                // adds to result if product not already visited
                if (visited.find(node->product.asin) == visited.end()) {
                    result.push_back(node->product);
                    visited.insert(node->product.asin);
                }
            }
        }
    }
    return result;
}

// builds graph by adding nodes and connecting related products based on user inputs
void Graph::buildGraph(const vector<Product>& products, Graph& graph, const string& price, const string& age, const string& relationship) {

    // adds all products as nodes
    for (const auto& p : products)
        graph.addNode(p);

    // connects products based on shared attributes
    for (int i = 0; i < products.size(); i++) {
        for (int j = 0; j < products.size(); j++) {
            int weight = 0;

            // increases weight for shared interest
            if (products[i].interest == products[j].interest)
                weight++;

            // increases weight if both products share the same age group and match user's selected age
            if (products[i].ageGroup == products[j].ageGroup && products[i].ageGroup == age)
                weight++;

            // increases weight if both products share the same relationship and match user's selected relationship
            if (products[i].relationship == products[j].relationship && products[i].relationship == relationship)
                weight++;

            // adds bidirectional edges if weight is positive
            if (weight > 0) {
                graph.addEdge(products[i].asin, products[j].asin, weight);
                graph.addEdge(products[j].asin, products[i].asin, weight);
            }
        }
    }
}
