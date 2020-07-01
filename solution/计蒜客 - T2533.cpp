#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int lowbit(int x) {return x & -x;}
int n;
int bit[maxn];

int ask(int x) {
    int res = 0;
    while(x < maxn) {
        res += bit[x];
        x += lowbit(x);
    }
    return res;
}

void update(int x, int val) {
    while(x) {
        bit[x] += val;
        x -= lowbit(x);
    }
}
int suf[maxn], a[maxn], c[maxn];
struct node {
    int l, r, id;
    node() {}
    node(int l,int r,int id) : l(l), r(r), id(id) {}
}q[maxn];
bool cmp(node a, node b) {
    return a.l < b.l;
}
int ans[maxn];

int main() {
    scanf("%d", &n);
    int all = 0;
    for(int i = 1;i <= n;++i) {
        scanf("%d", &a[i]);
        ++a[i];
        if(suf[a[i]] == 0) ++all;
        suf[a[i]] = n + 1 ;
    }
    for(int i = n;i >= 1;--i) {
        c[i] = suf[a[i]];
        suf[a[i]] = i;
    }
    for(int i = 1;i < maxn;++i) if(suf[i]) update(suf[i], 1);
    int m;
    scanf("%d", &m);
    for(int i = 1;i <= m;++i) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m, cmp);
    int now = 1;
    for(int i = 1;i <= n;++i) {
        while(now <= m&&q[now].l == i) {
            ans[q[now].id] = all - ask(q[now].r+1);
            ++now;
        }
        update(c[i], 1);
    }
    for(int i = 1;i <= m;++i) printf("%d\n", ans[i]);
    return 0;
}
