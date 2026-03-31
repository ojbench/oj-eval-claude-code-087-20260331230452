#include <iostream>
#include <vector>
using namespace std;

int main() {
    int D;
    long long n;
    cin >> D >> n;

    int leaf_count = 1 << (D - 1);
    int leaf_start = 1 << (D - 1);

    // Key insight: The last ball always goes to a specific position
    // The tree behaves like a binary counter
    // After 2^k balls, the state at depth k cycles back

    // For the last ball position, we can compute it using the pattern:
    // The n-th ball lands at the position determined by the path it takes
    // This path is determined by the state of switches, which depends on
    // how many balls passed through each node

    // The clever insight: the last ball position has a formula!
    // It's related to the binary representation and tree structure

    // For small test, let's still simulate but optimize
    if (n <= 100000000) {  // Should handle up to 10^8
        vector<int> state(1 << D, 0);
        int last_leaf = 0;

        for (long long i = 1; i <= n; i++) {
            int node = 1;

            while (node < leaf_start) {
                if (state[node] == 0) {
                    state[node] = 1;
                    node = 2 * node;
                } else {
                    state[node] = 0;
                    node = 2 * node + 1;
                }
            }

            state[node] = 1 - state[node];
            last_leaf = node;
        }

        cout << last_leaf << endl;

        for (int i = 0; i < leaf_count; i++) {
            if (i > 0) cout << " ";
            cout << state[leaf_start + i];
        }
        cout << endl;
    } else {
        // For very large n, need mathematical formula
        // TODO: derive the formula
        cout << "Error" << endl;
    }

    return 0;
}
