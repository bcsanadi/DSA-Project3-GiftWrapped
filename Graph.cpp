#include "Graph.h"

void Graph::addNode(const string &label) {
    if (graph.find(label) == graph.end())
        graph[label] = Node{label};
}

void Graph::addEdge(const string &from, const string &to) {
    if (graph.find(from) != graph.end() && graph.find(to) != graph.end())
        graph[from].neighbors.push_back(&graph[to]);
}

vector<string> Graph::traverse(const vector<string> &userInput) {
}
