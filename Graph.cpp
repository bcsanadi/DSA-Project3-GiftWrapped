#include "Graph.h"

void Graph::addNode(const string &value) {
    if (graph.find(value) == graph.end())
        graph[value] = Node{value};
}

void Graph::addEdge(const string &from, const string &to) {
    if (graph.find(from) != graph.end() && graph.find(to) != graph.end())
        graph[from].neighbors.push_back(&graph[to]);
}

vector<string> Graph::traverse(const vector<string> &userInput) {
    vector<string> result;
    for (const string& value : userInput) {
        if (graph.find(value) != graph.end()) {
            Node* nodeCurrent = &graph[value];
            result.push_back(nodeCurrent->value);

            for (Node* nodeNeighbor : nodeCurrent->neighbors) {
                result.push_back(nodeNeighbor->value);
            }

        } else {
            result.push_back("Node not found: " + value);
        }
    }
    return result;
}
