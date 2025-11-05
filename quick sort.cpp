#include <iostream>
#include <vector>
using namespace std;

struct Movie {
    string title;
    double rating;
    int year;
    long long watchtime;
};

// Compare two movies based on user's choice
bool compareMovies(const Movie &a, const Movie &b, int choice) {
    if (choice == 1) return a.rating < b.rating;          // sort by rating (small -> big)
    if (choice == 2) return a.year < b.year;              // sort by year (old -> new)
    return a.watchtime < b.watchtime;                     // sort by watchtime (less -> more)
}

// Lomuto partition (simple)
int partition(vector<Movie> &arr, int low, int high, int choice) {
    Movie pivot = arr[high];    // pivot = last element
    int i = low - 1;            // place for swapping

    for (int j = low; j <= high - 1; ++j) {
        if (compareMovies(arr[j], pivot, choice)) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort recursive
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
