#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "numeric"

using namespace std;

// Function to count substrings with at least one '#'
int countSubstringsWithHash(const string& s) {
    int n = s.length();
    int totalSubstrings = n * (n + 1) / 2;
    int withoutHash = 0;
    int len = 0;

    for (char c : s) {
        if (c != '#') {
            ++len;
        } else {
            withoutHash += len * (len + 1) / 2;
            len = 0;
        }
    }
    // Add last segment if it doesn't end with '#'
    withoutHash += len * (len + 1) / 2;

    return totalSubstrings - withoutHash;
}

int passwordRecoveryTime(string s, vector<int> targetIndex, int M) {
    int seconds = 0;

    for (int i = 0; i < targetIndex.size(); ++i) {
        ++seconds;
        int idx = targetIndex[i] - 1;  // convert to 0-based index
        s[idx] = '#';

        int substrWithHash = countSubstringsWithHash(s);
        if (substrWithHash >= M) {
            return seconds;
        }
    }
    return -1;  // if it never exceeds M
}

int main() {
    string s = "bcced";
    vector<int> targetIndex = {2, 3, 1, 4, 5};
    int M = 10;

    assert(passwordRecoveryTime(s, targetIndex, M) == 2);

    return 0;
}
