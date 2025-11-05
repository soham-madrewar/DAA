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
// 1. Model the problem as a graph and implement a graph coloring algorithm (e.g., Greedy
// Coloring or Backtracking).
// 2. Minimize the number of colors (exam slots) needed while ensuring conflict-free
// scheduling.
// 3. Handle large datasets with thousands of courses and students, optimizing performance.
// 4. Compare the efficiency of Greedy Coloring, DSATUR, and Welsh-Powell algorithms
// for better scheduling.
// Extend the solution to include room allocation constraints where exams in the same slot should
// fit within available classrooms.

#include <bits/stdc++.h>
using namespace std;

class ExamScheduler {
private:
    int numCourses;
    vector<vector<int>> adj;                
    vector<int> color;                  

public:
    ExamScheduler(int n) : numCourses(n) {
        adj.resize(n);
        color.assign(n, -1);
        courseSize.assign(n, 0);
    }

    void addEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= numCourses || v >= numCourses) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void setCourseSize(int course, int size) {
        if (course >= 0 && course < numCourses) courseSize[course] = size;
    }

    int greedyColoring() {
        color.assign(numCourses, -1);
        for (int u = 0; u < numCourses; ++u) {
            vector<bool> used(numCourses, false);
            for (int v : adj[u]) {
                if (color[v] != -1) used[color[v]] = true;
            }
            int c = 0;
            while (c < numCourses && used[c]) ++c;
            color[u] = c;
        }
        return *max_element(color.begin(), color.end()) + 1;
    }

    
    int welshPowellColoring() {
        color.assign(numCourses, -1);
        vector<int> order(numCourses);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b){
            return adj[a].size() > adj[b].size();
        });

        int numColors = 0;
        for (int u : order) {
            vector<bool> used(numCourses, false);
            for (int v : adj[u]) if (color[v] != -1) used[color[v]] = true;
            int c = 0;
            while (c < numCourses && used[c]) ++c;
            color[u] = c;
            numColors = max(numColors, c + 1);
        }
        return numColors;
    }

    int dsaturColoring() {
        color.assign(numCourses, -1);
        vector<int> degree(numCourses, 0);
        vector<unordered_set<int>> neighborColors(numCourses);

        for (int i = 0; i < numCourses; ++i) degree[i] = adj[i].size();

        
        int start = max_element(degree.begin(), degree.end()) - degree.begin();
        color[start] = 0;

        
        for (int v : adj[start]) neighborColors[v].insert(0);

        int colored = 1;
        while (colored < numCourses) {
            int next = -1, bestSat = -1, bestDeg = -1;
            for (int i = 0; i < numCourses; ++i) {
                if (color[i] != -1) continue;
                int sat = (int)neighborColors[i].size();
                if (sat > bestSat || (sat == bestSat && degree[i] > bestDeg)) {
                    bestSat = sat;
                    bestDeg = degree[i];
                    next = i;
                }
         
            vector<bool> used(numCourses, false);
            for (int v : adj[next]) if (color[v] != -1) used[color[v]] = true;
            int c = 0;
            while (c < numCourses && used[c]) ++c;
            color[next] = c;

           
            for (int v : adj[next]) if (color[v] == -1) neighborColors[v].insert(c);

            colored++;
        }
        return *max_element(color.begin(), color.end()) + 1;
    }

    void allocateRooms(int numRooms, int roomCapacity) {
        int numColors = *max_element(color.begin(), color.end()) + 1;
        vector<vector<int>> slotCourses(numColors);
        for (int i = 0; i < numCourses; ++i) slotCourses[color[i]].push_back(i);

        cout << "\nRoom Allocation (room capacity = " << roomCapacity << "):\n";
        for (int s = 0; s < numColors; ++s) {
            cout << "Slot " << s << ":\n";
            if (slotCourses[s].empty()) {
                cout << "  (no courses in this slot)\n";
                continue;
            }
            int currentRoom = 1;
            int usedCapacity = 0;
            for (int course : slotCourses[s]) {
                int sz = courseSize[course];
                if (usedCapacity + sz > roomCapacity) {
                    currentRoom++;
                    usedCapacity = 0;
                }
                cout << "  Room " << currentRoom << " -> Course " << course
                     << " (" << sz << " students)\n";
                usedCapacity += sz;
            }
        }
    }

    void printAssignments() {
        cout << "\nCourse -> Slot assignments:\n";
        for (int i = 0; i < numCourses; ++i) {
            cout << "Course " << i << " -> Slot " << color[i]
                 << " (students: " << courseSize[i] << ")\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 6;
    ExamScheduler scheduler(n);


    scheduler.addEdge(0, 1);
    scheduler.addEdge(0, 2);
    scheduler.addEdge(1, 2);
    scheduler.addEdge(1, 3);
    scheduler.addEdge(3, 4);
    scheduler.addEdge(4, 5);


    scheduler.setCourseSize(0, 80);
    scheduler.setCourseSize(1, 50);
    scheduler.setCourseSize(2, 40);
    scheduler.setCourseSize(3, 60);
    scheduler.setCourseSize(4, 90);
    scheduler.setCourseSize(5, 30);

    int gSlots = scheduler.greedyColoring();
    cout << "Greedy Coloring: " << gSlots << " slots\n";
    scheduler.printAssignments(); 

    int wpSlots = scheduler.welshPowellColoring();
    cout << "\nWelsh–Powell Coloring: " << wpSlots << " slots\n";
    scheduler.printAssignments(); 

    int dSlots = scheduler.dsaturColoring();
    cout << "\nDSATUR Coloring: " << dSlots << " slots\n";
    scheduler.printAssignments(); 

    scheduler.allocateRooms(3, 100);

    return 0;
}


