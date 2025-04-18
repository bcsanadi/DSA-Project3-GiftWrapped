#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include <map>
#include <vector>
#include <string>
#include "Product.h"

using namespace std;

struct Node {
  Product product;
vector<pair<Node*, int>> relatedProducts;
  Node() = default;
  Node(const Product& product) : product(product) {}
};

class Graph {
  map<string, Node> graph;
  map<string, vector<Product>> categoryBuckets;
public:
  void addNode(const Product& product);
  void addEdge(const string& from, const string& to, int weight);
  vector<string> traverse(const vector<string>& userInput);
  void buildGraph(const vector<Product>& products, Graph& graph, const string& price, const string& age, const string& relationship);
};

#endif //GRAPH_H
