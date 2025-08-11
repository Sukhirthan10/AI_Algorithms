#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

bool hill_climbing(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, std::unordered_map<char, int> &heuristicValues, char currentNode, char goalNode, std::vector<char> &path);

int main() {
    std::unordered_map<char, std::vector<std::pair<char, int>>> graph;
    graph['S'] = {{'A', 3}, {'B', 5}};
    graph['A'] = {{'D', 3}, {'B', 4}, {'S', 3}};
    graph['B'] = {{'A', 4}, {'C', 4}, {'S', 5}};
    graph['C'] = {{'E', 6}, {'B', 6}};
    graph['D'] = {{'A', 3}, {'G', 5}};
    graph['E'] = {{'C', 6}};
    graph['G'] = {{'D', 5}};

    std::unordered_map<char, int> heuristicValues = {
        {'S', 10}, {'A', 7}, {'B', 6}, {'C', 7}, {'D', 5}, {'E', 6}, {'G', 0}
    };

    std::vector<char> path;
    
    if (hill_climbing(graph, heuristicValues, 'S', 'G', path)) {
        for (char node : path) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

bool hill_climbing(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, std::unordered_map<char, int> &heuristicValues, char currentNode, char goalNode, std::vector<char> &path) {
    path.push_back(currentNode);

    if (currentNode == goalNode) {
        return true;
    }

    std::vector<std::pair<char, int>> neighbors = graph[currentNode];
    std::sort(neighbors.begin(), neighbors.end(),
         [&](const std::pair<char, int>& a, const std::pair<char, int>& b) {
             return heuristicValues[a.first] < heuristicValues[b.first];
         });

    for (const auto& neighbor : neighbors) {
        char nextNode = neighbor.first;
        if (hill_climbing(graph, heuristicValues, nextNode, goalNode, path)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}