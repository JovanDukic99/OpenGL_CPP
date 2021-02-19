#pragma once
#include <string>
#include <vector>
#include <queue>
#include "PriorityQueue.h"
#include "Square.h"
#include "AStarAlgorithm.h"
class Utils
{
public:
	static void loadMap(std::string filePath, std::vector<Square>& blocks, float unitWidth, float unitHeight);
	static void loadMap(std::string filePath, std::vector<Square>& blocks, AStarAlgorithm& algorithm, float unitWidth, float unitHeight);
	template <typename T, typename F, typename G>
	static bool contains(std::priority_queue<T, F, G> queue, T node);
	template <typename T>
	static bool contains(std::vector<T>& nodes, T node);
};

template<typename T, typename F, typename G>
inline bool Utils::contains(std::priority_queue<T, F, G> queue, T node) {
	while (!queue.empty()) {
		T temp = queue.top();
		if (temp == node) {
			return true;
		}
		queue.pop();
	}
	return false;
}

template<typename T>
inline bool Utils::contains(std::vector<T>& nodes, T node) {
	for (size_t i = 0; i < nodes.size(); i++) {
		if (nodes[i] == node) {
			return true;
		}
	}
	return false;
}
