#include <climits>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Graph {
    vector<vector<pair<int, int>>> g;

    int min_distance(vector<int> &distances, vector<bool> &visited) {
        int minimum = INT_MAX, min_index;

        for (int v = 0; v < distances.size(); v++) {
            if (!visited[v] && distances[v] < minimum) {
                minimum = distances[v];
                min_index = v;
            }
        }

        return min_index;
    }

public:
    Graph(int no_of_edges) {
        g.resize(no_of_edges);
    }

    void add_edge(int a, int b, int weight) {
        g[a].push_back({b, weight});
    }

    vector<int> djkstra_priority(int source) {
        vector<int> distances(g.size(), INT_MAX);

        distances[source] = 0;

        set<pair<int, int>> q;
        q.insert({0, source});

        while (!q.empty()) {
            auto node = *q.begin();
            auto v = node.second;

            q.erase(q.begin());

            for (auto neighbor: g[v]) {
                int to = neighbor.first;
                int weight = neighbor.second;

                if (distances[v] + weight < distances[to]) {
                    //q.erase({distances[to], to});
                    distances[to] = weight + distances[v];
                    q.insert({distances[to], to});
                }
            }

        }

        return distances;
    }

    vector<int> djkstra(int source) {
        vector<int> distances(g.size(), INT_MAX);
        vector<bool> visited(g.size(), 0);

        distances[source] = 0;

        for (int i = 0; i < g.size()-1; i++) {

            int u = min_distance(distances, visited);
            visited[u] = true;

            for (auto &neighbor: g[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                }
            }
        }

        return distances;
    }
};

int main() {

    int n;
    cout << "Enter the number of vertices" << endl;

    cin >> n;


    Graph g(n);

    while (true) {
        cout << "Enter new edge(0) or cancel(1)" << endl;
        int x; cin >> x;
        if (!x) {
            int a, b, w;
            cin >> a >> b >> w;
            g.add_edge(a, b, w);
        } else {
            break;
        }
    }

    int source;
    cout << "Enter source" << endl;
    cin >> source;

    vector<int> output = g.djkstra(source);

    for (int i = 0; i < output.size(); i++) {
        cout << i << " " << output[i] << " " << endl;
    }


    return 0;
}
