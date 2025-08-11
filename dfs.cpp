#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>


void dfs(std::unordered_map<char, std::vector<char>> &graph, char start, char goal) ;

int main() {
    std::unordered_map<char, std::vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    dfs(graph, 'S', 'G');
}

void dfs(std::unordered_map<char, std::vector<char>> &graph, char start, char goal) {
    std::stack<std::pair<char, std::vector<char>>> s;

    s.push({start, {start}});

    while (!s.empty()) {
        auto [node, path] = s.top();
        s.pop();

        if (node == goal) {
            for (char c : path) {
                std::cout << c << " ";
            }
            std::cout << "\n";
            return;
        }

        for (char neigh : graph[node]) {
            if (std::find(path.begin(), path.end(), neigh) == path.end()) {
                std::vector<char> new_path = path;
                new_path.push_back(neigh);
                s.push({neigh, new_path});
            }
        }
    }
}