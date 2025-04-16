#include "Graph.h"

void Graph::addNode(const Product& product) {
    if (graph.find(product.title) == graph.end()) {
        graph[product.title] = Node{product};
    }
}

void Graph::addEdge(const string &from, const string &to) {
    if (graph.find(from) != graph.end() && graph.find(to) != graph.end())
        graph[from].relatedProducts.push_back(&graph[to]);
}

vector<string> Graph::traverse(const vector<string> &userInput) {
    vector<string> result;
    return result;
}
