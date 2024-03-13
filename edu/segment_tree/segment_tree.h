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

struct min_segtree {
    int size = 1;
    vector<int> mins;

    void init(int n) {
        while (size < n) size *= 2;
        mins.assign(2 * size, 0LL);
    }

    void build(const vector<int> &inputs, int cur_idx, int cur_l, int cur_r) {
        if (cur_r - cur_l == 1) {
            if (cur_l < (int) inputs.size()) {
                mins[cur_idx] = inputs[cur_l];
            }
        } else {
            int mid = (cur_l + cur_r) / 2;
            build(inputs, 2 * cur_idx + 1, cur_l, mid);
            build(inputs, 2 * cur_idx + 2, mid, cur_r);
            mins[cur_idx] = min(mins[2 * cur_idx + 1], mins[2 * cur_idx + 2]);
        }
    }

    void build(vector<int> &inputs) {
        build(inputs, 0, 0, size);
    }

    void set(int idx, int val, int cur_idx, int l, int r) {
        if (r - l == 1) {
            mins[cur_idx] = val;
        } else {
            int m = (l + r) / 2;
            if (idx < m) {
                set(idx, val, 2 * cur_idx + 1, l, m);
            } else {
                set(idx, val, 2 * cur_idx + 2, m, r);
            }
            mins[cur_idx] = min(mins[2 * cur_idx + 1], mins[2 * cur_idx + 2]);
        }

    }

    void set(int idx, int val) {
        set(idx, val, 0, 0, size);
    }

    int calc(int l, int r, int cur_idx, int cur_l, int cur_r) {
        if (cur_l >= r || l >= cur_r) {
            return INT_MAX;
        }
        if (cur_l >= l && cur_r <= r) {
            return mins[cur_idx];
        }
        int m = (cur_l + cur_r) / 2;
        int s1 = calc(l, r, 2 * cur_idx + 1, cur_l, m);
        int s2 = calc(l, r, 2 * cur_idx + 2, m, cur_r);
        return min(s1, s2);
    }

    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

struct item {
    int m, c;
};

struct item_segtree {
    item merge(item i1, item i2) {
        if (i1.m < i2.m) {
            return item({i1.m, i1.c});
        } else if (i1.m > i2.m) {
            return item({i2.m, i2.c});
        } else {
            return item({i1.m, i1.c + i2.c});
        }
    }

    item NEUTRAL_ELEMENT = item({INT_MAX, 0});

    item single(int v) {
        return item({v, 1});
    }

    int size = 1;
    vector<item> items;

    void init(int n) {
        while (size < n) size *= 2;
        items.assign(2 * size, NEUTRAL_ELEMENT);
    }

    void build(const vector<int> &inputs, int cur_idx, int cur_l, int cur_r) {
        if (cur_r - cur_l == 1) {
            if (cur_l < (int) inputs.size()) {
                items[cur_idx] = single(inputs[cur_l]);
            }
        } else {
            int mid = (cur_l + cur_r) / 2;
            build(inputs, 2 * cur_idx + 1, cur_l, mid);
            build(inputs, 2 * cur_idx + 2, mid, cur_r);
            items[cur_idx] = merge(items[2 * cur_idx + 1], items[2 * cur_idx + 2]);
        }
    }

    void build(vector<int> &inputs) {
        build(inputs, 0, 0, size);
    }

    void set(int idx, int val, int cur_idx, int l, int r) {
        if (r - l == 1) {
            items[cur_idx] = single(val);
        } else {
            int m = (l + r) / 2;
            if (idx < m) {
                set(idx, val, 2 * cur_idx + 1, l, m);
            } else {
                set(idx, val, 2 * cur_idx + 2, m, r);
            }
            items[cur_idx] = merge(items[2 * cur_idx + 1], items[2 * cur_idx + 2]);
        }

    }

    void set(int idx, int val) {
        set(idx, val, 0, 0, size);
    }

    item calc(int l, int r, int cur_idx, int cur_l, int cur_r) {
        if (cur_l >= r || l >= cur_r) {
            return NEUTRAL_ELEMENT;
        }
        if (cur_l >= l && cur_r <= r) {
            return items[cur_idx];
        }
        int m = (cur_l + cur_r) / 2;
        item i1 = calc(l, r, 2 * cur_idx + 1, cur_l, m);
        item i2 = calc(l, r, 2 * cur_idx + 2, m, cur_r);
        return merge(i1, i2);
    }

    item calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

#endif //CP_SEGMENT_TREE_H
