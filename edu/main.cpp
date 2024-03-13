#include "segment_tree/segment_tree.h"
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    segtree st;
    st.init(n);
    vector<int> inputs;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        inputs.push_back(x);
    }
    st.build(inputs);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.sum(l, r) << "\n";
        }
    }
}