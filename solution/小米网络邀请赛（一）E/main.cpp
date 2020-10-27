#include <bits/stdc++.h>
#define lson(v) v << 1
#define rson(v) v << 1 | 1
using namespace std;

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int seg[maxn << 2], mx[maxn << 2], mi[maxn << 2], tag[maxn << 2];

void pushdown(int l,int r,int v) {
    if(!tag[v]) return;
    int mid = (l + r) >> 1;
    tag[lson(v)] = tag[rson(v)] = tag[v];
    mi[lson(v)] = mx[lson(v)] = tag[v];
    mi[rson(v)] = mx[rson(v)] = tag[v];
    seg[lson(v)] = tag[v] - mid + 1;
    seg[rson(v)] = tag[v] - r + 1;
    tag[v] = 0;
}

void pushup(int v) {
    seg[v] = min(seg[lson(v)], seg[rson(v)]);
    mi[v] = min(mi[lson(v)], mi[rson(v)]);
    mx[v] = max(mx[lson(v)], mx[rson(v)]);
}
void update(int v,int ql,int qr,int l,int r,int val) {
    if(ql <= l&&r <= qr) {
        if(mi[v] >= val&&mi[v] != INF) return;
        if(mx[v] <= val) {
            tag[v] = mi[v] = mx[v] = val;
            seg[v] = val - r + 1;
            return;
        }
    }
    pushdown(l, r, v);
    int mid = (l + r) >> 1;
    if(ql <= mid) update(lson(v), ql, qr, l, mid, val);
    if(qr > mid) update(rson(v), ql, qr, mid + 1, r, val);
    pushup(v);
}
int ask(int v, int l, int r, int x) {
    if(r <= x) {
        return seg[v];
    }
    int mid = (l + r) >> 1, res = INF;
    pushdown(l, r, v);
    res = min(res, ask(lson(v), l, mid, x));
    if(x > mid) res = min(res, ask(rson(v), mid + 1, r, x));
    pushup(v);
    return res;
}


void build(int l,int r,int v) {
    seg[v] = mi[v] = INF;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, lson(v));
    build(mid + 1, r, rson(v));
}
vector<int> g[maxn];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= n;++i) {
        int x;
        scanf("%d", &x);
        g[x].push_back(i);
    }
    build(1, n, 1);
    int tail = n;
    for(int i = 1;i <= m;++i) {
        tail = min(tail, g[i].back());
        int last = 0;
        for(auto u : g[i]) {
            update(1, last + 1, u, 1, n, u);
            last = u;
        }
        printf("%d%c", ask(1, 1, n, tail),i==m?'\n':' ');
    }
    return 0;
}
