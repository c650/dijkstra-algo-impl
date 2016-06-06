#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <utility>

/* typedef to make more clear */
typedef std::vector< std::vector< std::pair<int,int> > > adjacency_list;

int dijkstra(const adjacency_list& adj_list, const int& start, const int& end, std::vector<int>& distances);

int main() {
    int n,m; std::cin >> n >> m;
    
    /*
        adj-list using vector of size n holding a vector for
        each vertex.
    */
    adjacency_list adj_list(n);
    
    int f,s,w; /* first, second, weight */
    for (int i = 0; i < m; i++) {
        std::cin >> f >> s >> w;

        /* graph is undirected */
        adj_list[f-1].push_back( std::make_pair(s-1,w) );
        adj_list[s-1].push_back( std::make_pair(f-1,w) );
    }
    
    int start; std::cin >> start;
    start--; /* zero-base the starting point */

    std::vector<int> distances(adj_list.size(), std::numeric_limits<int>::max());
    for (int i = 0; i < n; i++) {
        if (i != start)
            std::cout << dijkstra(adj_list, start, i, distances) << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

int dijkstra(const adjacency_list& adj_list, const int& start, const int& end, std::vector<int>& distances) {
    
    /* another vec of ints to keep track of traversable nodes*/
    std::vector<int> nodes;
    
    distances[start] = 0;
    
    for (int i = 0, n = adj_list.size(); i < n; i++)
        nodes.push_back(i);
    
    nodes.push_back(start);
    
    auto comp = [&](int l, int r) {return distances[l] > distances[r];};
    std::make_heap(nodes.begin(), nodes.end(), comp);
    
    while(!nodes.empty()) {
        std::pop_heap(nodes.begin(), nodes.end(), comp);
        int smallest = nodes.back();
        nodes.pop_back();
 
        if (smallest == end)
            break; /* returns at bottom anyway */
 
        if (distances[smallest] == std::numeric_limits<int>::max())
            break;
 
        for(int i = 0, n = adj_list[smallest].size(); i < n; i++) {
            int tmp = distances[smallest] + adj_list[smallest][i].second;
           
            if (tmp < distances[adj_list[smallest][i].first] && tmp > 0) {
                distances[adj_list[smallest][i].first] = tmp;
                std::make_heap(nodes.begin(), nodes.end(), comp);
            }
        }
    }
    if (distances[end] == std::numeric_limits<int>::max())
        return -1;
    else
        return distances[end];
}