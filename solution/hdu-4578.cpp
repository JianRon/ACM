#include<bits/stdc++.h>
#define lson(v) v << 1
#define rson(v) v << 1 | 1
#define mid (l + r >> 1)
using namespace std;

const int mod = 10007;
const int maxn = 1e5 + 10;
int n, m;
int add(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
int mul(int a, int b) {return a * b % mod;}
struct node {
    int st, add, mul, sum[4];
}seg[maxn << 2];
void modif_set(int l,int r,int v,int c) {
    seg[v].st = c;
    seg[v].mul = 1;
    seg[v].add = 0;
    seg[v].sum[1] = mul(r - l + 1, c);
    seg[v].sum[2] = mul(r - l + 1, mul(c, c));
    seg[v].sum[3] = mul(r - l + 1, mul(c, mul(c, c)));
}

void modif_add(int l,int r,int v,int c) {
    if(seg[v].st) {
        if(l != r) {
            modif_set(l, mid, lson(v), seg[v].st);
            modif_set(mid + 1, r, rson(v), seg[v].st);
        }
        seg[v].st = 0;
    }
    seg[v].add = add(seg[v].add, c);
    seg[v].sum[3] = add(seg[v].sum[3], mul(mul(3, seg[v].sum[2]), c));
    seg[v].sum[3] = add(seg[v].sum[3], mul(mul(3, seg[v].sum[1]), mul(c, c)));
    seg[v].sum[3] = add(seg[v].sum[3], mul(r - l + 1, mul(mul(c,c),c)));
    seg[v].sum[2] = add(seg[v].sum[2], mul(c, mul(2, seg[v].sum[1])));
    seg[v].sum[2] = add(seg[v].sum[2], mul(r - l + 1, mul(c, c)));
    seg[v].sum[1] = add(seg[v].sum[1], mul(r - l + 1, c));
}
void modif_mul(int l,int r,int v,int c) {
    if(seg[v].st) {
        if(l != r) {
            modif_set(l, mid, lson(v), seg[v].st);
            modif_set(mid + 1, r, rson(v), seg[v].st);
        }
        seg[v].st = 0;
    }
    seg[v].sum[1] = mul(seg[v].sum[1], c);
    seg[v].sum[2] = mul(seg[v].sum[2], mul(c, c));
    seg[v].sum[3] = mul(seg[v].sum[3], mul(c, mul(c, c)));
    seg[v].add = mul(seg[v].add, c);
    seg[v].mul = mul(seg[v].mul, c);
}

void pushdown(int l, int r, int v) {
    if(seg[v].st) {
        modif_set(l, mid, lson(v), seg[v].st);
        modif_set(mid + 1, r, rson(v), seg[v].st);
        seg[v].st = 0;
    }
    else {
        if(seg[v].mul != 1) {
            modif_mul(l, mid, lson(v), seg[v].mul);
            modif_mul(mid + 1, r, rson(v), seg[v].mul);
            seg[v].mul = 1;
        }
        if(seg[v].add) {
            modif_add(l, mid, lson(v),seg[v].add);
            modif_add(mid + 1, r, rson(v), seg[v].add);
            seg[v].add = 0;
        }
    }
}

void build(int l,int r,int v) {
    seg[v].mul = 1;
    seg[v].sum[1] = seg[v].sum[2] = seg[v].sum[3] = 0;
    seg[v].add = seg[v].st = 0;
    if(l == r) return;
    build(l, mid, lson(v));
    build(mid + 1, r, rson(v));
}
void pushup(int v) {
    for(int i = 1;i <= 3;++i)
        seg[v].sum[i] = add(seg[lson(v)].sum[i], seg[rson(v)].sum[i]);
}

void update_add(int l,int r,int v,int ql,int qr,int c) {
    if(ql <= l&&r <= qr) {
        modif_add(l, r, v, c);
        return;
    }
    pushdown(l, r, v);
    if(ql <= mid) update_add(l, mid, lson(v), ql, qr, c);
    if(qr > mid) update_add(mid + 1, r, rson(v), ql, qr, c);
    pushup(v);
}
void update_mul(int l,int r,int v,int ql,int qr,int c) {
    if(ql <= l&&r <= qr) {
        modif_mul(l, r, v, c);
        return;
    }
    pushdown(l, r, v);
    if(ql <= mid) update_mul(l, mid, lson(v), ql, qr, c);
    if(qr > mid) update_mul(mid + 1, r, rson(v), ql, qr, c);
    pushup(v);
}
void update_set(int l,int r,int v,int ql,int qr,int c) {
    if(ql <= l&&r <= qr) {
        modif_set(l, r, v, c);
        return;
    }
    pushdown(l, r, v);
    if(ql <= mid) update_set(l, mid, lson(v), ql, qr, c);
    if(qr > mid) update_set(mid + 1, r, rson(v), ql, qr, c);
    pushup(v);
}
int ask(int l, int r,int v,int ql,int qr, int c) {
    if(ql <=l &&r <= qr) return seg[v].sum[c];
    pushdown(l, r, v);
    int res = 0;
    if(ql <= mid) res = add(res, ask(l, mid, lson(v), ql, qr, c));
    if(qr > mid) res = add(res, ask(mid + 1, r, rson(v), ql, qr, c));
    pushup(v);
    return res;
}

int main() {
    while(scanf("%d%d", &n, &m)&&n&&m) {
        build(1, n, 1);
        while(m--) {
            int cmd, l, r, c;
            scanf("%d%d%d%d", &cmd, &l, &r, &c);
            if(cmd == 1) {
                update_add(1, n, 1, l, r, c);
            }
            else if(cmd == 2) {
                update_mul(1, n, 1, l, r, c);
            }
            else if(cmd == 3) {
                update_set(1, n, 1, l, r, c);
            }
            else {
                printf("%d\n", ask(1, n, 1, l, r, c));
            }
        }
    }
    return 0;
}
