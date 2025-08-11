
#include <bits/stdc++.h>
using namespace std;

void bms(unordered_map<char, vector<char>> &adjList, char origin, char destination);

int main() {
    unordered_map<char, vector<char>> graph;
    graph['S'] = {'A', 'B'};
    graph['A'] = {'D', 'B', 'S'};
    graph['B'] = {'A', 'C', 'S'};
    graph['C'] = {'E', 'B'};
    graph['D'] = {'A', 'G'};
    graph['E'] = {'C'};
    graph['G'] = {'D'};

    bms(graph, 'S', 'G');
    
    return 0;
}


void bms(unordered_map<char, vector<char>> &adjList, char origin, char destination) {
    auto pathComparator = [](const pair<char, vector<char>> &pathA, const pair<char, vector<char>> &pathB) {
        return (pathA.first != pathB.first) ? pathA.first > pathB.first : pathA.second.size() > pathB.second.size();
    };

    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(pathComparator)> explorationQueue(pathComparator);
    
    explorationQueue.push({origin, {origin}});

    while (!explorationQueue.empty()) {
        auto [currentNode, currentPath] = explorationQueue.top();
        explorationQueue.pop();

        if (currentNode == destination) {
            for (char node : currentPath) {
                cout << node << " ";
            }
            cout << "\n";
            continue;
        }

        for (char adjacentNode : adjList[currentNode]) {
            if (find(currentPath.begin(), currentPath.end(), adjacentNode) == currentPath.end()) {
                vector<char> extendedPath = currentPath;
                extendedPath.push_back(adjacentNode);
                explorationQueue.push({adjacentNode, extendedPath});
            }
        }
    }
}
