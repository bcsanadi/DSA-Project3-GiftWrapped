#include "Graph.h"

void Graph::addNode(const Product& product) {
    if (graph.find(product.asin) == graph.end())
        graph[product.asin] = Node{product};
}

void Graph::addEdge(const string& from, const string& to, int weight) {
    if (graph.find(from) != graph.end() && graph.find(to) != graph.end()) {
        for (const auto& neighbor : graph[from].relatedProducts) {
            if (neighbor.first == &graph[to])
                return;
        }
        graph[from].relatedProducts.emplace_back(&graph[to], weight);
    }
}

vector<string> Graph::traverse(const vector<string> &userInput) {
    vector<string> result;

    for (const string& asin : userInput) {
        if (graph.find(asin) != graph.end()) {
            for (const auto& neighbor : graph[asin].relatedProducts) {
                Node* node = neighbor.first;
                result.push_back(node->product.title);
            }
        }
    }
    return result;
}

void Graph::buildGraph(const vector<Product>& products, Graph& graph, const string& price, const string& age, const string& relationship) {
    for (const auto& p : products) {
        graph.addNode(p);
    }

    // connect products
    for (int i = 0; i < products.size(); i++) {
        for (int j = 0; j < products.size(); j++) {
            int weight = 0;
            if (products[i].interest == products[j].interest)
                weight++;
            if (products[i].ageGroup == products[j].ageGroup && products[i].ageGroup == age)
                weight++;
            if (products[i].relationship == products[j].relationship && products[i].relationship == relationship)
                weight++;
            if (weight > 0) {
                graph.addEdge(products[i].asin, products[j].asin, weight);
                graph.addEdge(products[j].asin, products[i].asin, weight);
            }
        }
    }
}
