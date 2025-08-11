#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

void bfs(std::unordered_map<char, std::vector<char>> &graph,char startNode,char goalNode);

int main() {
    std::unordered_map<char, std::vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    bfs(graph, 'S', 'G');
    
    return 0;
}

void bfs(std::unordered_map<char, std::vector<char>> &graph,char startNode,char goalNode) {
    std::queue<std::pair<char, std::vector<char>>> q;
    q.push({startNode, {startNode}});
    bool goalFound = false;

    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<std::vector<char>> levelSolutions;

        for (int i = 0; i < levelSize; i++) {
            auto [currentNode, currentPath] = q.front();
            q.pop();

            if (currentNode == goalNode) {
                goalFound = true;
                levelSolutions.push_back(currentPath);
                continue;
            }

            if (!goalFound) {
                for (char neighbor : graph[currentNode]) {
                    if (std::find(currentPath.begin(), currentPath.end(), neighbor) == currentPath.end()) {
                        std::vector<char> newPath = currentPath;
                        newPath.push_back(neighbor);
                        q.push({neighbor, newPath});
                    }
                }
            }
        }

        if (goalFound) {
            for (const auto &path : levelSolutions) {
                for (char node : path) {
                    std::cout << node << " ";
                }
                std::cout << "\n";
            }
            break;
        }
    }
}