#include <iostream>
#include <vector>
using namespace std;

// Structure to store order details
struct Order {
    int id;
    long long timestamp;
};

// Function to merge two parts
void merge(vector<Order> &orders, int left, int mid, int right) {
    int i = left;       // starting index of left part
    int j = mid + 1;    // starting index of right part
    vector<Order> temp; // temporary array to store merged data

    // Compare and merge both parts
    while (i <= mid && j <= right) {
        if (orders[i].timestamp <= orders[j].timestamp) {
            temp.push_back(orders[i]);
            i++;
        } else {
            temp.push_back(orders[j]);
            j++;
        }
    }

    // Copy remaining elements (if any)
    while (i <= mid) {
        temp.push_back(orders[i]);
        i++;
    }

    while (j <= right) {
        temp.push_back(orders[j]);
        j++;
    }

    // Copy sorted elements back to main array
    for (int k = 0; k < temp.size(); k++) {
        orders[left + k] = temp[k];
    }
}

// Recursive merge sort function
void mergeSort(vector<Order> &orders, int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    // Sort left part
    mergeSort(orders, left, mid);
    // Sort right part
    mergeSort(orders, mid + 1, right);
    // Merge both parts
    merge(orders, left, mid, right);
}

int main() {
    int n;
    cout << "Enter number of orders: ";
    cin >> n;

    vector<Order> orders(n);

    cout << "Enter OrderID and Timestamp:\n";
    for (int i = 0; i < n; i++) {
        cin >> orders[i].id >> orders[i].timestamp;
    }

    // Sort the orders
    mergeSort(orders, 0, n - 1);

    // Display result
    cout << "\nSorted Orders by Timestamp:\n";
    for (int i = 0; i < n; i++) {
        cout << "OrderID: " << orders[i].id
             << " | Timestamp: " << orders[i].timestamp << endl;
    }

    return 0;
}
