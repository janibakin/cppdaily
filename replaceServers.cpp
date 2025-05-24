#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> getTotalRequests(vector<int> server, vector<int> replaceId, vector<int> newId) {
    unordered_map<int, int> serverCount;
    long long total = 0;

    // Initialize server counts and total requests
    for (int id : server) {
        serverCount[id]++;
        total += id;
    }

    vector<int> results;

    // Apply each day's replacement
    for (int i = 0; i < replaceId.size(); ++i) {
        int oldId = replaceId[i];
        int newServerId = newId[i];

        if (serverCount[oldId] > 0) {
            int count = serverCount[oldId];
            total -= (long long)oldId * count;
            total += (long long)newServerId * count;
            serverCount[newServerId] += count;
            serverCount[oldId] = 0; // all oldId servers are replaced
        }

        results.push_back((int)total);
    }

    return results;
}

int main() {
    // Sample Test
    vector<int> server = {3, 3, 7, 3};
    vector<int> replaceId = {7, 3};
    vector<int> newId = {2, 1};

    vector<int> result = getTotalRequests(server, replaceId, newId);
    for (int total : result) {
        cout << total << endl;
    }

    return 0;
}
