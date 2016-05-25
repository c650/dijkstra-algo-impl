#include <iostream>
#include <limits> // max int
#include <vector>
#include <algorithm> // make_heap
#include <unordered_map>

using namespace std;

int main() {
	unordered_map< char, const unordered_map<char, int> > vertices;
	
	// initialize test input
	vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type('A', { {'B', 7}, {'C', 8} }));
	vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type('B', { {'A', 7}, {'F', 2} }));
	vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type('C', { {'A', 8}, {'F', 6}, {'G', 4} }));
	vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type('D', { {'F', 8} }));
    vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type('E', { {'H', 1} }));
    vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type('F', { {'B', 2}, {'C', 6}, {'D', 8}, {'G', 9}, {'H', 3} }));
    vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type('G', { {'C', 4}, {'F', 9} }));
    vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type('H', { {'E', 1}, {'F', 3} }));

    char start = 'A';
    char finish = 'H';

    unordered_map<char, int> distances;
    unordered_map<char, char> previous;
    vector<char> nodes;
    vector<char> path;

    auto comparator = [&] (char left, char right) {return distances[left] > distances[right];};

    for (auto& vertex : vertices) {
    	if (vertex.first == start)
    		distances[vertex.first] = 0;
    	else
    		distances[vertex.first] = numeric_limits<int>::max();

    	nodes.push_back(vertex.first);
    	// make min heap
    	push_heap(nodes.begin(), nodes.end(), comparator);
    }

    while(!nodes.empty()) {
    	pop_heap(nodes.begin(), nodes.end(), comparator);
    	char smallest = nodes.back();
    	nodes.pop_back();
    	cout << "smallest = " << smallest << endl;
    	if (smallest == finish) {
    		while(previous.find(smallest) != previous.end()) {
    			path.push_back(smallest);
    			smallest = previous[smallest];
    		}
    		path.push_back(start);
    		reverse(path.begin(), path.end());
    		break; // quit finding shortest path
    	}

    	if (distances[smallest] == numeric_limits<int>::max()) {
    		break;
    	}

    	for (auto& neighbor : vertices[smallest]) {
    		int tmp = distances[smallest] + neighbor.second;

    		if (tmp < distances[neighbor.first]) {
    			
    			distances[neighbor.first] = tmp;
    			previous[neighbor.first] = smallest;

    			make_heap(nodes.begin(), nodes.end(), comparator); // we need to re-heapify after updating
    		}
    	}
    }

    for (auto& v : path) cout << v << " ";
   	cout << endl;

   	cout << distances[finish] << endl;

	return 0;
}