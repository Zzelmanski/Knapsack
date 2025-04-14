#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Function to solve 0/1 Knapsack and return indices of selected items
vector<int> knapsack(int n, int W, const vector<int>& weights, const vector<int>& values) {
    // DP table: dp[i][w] = max value using first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                // Take max of including or excluding the current item
                dp[i][w] = max(dp[i - 1][w],
                    dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
            else {
                // Can't include this item
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Trace back to find which items were selected
    vector<int> selectedItems;
    int w = W;
    for (int i = n; i >= 1; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(i - 1);  // Item i-1 is included
            w -= weights[i - 1];
        }
    }

    return selectedItems; // Contains indices of selected items
}

int main() {
    /*int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter maximum weight capacity: ";
    cin >> W;

    vector<int> weights(n), values(n);

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; ++i) cin >> weights[i];

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; ++i) cin >> values[i];*/
    int n = 200;
    int W = 500;
    vector<int> weights(n), values(n);

    srand(time(0));
    for (int i = 0; i < n; ++i) {
        weights[i] = rand() % 20 + 1;   // weights between 1 and 20
        values[i] = rand() % 100 + 1;  // values between 1 and 100
    }

    // Start timing
    auto start = chrono::high_resolution_clock::now();

    vector<int> result = knapsack(n, W, weights, values);

    // End timing
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Selected item indices: ";
    for (int i : result) cout << i+1 << " ";
    cout << endl;

    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    return 0;
}

