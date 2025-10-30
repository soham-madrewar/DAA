#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

// Structure for order details
struct Order {
    int orderID;
    int timestamp;
    string customer;
};

// Function to merge two sorted parts
void merge(vector<Order>& orders, int left, int mid, int right) {
    vector<Order> temp;
    int i = left;      // starting index for left half
    int j = mid + 1;   // starting index for right half

    // Merge both halves based on timestamp
    while (i <= mid && j <= right) {
        if (orders[i].timestamp <= orders[j].timestamp)
            temp.push_back(orders[i++]);
        else
            temp.push_back(orders[j++]);
    }

    // Copy remaining elements from left half
    while (i <= mid)
        temp.push_back(orders[i++]);

    // Copy remaining elements from right half
    while (j <= right)
        temp.push_back(orders[j++]);

    // Put sorted elements back into original vector
    for (int k = 0; k < temp.size(); k++)
        orders[left + k] = temp[k];
}

// Recursive merge sort function
void mergeSort(vector<Order>& orders, int left, int right) {
    if (left >= right) return;  // base case
    int mid = (left + right) / 2;
    mergeSort(orders, left, mid);
    mergeSort(orders, mid + 1, right);
    merge(orders, left, mid, right);
}

int main() {
    // Sample order data
    vector<Order> orders = {
        {101, 982634, "soham"},
        {102, 725722, "raj"},
        {103, 927365, "rohit"},
        {104, 273627, "abhishek"},
        {105, 362526, "mohit"}
    };

    // Start timer
    auto start = high_resolution_clock::now();

    // Perform sorting
    mergeSort(orders, 0, orders.size() - 1);

    // End timer
    auto end = high_resolution_clock::now();

    duration<double> time_taken = end - start;

    // Display results
    cout << "Orders sorted successfully!\n";
    cout << "Time taken: " << time_taken.count() << " seconds\n\n";

    cout << " Sorted Order List:\n";
    for (auto& o : orders) {
        cout << "Order ID: " << o.orderID
             << " | Timestamp: " << o.timestamp
             << " | Customer: " << o.customer << endl;
    }

    cout << "\n Time Complexity: O(n log n)\n";
    cout << " Space Complexity: O(n)\n";

    return 0;
}
