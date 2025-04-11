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
  vector<Node*> relatedProducts;
};

class Graph {
  map<string, Node> graph;
  map<string, vector<Product>> categoryBuckets;

public:
  void addNode(const string& label);
  void addEdge(const string& from, const string& to);
  vector<string> traverse(const vector<string>& userInput);
};

#endif //GRAPH_H
