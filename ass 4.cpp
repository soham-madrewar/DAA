// name: soham madrewar
// prn: 123B1F055
// assignment description 
// A smart city is implementing an intelligent traffic management system to assist ambulances
// in reaching hospitals as quickly as possible. The city’s road network is represented as a
// graph, where:
// ● Intersections (junctions) are nodes.
// ● Roads between intersections are edges with weights representing travel time (in minutes)
// considering traffic congestion.
// An ambulance is currently at Source (S) and needs to reach the nearest hospital (Destination
// D) in the shortest possible time. Due to dynamic traffic conditions, the weight of each road
// segment may change in real time.
// As a transportation engineer, you are assigned to:
// 1. Implement Dijkstra’s algorithm to find the shortest path from the ambulance's current
// location (S) to all possible hospitals.
// 2. Account for dynamic weight updates as traffic conditions change.
// 3. Optimize the system to work efficiently for a large city with thousands of intersections
// and roads.
// 4. Provide a visual representation of the optimal path for navigation.
// Expected Outcome:
// The system should suggest the quickest route for the ambulance, updating dynamically
// based on real-time traffic conditions, ensuring minimal response time to emergencies.


#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;


using PII = pair<int,int>; 

vector<int> dijkstra(int V, const vector<vector<PII>>& adj, int src) {
    const int INF = INT_MAX;
    vector<int> dist(V, INF);
    dist[src] = 0;

    
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue; 

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

    vector<vector<PII>> adj(V); 

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

   
    vector<int> dist = dijkstra(V, adj, source);

   
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


