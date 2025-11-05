// name: soham madrewar
// prn: 123B1F055
// assignment description 
// A devastating flood has hit multiple villages in a remote area, and the government, along

// with NGOs, is organizing an emergency relief operation. A rescue team has a limited-
// capacity boat that can carry a maximum weight of W kilograms. The boat must transport

// critical supplies, including food, medicine, and drinking water, from a relief center to the
// affected villages.
// Each type of relief item has:
// ● A weight (wi) in kilograms.
// ● Utility value (vi) indicating its importance (e.g., medicine has higher value than food).
// ● Some items can be divided into smaller portions (e.g., food and water), while others must
// be taken as a whole (e.g., medical kits).
// As the logistics manager, you must:
// 1. Implement the Fractional Knapsack algorithm to maximize the total utility value of the
// supplies transported.
// 2. Prioritize high-value items while considering weight constraints.
// 3. Allow partial selection of divisible items (e.g., carrying a fraction of food packets).
// 4. Ensure that the boat carries the most critical supplies given its weight limit W.


#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;


struct Item {
    double weight;
    double utility;
    bool divisible;
    double ratio; 
};

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

  
    for (auto& it : items) {
        if (currentWeight + it.weight <= capacity) {
           
            currentWeight += it.weight;
            totalUtility += it.utility;
        } else if (it.divisible) {
           
            double remaining = capacity - currentWeight;
            totalUtility += it.utility * (remaining / it.weight);
            currentWeight += remaining;
            break; 
        } else {
            break; 
        }
    }

    cout << "\nMaximum Utility Boat Can Carry = " << totalUtility << endl;

    cout << "\nTime Complexity: O(n log n) (due to sorting)\n";
    cout << "Space Complexity: O(n)\n";

    return 0;
}


