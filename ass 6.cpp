// name: soham madrewar
// prn: 123B1F055
// assignment description 
// A massive earthquake has struck a remote region, and a relief organization is transporting
// essential supplies to the affected area. The organization has a limited-capacity relief truck that
// can carry a maximum weight of W kg. They have N different types of essential items, each
// with a specific weight and an associated utility value (importance in saving lives and meeting
// urgent needs).
// Since the truck has limited capacity, you must decide which items to include to maximize the
// total utility value while ensuring the total weight does not exceed the truck's limit.
// Your Task as a Logistics Coordinator:
// 1. Model this problem using the 0/1 Knapsack approach, where each item can either be
// included in the truck (1) or not (0).
// 2. Implement an algorithm to find the optimal set of items that maximizes utility while
// staying within the weight constraint.
// 3. Analyze the performance of different approaches (e.g., Brute Force, Dynamic
// Programming, and Greedy Algorithms) for solving this problem efficiently.
// 4. Optimize for real-world constraints, such as perishable items (medicines, food) having
// priority over less critical supplies.
// Extend the model to consider multiple trucks or real-time decision-making for dynamic supply
// chain management.


#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Item {
    int weight;
    int utility;
};

int main() {
    int n, capacity;
    cout << "Enter the number of items: ";
    cin >> n;
    if (n <= 0) return 0;

    cout << "Enter the truck capacity: ";
    cin >> capacity;
    if (capacity <= 0) {
        cout << "Capacity must be positive.\n";
        return 0;
    }

    vector<Item> items(n);
    cout << "Enter weight and utility for each item:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> items[i].weight;
        cout << "Item " << i + 1 << " - Utility: ";
        cin >> items[i].utility;
    }

    // dp[i][w] = max utility using first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    // keep[i][w] = true if we take item (i-1) in optimal for dp[i][w]
    vector<vector<char>> keep(n + 1, vector<char>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        int wt = items[i - 1].weight;
        int val = items[i - 1].utility;
        for (int w = 0; w <= capacity; ++w) {
            // Option 1: don't take item i
            dp[i][w] = dp[i - 1][w];
            // Option 2: take item i (if fits)
            if (wt <= w) {
                int takeVal = val + dp[i - 1][w - wt];
                if (takeVal > dp[i][w]) {
                    dp[i][w] = takeVal;
                    keep[i][w] = 1; // mark that we took item i-1
                }
            }
        }
    }

    int maxUtility = dp[n][capacity];
    cout << "\nMax utility = " << maxUtility << "\n";

    // Reconstruct chosen items
    vector<int> chosen;
    int w = capacity;
    for (int i = n; i >= 1; --i) {
        if (keep[i][w]) {
            chosen.push_back(i - 1); // store index of chosen item
            w -= items[i - 1].weight;
        }
    }

    if (chosen.empty()) {
        cout << "No items chosen.\n";
    } else {
        cout << "Items chosen (index, weight, utility):\n";
        // print in original input order
        for (int i = chosen.size() - 1; i >= 0; --i) {
            int idx = chosen[i];
            cout << "Item " << (idx + 1)
                 << " - Weight: " << items[idx].weight
                 << " Utility: " << items[idx].utility << "\n";
        }
    }

    return 0;
}

