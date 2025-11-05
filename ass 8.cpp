// name: soham madrewar
// prn: 123B1F055
// assignment description 
// A university is facing challenges in scheduling exam timetables due to overlapping student
// enrollments in multiple courses. To prevent clashes, the university needs to assign exam
// slots efficiently, ensuring that no two exams taken by the same student are scheduled at the
// same time.
// To solve this, the university decides to model the problem as a Graph Coloring Problem,
// where:
// ● Each course is represented as a vertex.
// ● An edge exists between two vertices if a student is enrolled in both courses.
// ● Each vertex (course) must be assigned a color (time slot) such that no two adjacent
// vertices share the same color (no two exams with common students are scheduled in the
// same slot).
// As a scheduling system developer, you must:
// 5. Model the problem as a graph and implement a graph coloring algorithm (e.g., Greedy
// Coloring or Backtracking).
// 6. Minimize the number of colors (exam slots) needed while ensuring conflict-free
// scheduling.
// 7. Handle large datasets with thousands of courses and students, optimizing performance.
// 8. Compare the efficiency of Greedy Coloring, DSATUR, and Welsh-Powell algorithms
// for better scheduling.
// Extend the solution to include room allocation constraints where exams in the same slot
// should fit within available classrooms.


#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e12; 


struct Node {
    vector<vector<ll>> reduced; 
    vector<int> path;           
    ll cost;                   
    int vertex;                
    int level;                  

    Node(const vector<vector<ll>>& r, const vector<int>& p, ll c, int v, int l)
        : reduced(r), path(p), cost(c), vertex(v), level(l) {}
};


ll reduceMatrix(vector<vector<ll>>& mat) {
    int n = (int)mat.size();
    ll reduction = 0;

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


vector<vector<ll>> copyMatrix(const vector<vector<ll>>& src) {
    return src;
}


Node createChild(const Node& parent, int from, int to, const vector<vector<ll>>& originalCost) {
    int n = (int)originalCost.size();
    vector<vector<ll>> childMat = copyMatrix(parent.reduced);

    
    for (int k = 0; k < n; ++k) {
        childMat[from][k] = INF;
        childMat[k][to] = INF;
    }
    
    childMat[to][0] = INF;

   
    ll reduction = reduceMatrix(childMat);

    
    ll edgeCost = originalCost[from][to];

    
    ll childCost = parent.cost + edgeCost + reduction;

    vector<int> newPath = parent.path;
    newPath.push_back(to);

    return Node(childMat, newPath, childCost, to, parent.level + 1);
}


void branchAndBound(const vector<vector<ll>>& cost) {
    int n = (int)cost.size();
   
    vector<vector<ll>> rootMat = copyMatrix(cost);

    
    ll rootReduction = reduceMatrix(rootMat);

    vector<int> rootPath = {0};
    Node root(rootMat, rootPath, rootReduction, 0, 0);

    auto cmp = [](const Node& a, const Node& b) { return a.cost > b.cost; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    pq.push(root);

    ll bestCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();

        if (cur.cost >= bestCost) continue;

        if (cur.level == n - 1) {
            ll totalCost = cur.cost + cost[cur.vertex][0];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestPath = cur.path;
                bestPath.push_back(0);
            }
            continue;
        }

        for (int j = 0; j < n; ++j) {
            if (cost[cur.vertex][j] != INF) {
   
                bool visited = false;
                for (int v : cur.path) if (v == j) { visited = true; break; }
                if (visited) continue;

                Node child = createChild(cur, cur.vertex, j, cost);
                if (child.cost < bestCost) pq.push(child);
            }
        }
    }


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


    vector<vector<ll>> cost(n, vector<ll>(n, INF));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (i == j) cost[i][j] = INF;
            else cost[i][j] = (ll) llround(distance[i][j] * fuelMult[i]);
        }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (cost[i][j] >= INF) cout << "- ";
            else cout << cost[i][j] << ' ';
        }
        cout << '\n';
    }

   
    branchAndBound(cost);

    return 0;
}

