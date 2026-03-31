#include <iostream>
#include <vector>
using namespace std;

// Count how many balls reach each leaf using recursive distribution
void count_balls(int depth, long long n, int start_idx, vector<long long>& counts) {
    if (depth == 0) {
        // At a leaf
        counts[start_idx] += n;
        return;
    }

    // At this subtree root, distribute n balls between left and right children
    // Balls alternate: 1st goes left, 2nd goes right, 3rd goes left, etc.

    long long left_count = (n + 1) / 2;  // Balls 1, 3, 5, 7, ...
    long long right_count = n / 2;        // Balls 2, 4, 6, 8, ...

    if (left_count > 0) {
        count_balls(depth - 1, left_count, start_idx, counts);
    }
    if (right_count > 0) {
        int right_start = start_idx + (1 << (depth - 1));
        count_balls(depth - 1, right_count, right_start, counts);
    }
}

// Find which leaf the n-th ball reaches using O(D) computation
int find_leaf_optimized(int D, long long n) {
    int node = 1;
    long long ball_at_node = n;  // Which ball (in sequence visiting this node) are we?

    for (int level = 0; level < D - 1; level++) {
        // At this node, we're the ball_at_node-th ball to visit it
        // Determine state: after (ball_at_node-1) balls, state is (ball_at_node-1) % 2

        long long balls_before = ball_at_node - 1;

        if (balls_before % 2 == 0) {
            // State is closed (even number of balls visited), go left
            node = 2 * node;
            // In the left subtree, which ball are we?
            // Left subtree gets balls 1, 3, 5, 7, ... from this node
            // So the ball_at_node-th ball to this node is the ((ball_at_node+1)/2)-th to go left
            ball_at_node = (ball_at_node + 1) / 2;
        } else {
            // State is open (odd number of balls visited), go right
            node = 2 * node + 1;
            // Right subtree gets balls 2, 4, 6, 8, ... from this node
            // So the ball_at_node-th ball to this node is the (ball_at_node/2)-th to go right
            ball_at_node = ball_at_node / 2;
        }
    }

    return node;
}

int main() {
    int D;
    long long n;
    cin >> D >> n;

    int leaf_count = 1 << (D - 1);
    int leaf_start = 1 << (D - 1);

    // Use optimized O(D) algorithm for finding last ball position
    int last_leaf = find_leaf_optimized(D, n);

    // Use optimized O(D * leaf_count) algorithm for counting balls at each leaf
    vector<long long> ball_counts(1 << D, 0);
    count_balls(D - 1, n, leaf_start, ball_counts);

    // Output
    cout << last_leaf << endl;

    for (int i = 0; i < leaf_count; i++) {
        if (i > 0) cout << " ";
        cout << (ball_counts[leaf_start + i] % 2);
    }
    cout << endl;

    return 0;
}
