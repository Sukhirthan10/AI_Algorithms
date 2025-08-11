#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>

int find_shortest_path_exhaustive(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, char currentNode, char goalNode, std::vector<char> &path, int currentCost);
int branch_and_bound_uniform_cost(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, char startNode, char goalNode, int bound);

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
    int oracle_distance = find_shortest_path_exhaustive(graph, 'S', 'G', path, 0);

    if (oracle_distance == INT_MAX) {
        std::cout << "not reachable" << "\n";
        return 0;
    } else {
        std::cout << "\nshortest path distance: " << oracle_distance << "\n";
    }

    int result = branch_and_bound_uniform_cost(graph, 'S', 'G', oracle_distance);

    if (result == -1)
        std::cout << " not found within bound\n";
    else
        std::cout << "best path cost : " << result << "\n";

    return 0;
}

int branch_and_bound_uniform_cost(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, char startNode, char goalNode, int bound) {
    using State = std::pair<int, std::pair<char, std::vector<char>>>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push({0, {startNode, {startNode}}});
    std::unordered_set<char> visited;

    while (!pq.empty()) {
        auto [cost, nodePath] = pq.top();
        auto [currentNode, path] = nodePath;
        pq.pop();

        if (cost > bound) {
            continue;
        }

        if (visited.count(currentNode)) {
            continue;
        }
        visited.insert(currentNode);

        if (currentNode == goalNode) {
            for (char node : path) std::cout << node << " ";
            std::cout << "| Cost: " << cost << "\n";
            return cost;
        }

        for (auto& neighbor : graph[currentNode]) {
            if (!visited.count(neighbor.first)) {
                std::vector<char> newPath = path;
                newPath.push_back(neighbor.first);
                pq.push({cost + neighbor.second, {neighbor.first, newPath}});
            }
        }
    }
    return -1;
}

int find_shortest_path_exhaustive(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, char currentNode, char goalNode, std::vector<char> &path, int currentCost) {
    if (currentNode == goalNode) {
        return currentCost;
    }
    int minCost = INT_MAX;
    for (const auto& neighbor : graph[currentNode]) {
        if (std::find(path.begin(), path.end(), neighbor.first) == path.end()) {
            path.push_back(neighbor.first);
            minCost = std::min(minCost, find_shortest_path_exhaustive(graph, neighbor.first, goalNode, path, currentCost + neighbor.second));
            path.pop_back();
        }
    }
    return minCost;
}