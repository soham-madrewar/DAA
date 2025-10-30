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
