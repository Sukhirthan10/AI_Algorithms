#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

void dfs(std::unordered_map<char, std::vector<char>> &graph, char startNode, char goalNode);

bool bfs(std::unordered_map<char, std::vector<char>> &graph, char currentNode, char goalNode, int limit, std::vector<char> &path);

int main() {
    std::unordered_map<char, std::vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    dfs(graphData, 'S', 'G');

    return 0;
}

void dfs(std::unordered_map<char, std::vector<char>> &graph, char startNode, char goalNode) {
    for (int depth = 0; ; ++depth) {
        std::vector<char> path;
        if (bfs(graph, startNode, goalNode, depth, path)) {
            for (char node : path) {
                std::cout << node << " ";
            }
            std::cout << "\n";
            return;
        }
    }
}

bool bfs(std::unordered_map<char, std::vector<char>> &graph, char currentNode, char goalNode, int limit, std::vector<char> &path) {
    path.push_back(currentNode);

    if (currentNode == goalNode) {
        return true;
    }

    if (limit <= 0) {
        path.pop_back();
        return false;
    }

    std::vector<char> neighbors = graph[currentNode];
    std::sort(neighbors.begin(), neighbors.end());

    for (char neighbor : neighbors) {
        if (std::find(path.begin(), path.end(), neighbor) == path.end()) {
            if (bfs(graph, neighbor, goalNode, limit - 1, path)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}