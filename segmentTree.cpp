#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int lson(int v) {return v * 2;}
int rson(int v) {return v * 2 + 1;}
const int maxn = 1e5 + 10;
ll seg[maxn * 4], tag[maxn * 4];
ll a[maxn];

void build(int l,int r,int v) {
    if(l == r) {
        seg[v] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, lson(v));
    build(mid + 1, r, rson(v));
    seg[v] = seg[lson(v)] + seg[rson(v)];
}

void pushdown(int l,int r,int v) {
    if(tag[v]) {
        int mid = (l + r) / 2;
        tag[lson(v)] += tag[v];
        tag[rson(v)] += tag[v];
        seg[lson(v)] += (mid - l + 1) * tag[v];
        seg[rson(v)] += (r - mid) * tag[v];
        tag[v] = 0;
    }
}
ll query(int l,int r,int v,int ql,int qr) {
    if(ql <= l&&r <= qr) return seg[v];
    pushdown(l, r, v);
    int mid = (l + r) / 2;
    ll res = 0;
    if(ql <= mid) res += query(l, mid, lson(v), ql, qr);
    if(qr > mid) res += query(mid+1, r, rson(v), ql, qr);
    return res;
}
void update(int l,int r,int v,int ql,int qr,ll k) {
    if(ql <= l&&r <= qr) {
        tag[v] += k;
        seg[v] += (r - l + 1) * k;
        return;
    }
    pushdown(l, r, v);
    int mid = (l + r) / 2;
    if(ql <= mid) update(l, mid, lson(v), ql, qr, k);
    if(qr > mid) update(mid + 1, r, rson(v), ql, qr, k);
    seg[v] = seg[lson(v)] + seg[rson(v)];
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= n;++i) scanf("%d", &a[i]);
    build(1, n, 1);
    while(m--) {
        int cmd, x, y;
        ll k;
        scanf("%d", &cmd);
        if(cmd == 1) {
            scanf("%d%d%lld", &x, &y, &k);
            update(1, n, 1, x, y, k);
        }
        else {
            scanf("%d%d",&x,&y);
            printf("%lld\n", query(1, n, 1, x, y));
        }
    }
    return 0;
}
