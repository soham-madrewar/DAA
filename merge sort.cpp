#include <iostream>
#include <vector>
using namespace std;


struct Order {
    int id;
    long long timestamp;
};


void merge(vector<Order> &orders, int left, int mid, int right) {
    int i = left;     
    int j = mid + 1;   
    vector<Order> temp;

    
    while (i <= mid && j <= right) {
        if (orders[i].timestamp <= orders[j].timestamp) {
            temp.push_back(orders[i]);
            i++;
        } else {
            temp.push_back(orders[j]);
            j++;
        }
    }

 
    while (i <= mid) {
        temp.push_back(orders[i]);
        i++;
    }

    while (j <= right) {
        temp.push_back(orders[j]);
        j++;
    }

  
    for (int k = 0; k < temp.size(); k++) {
        orders[left + k] = temp[k];
    }
}

    if (left >= right)
        return;

    int mid = (left + right) / 2;


    mergeSort(orders, left, mid);
  
    mergeSort(orders, mid + 1, right);

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

 
    mergeSort(orders, 0, n - 1);

 
    cout << "\nSorted Orders by Timestamp:\n";
    for (int i = 0; i < n; i++) {
        cout << "OrderID: " << orders[i].id
             << " | Timestamp: " << orders[i].timestamp << endl;
    }

    return 0;
}

