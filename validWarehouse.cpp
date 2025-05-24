#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

bool isValidWarehouse(int x, const vector<int>& center, int half_d) {
    long long dist = 0;
    for (int c : center) {
        dist += abs((long long)x - c);
    }
    return dist <= half_d;
}

int countValidWarehouses(const vector<int>& center, int d) {
    int leftMost = INT_MAX;
    int rightMost = INT_MIN;
    int half_d = d / 2;

    // Binary search for leftmost valid position
    int left = -1e9, right = 1e9;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (isValidWarehouse(mid, center, half_d)) {
            leftMost = min(leftMost, mid);
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    // Binary search for rightmost valid position
    left = -1e9, right = 1e9;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (isValidWarehouse(mid, center, half_d)) {
            rightMost = max(rightMost, mid);
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (leftMost == INT_MAX || rightMost == INT_MIN) return 0;
    return rightMost - leftMost + 1;
}

int main() {
    vector<int> centers = {-2, 1, 0};
    int d = 8;
    int result = countValidWarehouses(centers, d);
    cout << "Number of valid warehouse positions: " << result << endl;  // Output: 3
    return 0;
}
