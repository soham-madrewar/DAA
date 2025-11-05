// name: soham madrewar
// prn: 123B1F055
// assignment description 
// Design and implement a sorting algorithm using Merge Sort to efficiently arrange customer
// orders based on their timestamps. The solution should handle a large dataset (up to 1 million
// orders) with minimal computational overhead. Additionally, analyze the time complexity and
// compare it with traditional sorting techniques.

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;


struct Order {
    int orderID;
    int timestamp;
    string customer;
};


void merge(vector<Order>& orders, int left, int mid, int right) {
    vector<Order> temp;
    int i = left;      
    int j = mid + 1;   

    
    while (i <= mid && j <= right) {
        if (orders[i].timestamp <= orders[j].timestamp)
            temp.push_back(orders[i++]);
        else
            temp.push_back(orders[j++]);
    }

    
    while (i <= mid)
        temp.push_back(orders[i++]);

 
    while (j <= right)
        temp.push_back(orders[j++]);

    
    for (int k = 0; k < temp.size(); k++)
        orders[left + k] = temp[k];
}


void mergeSort(vector<Order>& orders, int left, int right) {
    if (left >= right) return;  // base case
    int mid = (left + right) / 2;
    mergeSort(orders, left, mid);
    mergeSort(orders, mid + 1, right);
    merge(orders, left, mid, right);
}

int main() {
    
    vector<Order> orders = {
        {101, 982634, "soham"},
        {102, 725722, "raj"},
        {103, 927365, "rohit"},
        {104, 273627, "abhishek"},
        {105, 362526, "mohit"}
    };

   
    auto start = high_resolution_clock::now();

    
    mergeSort(orders, 0, orders.size() - 1);

    
    auto end = high_resolution_clock::now();

    duration<double> time_taken = end - start;

    
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

