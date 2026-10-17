#include <bits/stdc++.h>
using namespace std;

class CountMinSketch {
private:
    int d, w;
    vector<vector<int>> table;
    vector<hash<string>> hashFuncs;

    int hashFunction(const string &item, int i) {
        // Simple hash mixing with seed i
        return (hash<string>()(item) + i * 101) % w;
    }

public:
    CountMinSketch(int depth, int width) : d(depth), w(width) {
        table.assign(d, vector<int>(w, 0));
    }

    void update(const string &item, int count = 1) {
        for (int i = 0; i < d; i++) {
            int idx = hashFunction(item, i);
            table[i][idx] += count;
        }
    }

    int estimate(const string &item) {
        int result = INT_MAX;
        for (int i = 0; i < d; i++) {
            int idx = hashFunction(item, i);
            result = min(result, table[i][idx]);
        }
        return result;
    }
};

int main() {
    CountMinSketch cms(5, 100); // depth=5, width=100
    cms.update("apple");
    cms.update("apple");
    cms.update("banana");

    cout << "apple count ≈ " << cms.estimate("apple") << endl;
    cout << "banana count ≈ " << cms.estimate("banana") << endl;
    cout << "orange count ≈ " << cms.estimate("orange") << endl;
}
