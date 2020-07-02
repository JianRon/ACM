#include<bits/stdc++.h>
#define lson(v) v << 1
#define rson(v) v << 1 | 1
using namespace std;

const int maxn = 5e4 + 10;
int a[maxn], n;
struct node {
    int mx, mxl, mxr, sum;
}seg[maxn << 2];
void merge(node& o, const node& l, const node& r) {
    o.sum = l.sum + r.sum;
    o.mxl = max(l.mxl, l.sum + r.mxl);
    o.mxr = max(r.mxr, r.sum + l.mxr);
    o.mx  = max({l.mx, r.mx, l.mxr + r.mxl});
}

void build(int l, int r, int v) {
    if(l == r) {
        seg[v].mx = seg[v].mxl = seg[v].mxr = seg[v].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, lson(v));
    build(mid + 1, r, rson(v));
    merge(seg[v], seg[lson(v)], seg[rson(v)]);
}

node ask(int l,int r,int v,int ql,int qr) {
    if(ql <= l&&r <= qr) {
        return seg[v];
    }
    int mid = (l + r) >> 1;
    node res;
    if(ql <= mid&&qr > mid) {
        merge(res,
              ask(l, mid, lson(v), ql, qr),
              ask(mid + 1, r, rson(v), ql, qr));
    }
    else if(ql <= mid) {
        res = ask(l, mid, lson(v), ql, qr);
    }
    else {
        res = ask(mid + 1, r, rson(v), ql, qr);
    }

    return res;
}

int main() {
    scanf("%d", &n);
    for(int i = 1;i <= n;++i) {
        scanf("%d", &a[i]);
    }
    build(1, n, 1);
    int m;
    scanf("%d",&m);
    while(m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", ask(1, n, 1, l, r).mx);
    }
    return 0;
}
