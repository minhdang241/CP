#include <vector>
#include <iostream>
using namespace std;
class Solution {
public:
    struct item {
        int m, c;
    };

    struct item_segtree {
        item merge(item i1, item i2) {
            if (i1.m >= i2.m) {
                return item({i2.m, i1.c + i2.c});
            } else {
                return item({i1.m, i1.c + i2.c});
            }
        }

        item NEUTRAL_ELEMENT = item({INT_MAX, 0});

        item single(int v) { return item({v, 1}); }

        int size = 1;
        int cnt = 1;
        vector<item> items;

        void init(int n) {
            while (size < n)
                size *= 2;
            items.assign(2 * size, NEUTRAL_ELEMENT);
        }

        void build(const vector<int>& inputs, int cur_idx, int cur_l,
                   int cur_r) {
            if (cur_r - cur_l == 1) {
                if (cur_l < (int)inputs.size()) {
                    items[cur_idx] = single(inputs[cur_l]);
                }
            } else {
                int mid = (cur_l + cur_r) / 2;
                build(inputs, 2 * cur_idx + 1, cur_l, mid);
                build(inputs, 2 * cur_idx + 2, mid, cur_r);
                items[cur_idx] =
                        merge(items[2 * cur_idx + 1], items[2 * cur_idx + 2]);
            }
        }

        void insert(int val, int cur_idx, int l, int r) {
            if (r - l == 1) {
                items[cur_idx] = single(val);
                ++cnt;
            } else {
                int m = (l + r) / 2;
                if (cnt-1 < m) {
                    insert(val, 2 * cur_idx + 1, l, m);
                } else {
                    insert(val, 2 * cur_idx + 2, m, r);
                }
                items[cur_idx] =
                        merge(items[2 * cur_idx + 1], items[2 * cur_idx + 2]);
            }
        }

        void insert(int val) { insert(val, 0, 0, size); }

        int greaterCount(int cur_val, int l, int r, int cur_idx, int cur_l,
                         int cur_r) {
            if (cur_idx >= items.size()) return 0;
            if (cur_l >= l && cur_r <= r) {
                if (cur_val < items[cur_idx].m) {
                    return items[cur_idx].c;
                }
            }
            int m = (cur_l + cur_r) / 2;
            int c1 = greaterCount(cur_val, l, r, 2 * cur_idx + 1, cur_l, m);
            int c2 = greaterCount(cur_val, l, r, 2 * cur_idx + 2, m, cur_r);
            return c1 + c2;
        }

        int greaterCount(int cur_val) {
            return greaterCount(cur_val, 0, cnt, 0, 0, cnt);
        }
    };

    vector<int> resultArray(vector<int>& nums) {
        int n = nums.size();
        item_segtree a;
        item_segtree b;
        a.init(n);
        a.insert(nums[0]);
        b.init(n);
        b.insert(nums[1]);
        for (int i = 2; i < n; i++) {
            if (a.greaterCount(nums[i]) > b.greaterCount(nums[i])) {
                a.insert(nums[i]);
            } else if (
                    a.greaterCount(nums[i]) <
                    b.greaterCount(nums[i])) {
                b.insert(nums[i]);
            } else {
                if (a.cnt <= b.cnt) {
                    a.insert(nums[i]);
                } else {
                    b.insert(nums[i]);
                }
            }
        }
        vector<int> result(n);
        int j = 2;
        for (int i = a.items.size() - 1; i >= a.items.size() - 1 - a.size; i--) {
            item it = a.items[i];
            if (it.m != INT_MAX) {
//                cout << a.cnt << endl;
//                cout << a.cnt - j << it.m << endl;
                result[a.cnt-j] = it.m;
                ++j;
            }

        }
        j = 3;
        for (int i = b.items.size() - 1; i >= b.items.size() - 1 - b.size; i--) {
            item it = b.items[i];
            if (it.m != INT_MAX) {
//                cout << b.cnt << endl;
//                cout << b.cnt - j << it.m << endl;
                result[a.cnt + b.cnt-j] = it.m;
                ++j;
            }

        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> nums = {11,92,25,90};
    vector<int> result = s.resultArray(nums);
    for (int i: result) {
        cout << i << " ";
    }
    return 0;
}