#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

int oracle(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, char currentNode, char goalNode, std::vector<char> &path, int currentCost);

int main() {
    std::unordered_map<char, std::vector<std::pair<char, int>>> graph;
    graph['S'] = {{'A', 3}, {'B', 5}};
    graph['A'] = {{'D', 3}, {'B', 4}, {'S', 3}};
    graph['B'] = {{'A', 4}, {'C', 4}, {'S', 5}};
    graph['C'] = {{'E', 6}, {'B', 6}};
    graph['D'] = {{'A', 3}, {'G', 5}};
    graph['E'] = {{'C', 6}};
    graph['G'] = {{'D', 5}};

    std::vector<char> path = {'S'};
    int shortestDistance = oracle(graph, 'S', 'G', path, 0);

    if (shortestDistance == INT_MAX) {
        std::cout << "not possible" << "\n";
    } else {
        std::cout << "\nshortest distance: " << shortestDistance << "\n";
    }

    return 0;
}

int oracle(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, char currentNode, char goalNode, std::vector<char> &path, int currentCost) {
    if (currentNode == goalNode) {
        std::cout << "path= ";
        for (char node : path) {
            std::cout << node << " ";
        }
        std::cout << "cost=" << currentCost << "\n";
        return currentCost;
    }

    int minCost = INT_MAX;

    for (const auto& neighbor : graph[currentNode]) {
        if (std::find(path.begin(), path.end(), neighbor.first) == path.end()) {
            path.push_back(neighbor.first);
            minCost = std::min(minCost, oracle(graph, neighbor.first, goalNode, path, currentCost + neighbor.second));
            path.pop_back();
        }
    }
    
    return minCost;
}