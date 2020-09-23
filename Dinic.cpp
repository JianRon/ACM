/**
注意：
1、在建图之前先调用 init 函数。
2、图内下标从0开始(原图下标从1开始，下标需要-1)。
*/

#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int rev,to,cap;
    Edge() {}
    Edge(int rev,int to,int cap) : rev(rev),to(to),cap(cap) {}
};

const int maxn = 1e4 + 10;
const int INF  = 0x3f3f3f3f;
struct Dinic{
    vector<Edge> g[maxn];
    int vis[maxn],ptr[maxn];
    int d[maxn];
    int n,m,s,t;
    void init(int n) {
        this->n = n;
        for(int i = 0;i < n;++i) g[i].clear();
        m = 0;
    }
    void addedge(int from,int to,int cap) {
        g[from].push_back(Edge(g[to].size(),to,cap));
        g[to].push_back(Edge((int)g[from].size() - 1,from,0));
    }

    bool augment(int s,int t,int &flow) {
        fill(d, d + n,INT_MAX);
        fill(vis, vis + n,INT_MAX);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            for(auto u : g[cur]) if(u.cap&&d[u.to] == INT_MAX) {
                d[u.to] = d[cur] + 1;
                q.push(u.to);
            }
        }
//        cout << d[t] << endl;
        return d[t] != INT_MAX;
    }
    /// dfs-speed
    int dfs(int v, int r) {
        if (v == t) {
            return r;
        }

        vis[v] = true;
        int res = 0;

        for (int& i = ptr[v]; i < int(g[v].size()); i++) {
            Edge& e = g[v][i];
            if (e.cap == 0 || d[e.to] != d[v] + 1 || vis[e.to]) {
                continue;
            }
            int d = dfs(e.to, min(r - res, e.cap));
            res += d;
            e.cap -= d;
            g[e.to][e.rev].cap += d;
            if (res == r) {
                vis[v] = false;
                break;
            }
        }

        return res;
    }
    int Maxflow(int s,int t) {
        this->t = t;
        this->s = s;
        int flow = 0;
        while(augment(s,t,flow)) {
            fill(ptr,ptr + n,0);
            fill(vis,vis + n,0);
            int tmp = dfs(s,INF);
            flow += tmp;
        }
        return flow;
    }
}D;

int main() {
    ios::sync_with_stdio(false);
    int n,m,s,t;
    cin >> n >> m >> s >> t;
    D.init(n);
    --s,--t;
    for(int i = 1;i <= m;++i) {
        int a,b,c;
        cin >> a >> b >> c;
        --a,--b;
        D.addedge(a,b,c);
    }
    cout << D.Maxflow(s,t) << endl;
    return 0;
}
