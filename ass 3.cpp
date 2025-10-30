#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Structure for each item
struct Item {
    double weight;
    double utility;
    bool divisible;
    double ratio; // utility/weight
};

// Sort items by ratio (high to low)
bool cmp(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

int main() {
    int n;
    double capacity;
    cout << "Enter boat capacity (kg): ";
    cin >> capacity;

    cout << "Enter number of items: ";
    cin >> n;
    cout << endl;

    vector<Item> items(n);

    // Input item details
    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << ":\n";
        cout << "Weight (kg): ";
        cin >> items[i].weight;
        cout << "Utility value: ";
        cin >> items[i].utility;
        cout << "Divisible (1 = Yes, 0 = No): ";
        cin >> items[i].divisible;
        items[i].ratio = items[i].utility / items[i].weight;
        cout << endl;
    }

    // Sort items by best utility-to-weight ratio
    sort(items.begin(), items.end(), cmp);

    cout << fixed << setprecision(2);
    cout << "\nItems sorted by utility/weight ratio:\n";
    cout << left << setw(10) << "Weight" 
         << setw(10) << "Utility" 
         << setw(10) << "Divisible" 
         << setw(15) << "U/W Ratio" << "\n";

    for (auto& it : items) {
        cout << left << setw(10) << it.weight
             << setw(10) << it.utility
             << setw(10) << (it.divisible ? "Yes" : "No")
             << setw(15) << it.ratio << "\n";
    }

    double totalUtility = 0.0;
    double currentWeight = 0.0;

    // Pick items greedily
    for (auto& it : items) {
        if (currentWeight + it.weight <= capacity) {
            // Take whole item
            currentWeight += it.weight;
            totalUtility += it.utility;
        } else if (it.divisible) {
            // Take fraction if allowed
            double remaining = capacity - currentWeight;
            totalUtility += it.utility * (remaining / it.weight);
            currentWeight += remaining;
            break; // boat full
        } else {
            break; // cannot take non-divisible partially
        }
    }

    cout << "\nMaximum Utility Boat Can Carry = " << totalUtility << endl;

    cout << "\nTime Complexity: O(n log n) (due to sorting)\n";
    cout << "Space Complexity: O(n)\n";

    return 0;
}
