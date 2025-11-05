// name: soham madrewar
// prn: 123B1F055
// assignment description 
// quick sort


#include <iostream>
#include <vector>
using namespace std;

struct Movie {
    string title;
    double rating;
    int year;
    long long watchtime;
};


bool compareMovies(const Movie &a, const Movie &b, int choice) {
    if (choice == 1) return a.rating < b.rating;          
    if (choice == 2) return a.year < b.year;             
    return a.watchtime < b.watchtime;                    
}

int partition(vector<Movie> &arr, int low, int high, int choice) {
    Movie pivot = arr[high];    
    int i = low - 1;            

    for (int j = low; j <= high - 1; ++j) {
        if (compareMovies(arr[j], pivot, choice)) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(vector<Movie> &arr, int low, int high, int choice) {
    if (low < high) {
        int p = partition(arr, low, high, choice);
        quicksort(arr, low, p - 1, choice);
        quicksort(arr, p + 1, high, choice);
    }
}

int main() {
    int n;
    cout << "Enter number of movies: ";
    cin >> n;

    vector<Movie> movies(n);
    cout << "Enter details (Title Rating Year WatchTime) one per line:\n";
    for (int i = 0; i < n; ++i) {
        cin >> movies[i].title >> movies[i].rating >> movies[i].year >> movies[i].watchtime;
    }

    int choice;
    cout << "\nSort by:\n1. IMDB Rating\n2. Release Year\n3. Watch Time Popularity\nEnter choice: ";
    cin >> choice;

    if (n > 0) quicksort(movies, 0, n - 1, choice);

    cout << "\nSorted Movies:\n";
    for (const auto &m : movies) {
        cout << m.title << " | Rating: " << m.rating
             << " | Year: " << m.year
             << " | WatchTime: " << m.watchtime << '\n';
    }

    return 0;
}


