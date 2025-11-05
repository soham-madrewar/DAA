#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e12; // large value for "no edge"

// Node for priority queue
struct Node {
    vector<vector<ll>> reduced; // reduced cost matrix
    vector<int> path;           // visited path (sequence of vertices)
    ll cost;                    // current lower bound cost
    int vertex;                 // current vertex
    int level;                  // how many vertices visited (root level = 0)

    Node(const vector<vector<ll>>& r, const vector<int>& p, ll c, int v, int l)
        : reduced(r), path(p), cost(c), vertex(v), level(l) {}
};

// Reduce matrix (row & column reduction). Modify matrix and return total reduction amount.
ll reduceMatrix(vector<vector<ll>>& mat) {
    int n = (int)mat.size();
    ll reduction = 0;

    // Row reduction
    for (int i = 0; i < n; ++i) {
        ll rowMin = INF;
        for (int j = 0; j < n; ++j)
            rowMin = min(rowMin, mat[i][j]);
        if (rowMin != INF && rowMin > 0) {
            reduction += rowMin;
            for (int j = 0; j < n; ++j)
                if (mat[i][j] != INF) mat[i][j] -= rowMin;
        }
    }

    // Column reduction
    for (int j = 0; j < n; ++j) {
        ll colMin = INF;
        for (int i = 0; i < n; ++i)
            colMin = min(colMin, mat[i][j]);
        if (colMin != INF && colMin > 0) {
            reduction += colMin;
            for (int i = 0; i < n; ++i)
                if (mat[i][j] != INF) mat[i][j] -= colMin;
        }
    }

    return reduction;
}

// Deep copy matrix
vector<vector<ll>> copyMatrix(const vector<vector<ll>>& src) {
    return src;
}

// Create child node when taking edge from -> to
Node createChild(const Node& parent, int from, int to, const vector<vector<ll>>& originalCost) {
    int n = (int)originalCost.size();
    vector<vector<ll>> childMat = copyMatrix(parent.reduced);

    // forbid row 'from' and column 'to'
    for (int k = 0; k < n; ++k) {
        childMat[from][k] = INF;
        childMat[k][to] = INF;
    }
    // forbid returning to start prematurely
    childMat[to][0] = INF;

    // reduction on child matrix
    ll reduction = reduceMatrix(childMat);

    // Use original cost for actual edge weight from->to
    ll edgeCost = originalCost[from][to];

    // child cost = parent's cost + edgeCost + reduction
    ll childCost = parent.cost + edgeCost + reduction;

    vector<int> newPath = parent.path;
    newPath.push_back(to);

    return Node(childMat, newPath, childCost, to, parent.level + 1);
}

// Branch and Bound solver
void branchAndBound(const vector<vector<ll>>& cost) {
    int n = (int)cost.size();
    // root reduced matrix = copy of original cost (diagonal should be INF already)
    vector<vector<ll>> rootMat = copyMatrix(cost);

    // initial reduction
    ll rootReduction = reduceMatrix(rootMat);

    // root node: start at city 0
    vector<int> rootPath = {0};
    Node root(rootMat, rootPath, rootReduction, 0, 0);

    // min-heap by cost
    auto cmp = [](const Node& a, const Node& b) { return a.cost > b.cost; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    pq.push(root);

    ll bestCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        // prune if cost already worse than best found
        if (cur.cost >= bestCost) continue;

        // if all vertices visited, close the tour by returning to start
        if (cur.level == n - 1) {
            ll totalCost = cur.cost + cost[cur.vertex][0];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestPath = cur.path;
                bestPath.push_back(0);
            }
            continue;
        }

        // expand node: try all unvisited vertices
        for (int j = 0; j < n; ++j) {
            if (cost[cur.vertex][j] != INF) {
                // skip if already visited
                bool visited = false;
                for (int v : cur.path) if (v == j) { visited = true; break; }
                if (visited) continue;

                Node child = createChild(cur, cur.vertex, j, cost);
                if (child.cost < bestCost) pq.push(child);
            }
        }
    }

    // print result
    if (bestPath.empty()) {
        cout << "No Hamiltonian tour found.\n";
    } else {
        cout << "\nOptimal Delivery Route:\n";
        for (size_t i = 0; i < bestPath.size(); ++i) {
            cout << "City " << (bestPath[i] + 1);
            if (i + 1 < bestPath.size()) cout << " -> ";
        }
        cout << "\nMinimum Delivery Cost: " << bestCost << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Enter number of cities: ";
    if (!(cin >> n) || n <= 0) return 0;

    vector<vector<ll>> distance(n, vector<ll>(n, 0));
    cout << "Enter distance matrix (0 for same city):\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            ll d; cin >> d;
            if (i == j) distance[i][j] = 0;
            else distance[i][j] = d;
        }

    vector<double> fuelMult(n);
    cout << "Enter fuel multiplier for each city (space separated):\n";
    for (int i = 0; i < n; ++i) cin >> fuelMult[i];

    // build cost matrix: cost[i][j] = round(distance[i][j] * fuelMult[i]), diagonal INF
    vector<vector<ll>> cost(n, vector<ll>(n, INF));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (i == j) cost[i][j] = INF;
            else cost[i][j] = (ll) llround(distance[i][j] * fuelMult[i]);
        }

    // optional print of computed cost matrix
    cout << "\nComputed cost matrix (INF shown as -):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (cost[i][j] >= INF) cout << "- ";
            else cout << cost[i][j] << ' ';
        }
        cout << '\n';
    }

    // run Branch and Bound to find optimal tour
    branchAndBound(cost);

    return 0;
}
