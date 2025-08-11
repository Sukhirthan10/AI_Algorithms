
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>

int heuristic(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, std::unordered_map<char, int> &heuristicValues, char startNode, char goalNode);

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
    
    heuristic(graph, heuristicValues, 'S', 'G');

    return 0;
}

int heuristic(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, std::unordered_map<char, int> &heuristicValues, char startNode, char goalNode) {
    using State = std::pair<std::pair<int, int>, std::pair<char, std::vector<char>>>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    pq.push({{heuristicValues[startNode], 0}, {startNode, {startNode}}});

    while (!pq.empty()) {
        auto [costs, nodePath] = pq.top();
        auto [estimatedCost, pathCost] = costs;
        auto [currentNode, path] = nodePath;
        pq.pop();

        if (currentNode == goalNode) {
            for (char node : path) std::cout << node << " ";
            std::cout << "| Cost: " << pathCost << "\n";
            return pathCost;
        }

        for (auto& neighbor : graph[currentNode]) {
            int newPathCost = pathCost + neighbor.second;
            int newEstimatedCost = newPathCost + heuristicValues[neighbor.first];
            std::vector<char> newPath = path;
            newPath.push_back(neighbor.first);
            pq.push({{newEstimatedCost, newPathCost}, {neighbor.first, newPath}});
        }
    }
    return -1;
}