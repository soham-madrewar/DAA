// name: soham madrewar
// prn: 123B1F055
// assignment description 
// A logistics company, SwiftCargo, specializes in delivering packages across multiple cities.
// To optimize its delivery process, the company divides the transportation network into
// multiple stages (warehouses, transit hubs, and final delivery points). Each package must
// follow the most cost-efficient or fastest route from the source to the destination while
// passing through these predefined stages.
// As a logistics optimization engineer, you must:
// 1. Model the transportation network as a directed, weighted multistage graph with
// multiple intermediate stages.
// 2. Implement an efficient algorithm (such as Dynamic Programming or Dijkstra’s
// Algorithm) to find the optimal delivery route.
// 3. Ensure that the algorithm scales for large datasets (handling thousands of cities and
// routes).
// 4. Analyze and optimize route selection based on real-time constraints, such as traffic
// conditions, weather delays, or fuel efficiency.
// Constraints & Considerations:
// ● The network is structured into N stages, and every package must pass through at least
// one node in each stage.
// ● There may be multiple paths with different costs/times between stages.
// ● The algorithm should be flexible enough to handle real-time changes (e.g., road
// closures or rerouting requirements).
// ● The system should support batch processing for multiple delivery requests.


#include <iostream>
#include <vector>
#include <limits>
#include <numeric> // for accumulate
using namespace std;

const double INF = 1e18;

struct Edge { int to; double cost; };

// Compute best cost and next node using backward DP on layered DAG
void computeBestCosts(int totalNodes, const vector<vector<Edge>>& adj,
                      vector<double>& bestCost, vector<int>& nextNode) {
    bestCost.assign(totalNodes, INF);
    nextNode.assign(totalNodes, -1);
    bestCost[totalNodes - 1] = 0.0; // assume last node is sink/goal

    for (int u = totalNodes - 2; u >= 0; --u) {
        for (const auto &e : adj[u]) {
            if (e.cost + bestCost[e.to] < bestCost[u]) {
                bestCost[u] = e.cost + bestCost[e.to];
                nextNode[u] = e.to;
            }
        }
    }
}

// Print path starting from src using nextNode table
void printPath(int src, const vector<int>& nextNode, const vector<vector<Edge>>& adj) {
    if (src < 0) return;
    int cur = src;
    double total = 0.0;
    cout << "Path: ";
    while (cur != -1) {
        cout << cur;
        int nx = nextNode[cur];
        if (nx != -1) {
            // find edge cost cur->nx
            for (auto &e : adj[cur]) if (e.to == nx) { total += e.cost; break; }
            cout << " -> ";
        }
        cur = nx;
    }
    cout << "\nTotal route cost: " << (total >= INF ? -1 : total) << "\n";
}

int main() {
    int stages;
    cout << "Enter total no. of stages: ";
    if (!(cin >> stages) || stages <= 0) return 0;

    vector<int> nodesInStage(stages);
    cout << "Enter number of nodes in each stage (" << stages << " values):\n";
    for (int i = 0; i < stages; ++i) cin >> nodesInStage[i];

    int totalNodes = accumulate(nodesInStage.begin(), nodesInStage.end(), 0);
    int edges;
    cout << "Enter no. of edges: ";
    cin >> edges;

    vector<vector<Edge>> adj(totalNodes);
    cout << "Enter edges as: u v cost\n"; // assume 0-indexed nodes
    for (int i = 0; i < edges; ++i) {
        int u, v; double c;
        cin >> u >> v >> c;
        if (u >= 0 && u < totalNodes && v >= 0 && v < totalNodes)
            adj[u].push_back({v, c});
    }

    // compute best costs before updates
    vector<double> bestCost;
    vector<int> nextNode;
    computeBestCosts(totalNodes, adj, bestCost, nextNode);

    cout << "\nBest costs from stage-0 nodes:\n";
    int idx = 0;
    for (int i = 0; i < nodesInStage[0]; ++i) {
        double c = bestCost[idx];
        cout << "Node " << idx << ": cost = " << (c >= INF ? -1 : c) << "\n";
        ++idx;
    }

    cout << "\nEnter a source node id (or -1 to skip): ";
    int src; cin >> src;
    if (src != -1) printPath(src, nextNode, adj);

    // Live updates to edge costs
    cout << "\nEnter number of live updates to edge costs (0 to finish): ";
    int updates; cin >> updates;
    while (updates-- > 0) {
        int u, v; double mult;
        cout << "Enter update: u v multiplier (e.g. 2 5 1.1): ";
        cin >> u >> v >> mult;
        if (u >= 0 && u < totalNodes) {
            for (auto &e : adj[u]) if (e.to == v) e.cost *= mult;
        }
    }

    // recompute after updates
    computeBestCosts(totalNodes, adj, bestCost, nextNode);

    cout << "\nAfter updates, best costs from stage-0 nodes:\n";
    idx = 0;
    for (int i = 0; i < nodesInStage[0]; ++i) {
        double c = bestCost[idx];
        cout << "Node " << idx << ": cost = " << (c >= INF ? -1 : c) << "\n";
        ++idx;
    }

    return 0;
}

