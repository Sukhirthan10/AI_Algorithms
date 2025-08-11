#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>

void dfs_history(std::unordered_map<char, std::vector<char>> &graph, char startNode, char goalNode);

int main() {
    std::unordered_map<char, std::vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    dfs_history(graph, 'S', 'G');
}

void dfs_history(std::unordered_map<char, std::vector<char>> &graph, char startNode, char goalNode) {
    std::stack<std::vector<char>> s;
    std::unordered_set<char> visited;

    s.push({startNode});
    visited.insert(startNode);

    while (!s.empty()) {
        std::vector<char> currentPath = s.top();
        s.pop();
        char currentNode = currentPath.back();

        if (currentNode == goalNode) {
            for (char c : currentPath) {
                std::cout << c << " ";
            }
            std::cout << "\n";
            return;
        }

        for (char neighbor : graph[currentNode]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                std::vector<char> newPath = currentPath;
                newPath.push_back(neighbor);
                s.push(newPath);
            }
        }
    }
}