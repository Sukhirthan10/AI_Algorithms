#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <functional>

bool beam_search(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, std::unordered_map<char, int> &heuristicValues, char startNode, char goalNode, size_t beamWidth);

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

    size_t beamWidth = 2;
    if (!beam_search(graph, heuristicValues, 'S', 'G', beamWidth)) {
        std::cout << "not reachable" << "\n";
    }

    return 0;
}

bool beam_search(std::unordered_map<char, std::vector<std::pair<char, int>>> &graph, std::unordered_map<char, int> &heuristicValues, char startNode, char goalNode, size_t beamWidth) {
    using PathState = std::pair<char, std::vector<char>>;
    auto comparePaths = [&](const PathState& a, const PathState& b) {
        return heuristicValues.at(a.first) > heuristicValues.at(b.first);
    };

    std::priority_queue<PathState, std::vector<PathState>, decltype(comparePaths)> beam(comparePaths);
    beam.push({startNode, {startNode}});

    while (!beam.empty()) {
        std::priority_queue<PathState, std::vector<PathState>, decltype(comparePaths)> candidates(comparePaths);

        while (!beam.empty()) {
            PathState current = beam.top();
            beam.pop();

            char currentNode = current.first;
            std::vector<char> currentPath = current.second;

            if (currentNode == goalNode) {
                for (char node : currentPath) {
                    std::cout << node << " ";
                }
                std::cout << "\n";
                return true;
            }

            for (const auto& neighbor : graph.at(currentNode)) {
                std::vector<char> newPath = currentPath;
                newPath.push_back(neighbor.first);
                candidates.push({neighbor.first, newPath});
            }
        }

        while (!candidates.empty() && beam.size() < beamWidth) {
            beam.push(candidates.top());
            candidates.pop();
        }

        if (beam.empty()) {
            break;
        }
    }
    return false;
}