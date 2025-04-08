#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Node {
  string label;
  vector<Node*> neighbors;
};

class Graph {
  map<string, Node> graph;
  void addNode(const string& label);
  void addEdge(const string& from, const string& to);
  vector<string> traverse(const vector<string>& userInput);
};

#endif //GRAPH_H
