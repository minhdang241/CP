//
// Created by DANG BA MINH on 13/03/2024.
//

#ifndef CP_SEGMENT_TREE_H
#define CP_SEGMENT_TREE_H

#include <vector>

using namespace std;

struct segtree {
    int size = 1;
    vector<long long> sums;

    void init(int n) {
        while (size < n) size *= 2;
        sums.assign(2 * size, 0LL);
    }

    void build(const vector<int> &inputs, int cur_idx, int cur_l, int cur_r) {
        if (cur_r - cur_l == 1) {
            if (cur_l < (int) inputs.size()) {
                sums[cur_idx] = inputs[cur_l];
            }
        } else {
            int mid = (cur_l + cur_r) / 2;
            build(inputs, 2 * cur_idx + 1, cur_l, mid);
            build(inputs, 2 * cur_idx + 2, mid, cur_r);
            sums[cur_idx] = sums[2 * cur_idx + 1] + sums[2 * cur_idx + 2];
        }
    }

    void build(vector<int> &inputs) {
        build(inputs, 0, 0, size);
    }

    void set(int idx, int val, int cur_idx, int l, int r) {
        if (r - l == 1) {
            sums[cur_idx] = val;
        } else {
            int m = (l + r) / 2;
            if (idx < m) {
                set(idx, val, 2 * cur_idx + 1, l, m);
            } else {
                set(idx, val, 2 * cur_idx + 2, m, r);
            }
            sums[cur_idx] = sums[2 * cur_idx + 1] + sums[2 * cur_idx + 2];
        }

    }

    void set(int idx, int val) {
        set(idx, val, 0, 0, size);
    }

    long long sum(int l, int r, int cur_idx, int cur_l, int cur_r) {
        if (cur_l >= r || l >= cur_r) {
            return 0;
        }
        if (cur_l >= l && cur_r <= r) {
            return sums[cur_idx];
        }
        int m = (cur_l + cur_r) / 2;
        long s1 = sum(l, r, 2 * cur_idx + 1, cur_l, m);
        long s2 = sum(l, r, 2 * cur_idx + 2, m, cur_r);
        return s1 + s2;
    }

    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }

};

#endif //CP_SEGMENT_TREE_H
