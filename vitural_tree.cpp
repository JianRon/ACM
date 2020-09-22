/**
g  为原树的图；
vg 为虚树的图；
默认1是根节点，根节点总在虚树中.
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<int> g[maxn];
int dep[maxn];
int fa[maxn];
int sz[maxn];

void dfs0(int o,int p) {
    dep[o] = dep[p] + 1;
    fa[o] = p;
    for(int i = 0;i < g[o].size();++i) {
        if(g[o][i] == p) {
            g[o].erase(g[o].begin() + i);
            break;
        }
    }
    sz[o] = 1;
    for(int i = 0;i < g[o].size();++i) {
        dfs0(g[o][i], o);
        sz[o] += sz[g[o][i]];
        if(sz[g[o][i]] > sz[g[o][0]]) {
            swap(g[o][i], g[o][0]);
        }
    }
}
int ftop[maxn];
int tot, dfn[maxn];

void dfs1(int o,int tp) {
    ftop[o] = tp;
    dfn[o] = ++tot;
    if(g[o].size()) dfs1(g[o][0], tp);
    for(int i = 1;i < g[o].size();++i) {
        dfs1(g[o][i], g[o][i]);
    }
}
int LCA(int x, int y) {
    while(ftop[x] != ftop[y]) {
        if(dep[ftop[x]] < dep[ftop[y]] ) swap(x, y);
        x = fa[ftop[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    return x;
}

int cmp(int a,int b) {
    return dfn[a] < dfn[b];
}
vector<int> vg[maxn];

void addedge(int a,int b) {
    vg[a].push_back(b);
}
int h[maxn], stk[maxn], top;

void build(int k) {
//        sort(h + 1, h + 1 + k, cmp);
    sort(h + 1, h + 1 + k, [&](int a,int b){return dfn[a] < dfn[b];});
    stk[top = 1] = 1; vg[1].resize(0);
    for(int i = 1;i <= k;++i) {
        if(h[i] == 1) continue;
        int lca = LCA(stk[top], h[i]);
//        printf("%d %d %d\n", lca, stk[top], h[i]);
        vg[h[i]].resize(0);
        if(lca == stk[top]) {
            stk[++top] = h[i];
        }
        else {
            while(dfn[lca] < dfn[stk[top - 1]]) {
                addedge(stk[top - 1], stk[top]);
                --top;
            }
            if(lca == stk[top - 1]) {
                addedge(stk[top - 1], stk[top]);
                stk[top] = h[i];
            }
            else {
                vg[lca].resize(0);
                addedge(lca, stk[top]);
                stk[top] = lca; stk[++top] = h[i];
            }
        }
    }
    while(top > 1) addedge(stk[top - 1], stk[top]), --top;
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1;i < n;++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs0(1, 0);
    dfs1(1, 1);
    int q;
    scanf("%d", &q);
    while(q--) {
        int k;
        scanf("%d", &k);
        for(int i = 1;i <= k;++i) scanf("%d", &h[i]);
        build(k);
        for(int i = 1;i <= n;++i) {
            printf("%d >> ", i);
            for(auto u: vg[i]) printf("%d ", u);puts("");
        }
        puts("");
    }
    return 0;
}
/*
===========INPUT===========
9
1 2
1 8
2 3
2 4
8 9
3 5
5 6
5 7
1
5 4 5 6 7 9
===========OUTPUT==========
1 >> 2 9
2 >> 5 4
3 >>
4 >>
5 >> 6 7
6 >>
7 >>
8 >>
9 >>
*/
