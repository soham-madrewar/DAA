#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Graph: adjacency list as (neighbor, weight)
using PII = pair<int,int>; // {distance, node} ya {neighbor, weight}

vector<int> dijkstra(int V, const vector<vector<PII>>& adj, int src) {
    const int INF = INT_MAX;
    vector<int> dist(V, INF);
    dist[src] = 0;

    // min-heap: {currentDistance, node}
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue; // stale entry skip

        for (auto [v, w] : adj[u]) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int V, E;
    cout << "Enter total no. of intersections: ";
    cin >> V;
    cout << "Enter total number of roads: ";
    cin >> E;

    vector<vector<PII>> adj(V); // 0..V-1 nodes

    cout << "Enter roads as: u v w (0-indexed, undirected)\n";
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int source;
    cout << "Enter ambulance start location: ";
    cin >> source;

    int H;
    cout << "Enter number of hospitals: ";
    cin >> H;

    vector<int> hospitals(H);
    cout << "Enter hospital nodes: ";
    for (int i = 0; i < H; ++i) cin >> hospitals[i];

    // Run Dijkstra once from source
    vector<int> dist = dijkstra(V, adj, source);

    // Find nearest hospital
    int bestHospital = -1, bestTime = INT_MAX;
    for (int h : hospitals) {
        if (h >= 0 && h < V && dist[h] < bestTime) {
            bestTime = dist[h];
            bestHospital = h;
        }
    }

    if (bestHospital != -1 && bestTime != INT_MAX) {
        cout << "Nearest hospital is at node " << bestHospital
             << " with travel time " << bestTime << " minutes.\n";
    } else {
        cout << "No reachable hospital found.\n";
    }

    return 0;
}
