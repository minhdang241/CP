#include "segment_tree/segment_tree.h"
#include <iostream>

using namespace std;

int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    item_segtree st;
    st.init(n);
    vector<int> a(n);
    for  (int i = 0; i < a.size(); i++) {
        cin >> a[i];
    }
    st.build(a);
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
            item i = st.calc(l, r);
            cout << i.m << " " <<  i.c << "\n";
        }
    }
    return 0;

}