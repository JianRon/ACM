/*
Dijkstra 优化最小费
*/
/**
注意：
1、在建图之前先调用 init 函数。
2、图内下标从0开始(原图下标从1开始，下标需要-1)。
*/

#include<bits/stdc++.h>
#define in(a)  (a << 1)
#define out(a) (a << 1 | 1)

using namespace std;


inline int read_int() {
    char c;
    int ret = 0, sgn = 1;
    do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') sgn = -1; else ret = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    return sgn * ret;
}

struct Node {
    int id,dis;
    Node() {}
    Node(int dis,int id):dis(dis),id(id) {}
    bool operator < (const Node& b) const {
        return dis > b.dis;
    }
};

struct Edge {
    int rev,to,cap,cost;
    Edge() {}
    Edge(int rev,int to,int cap,int cost) : rev(rev),to(to),cap(cap),cost(cost) {}
};

const int maxn = 4e3 + 10;
const int INF  = 0x3f3f3f3f;
struct MCMF{
    vector<Edge> g[maxn];
    int inq[maxn],vis[maxn],ptr[maxn];
    int d[maxn],a[maxn],h[maxn];
    int n,m,s,t;
    void init(int n) {
        this->n = n;
        for(int i = 0;i < n;++i) g[i].clear();
        m = 0;
    }
    void addedge(int from,int to,int cap,int cost) {
        g[from].push_back(Edge(g[to].size(),to,cap,cost));
        g[to].push_back(Edge((int)g[from].size() - 1,from,0,-cost));
    }

    bool augment(int s,int t,int &flow,int &cost) {
        fill(d, d + n,INT_MAX);
        fill(vis, vis + n,INT_MAX);
        d[s] = 0; a[s] = INT_MAX;

        priority_queue<Node> q;
        q.push(Node(0,s));

        while(!q.empty()) {
            Node u = q.top();
            q.pop();
            if(vis[u.id] <= u.dis) continue;
            vis[u.id] = u.dis;
            for(int i = 0;i < (int)g[u.id].size();++i) {
                Edge& e = g[u.id][i];
                if(e.cap&& d[e.to] > d[u.id] + e.cost + h[u.id] - h[e.to]) {
                    d[e.to] = d[u.id] + e.cost + h[u.id] - h[e.to];
                    q.push(Node(d[e.to],e.to));
                }
            }
        }
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
            if (e.cap == 0 || d[e.to] != d[v] + e.cost + h[v] - h[e.to] || vis[e.to]) {
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
    int Mincost(int s,int t) {
        this->t = t;
        this->s = s;
        int flow = 0,cost = 0;
        while(augment(s,t,flow,cost)) {
            fill(ptr,ptr + n,0);
            fill(vis,vis + n,0);
            int tmp = dfs(s,INF);
            for(int i = 0;i < n;++i) h[i] += d[i];
            flow += tmp;
            cost += tmp * h[t];

        }
        return cost;
    }
}mcmf;

int a[maxn];

void solve() {
    int n,k;
//    scanf("%d%d",&n,&k);
    n = read_int();
    k = read_int();
    for(int i = 1;i <= n;++i) {
//        scanf("%d",&a[i]);
        a[i] = read_int();
    }
    mcmf.init(in(n + 1) + 1);
    mcmf.addedge(in(0),out(0),k,0);
    for(int i = 1;i <= n;++i) {
        mcmf.addedge(out(0),in(i),1,0);
        mcmf.addedge(in(i),out(i),1,-a[i]);
        mcmf.addedge(out(i),in(n + 1),1,0);
        for(int j = i + 1;j <= n;++j) {
            if(a[i] <= a[j]) {
                mcmf.addedge(out(i),in(j),1,0);
            }
        }
    }
    int ans = mcmf.Mincost(in(0),in(n + 1));
    printf("%d\n",-ans);
}

int main() {
    int  T;
    T = read_int();
    while(T--) solve();
    return 0;
}
