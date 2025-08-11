#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

void bfs_history(std::unordered_map<char, std::vector<char>> &graph, char startNode, char goalNode);

int main() {
    std::unordered_map<char, std::vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    bfs_history(graph, 'S', 'G');
    
    return 0;
}

void bfs_history(std::unordered_map<char, std::vector<char>> &graph, char startNode, char goalNode) {
    std::queue<std::vector<char>> q;
    std::unordered_set<char> visited;

    q.push({startNode});
    visited.insert(startNode);

    while (!q.empty()) {
        std::vector<char> currentPath = q.front();
        q.pop();

        char currentNode = currentPath.back();

        if (currentNode == goalNode) {
            for (char node : currentPath) {
                std::cout << node << " ";
            }
            std::cout << "\n";
            return;
        }

        for (char neighbor : graph[currentNode]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                std::vector<char> newPath = currentPath;
                newPath.push_back(neighbor);
                q.push(newPath);
            }
        }
    }
}