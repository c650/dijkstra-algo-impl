#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
void debug(const std::string& s) {
	std::cout << s << std::endl;
}
int dijkstra(std::vector< std::vector<int> >& matrix, int start, int end) {

	start--; end--;

	std::vector<int> distances(matrix.size()), previous(matrix.size());
	std::vector<int> nodes, path;

	for (int i = 0, n = matrix[start].size(); i < n; i++) {

		if (i == start)
			distances[i] = 0;
		else
			distances[i] = std::numeric_limits<int>::max();

		nodes.push_back(i);
	}
	
	auto comp = [&](int l, int r) {return distances[l] > distances[r];};
	std::sort(nodes.begin(), nodes.end(), comp);
	
	while(!nodes.empty()) {
		int smallest = nodes.back();
		nodes.pop_back();

		if (smallest == end) {

			while(smallest != start) {

				path.push_back(smallest+1);
				smallest = previous[smallest];
			}
			
			path.push_back(start+1);
			std::reverse(path.begin(), path.end());
			break;
		}

		if (distances[smallest] == std::numeric_limits<int>::max())
			break;

		for(int i = 0, n = matrix[smallest].size(); i < n; i++) {
			int tmp = distances[smallest] + matrix[smallest][i];
			
			if (tmp < 0)
				tmp = std::numeric_limits<int>::max();
				// combat integer overflow!
			
			if (tmp < distances[i]) {
				distances[i] = tmp;
				previous[i] = smallest;

				std::sort(nodes.begin(), nodes.end(), comp);
			}
		}
	}

	for(auto& v : path) std::cout << v << " ";
	std::cout << "\n";

	return distances[end];
}

int main() {
	std::cout << "How many nodes? ";
	int nodes; std::cin >> nodes;

	std::vector < std::vector<int> > matrix(nodes, std::vector<int>(nodes));

	for (auto& v : matrix) {
		for (auto& d : v) {
			std::cin >> d;

			if (d < 0)
				d = std::numeric_limits<int>::max();
		}
	}

	std::cout << "Start point? ";
	int start; std::cin >> start;

	std::cout << "End point? ";
	int end; std::cin >> end;

	std::cout << "Distance: " << dijkstra(matrix, start, end) << std::endl;

	return 0;
}