#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

struct Movie {
    string title;
    double imdbRating;
    int releaseYear;
    int watchTime; // hours
};

// Compare helper: returns true if movies[a] should come before movies[b]
// choice: 1 -> rating, 2 -> year, 3 -> watchTime
bool comesBefore(const Movie& A, const Movie& B, int choice) {
    if (choice == 1) return A.imdbRating < B.imdbRating;   // ascending by rating
    if (choice == 2) return A.releaseYear < B.releaseYear; // ascending by year
    return A.watchTime < B.watchTime;                      // ascending by watchTime
}

// Selection sort (simple & easy)
void selectionSort(vector<Movie>& movies, int choice) {
    int n = movies.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (comesBefore(movies[j], movies[minIndex], choice)) {
                minIndex = j;
            }
        }
        if (minIndex != i) swap(movies[i], movies[minIndex]);
    }
}

int main() {
    int n;
    cout << "Enter total number of movies: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number. Exiting.\n";
        return 0;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Movie> movies;
    movies.reserve(n);

    for (int i = 0; i < n; ++i) {
        Movie m;
        cout << "Movie " << (i + 1) << " details:\n";
        cout << "Title: ";
        getline(cin, m.title);
        cout << "IMDB Rating: ";
        cin >> m.imdbRating;
        cout << "Release Year: ";
        cin >> m.releaseYear;
        cout << "Watch Time (in hours): ";
        cin >> m.watchTime;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline
        cout << endl;
        movies.push_back(m);
    }

    cout << "Choose parameter to sort by (ascending):\n";
    cout << "1 - IMDB Rating\n2 - Release Year\n3 - Watch Time\n";
    cout << "Your choice: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice, defaulting to IMDB Rating (1).\n";
        choice = 1;
    }
    cout << endl;

    // Sort using selection sort
    selectionSort(movies, choice);

    // Display sorted list
    cout << left << setw(30) << "Title"
         << setw(10) << "Rating"
         << setw(8) << "Year"
         << setw(12) << "Watch(hrs)" << '\n';
    cout << string(60, '-') << '\n';
    for (const auto& m : movies) {
        cout << left << setw(30) << m.title
             << setw(10) << m.imdbRating
             << setw(8) << m.releaseYear
             << setw(12) << m.watchTime << '\n';
    }

    cout << "\nMovies sorted successfully using Selection Sort!\n";
    cout << "Time Complexity: O(n^2) (simple but okay for small lists)\n";

    return 0;
}
