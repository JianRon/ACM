#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e3 + 10;
const int INF = 0x7fffffff;

char s[maxn][maxn];
int ID[maxn][maxn];

const int fy[] = {-3,0,+3};
const int fx[] = {-1,-2,-1};
const int sy[] = {-6,0,+6};
const int sx[] = {-2,-4,-2};
int n,m;

bool ok(int x,int y){
    return x >= 0&&x < 4 * n + 3&&y >=0&&y < 6 * m + 3;
}
struct EDGE{
    int from,to,cap,flow;
    EDGE(){}
    EDGE(int a,int b,int c,int d):from(a),to(b),cap(c),flow(d) {}
};

struct DINIC{
    int n,m,s,t;
    vector<int> G[maxn];
    vector<EDGE> e;
    int cur[maxn],d[maxn];
    int be[maxn];
    queue<int> q;
    void clear(){
        e.clear();
        for(int i = 1;i <= n;i++) G[i].clear();
    }
    void init(){

        for(int i = 0;i < (int)e.size();i+=2) {
            EDGE& u = e[i];
            u.cap += u.flow + e[i^1].cap + e[i^1].flow;
            u.flow = 0;
            e[i^1].flow = 0;
            e[i^1].cap = (u.cap /= 2);
        }
    }
    void addedge(int from,int to,int cap){
        //printf("%d %d\n",from,to);
        e.push_back(EDGE(from,to,cap,0));
        e.push_back(EDGE(to,from,cap,0));
        m = e.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool bfs(){
        memset(d,-1,sizeof d);
        q.push(s);
        d[s] = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            //printf("- %d ",u);
            for(auto& v:G[u]) {
                auto& temp =  e[v];
                if(d[temp.to] == -1&&temp.cap > temp.flow) {
                    d[temp.to] = d[u] + 1;
                    q.push(temp.to);
                }
            }
        }
        /*
        puts("");
        printf("%d %d d[t] == %d\n",s,t,d[t]);
        */
        return d[t] != -1;
    }
    int dfs(int x,int a) {
        if(x == t|| a == 0) return a;
        int flow = 0,f;
        for(auto& i = cur[x];i < G[x].size();i++){
            EDGE& temp = e[G[x][i]];
            if(d[x] + 1 == d[temp.to]&&(f = dfs(temp.to,min(a,temp.cap - temp.flow))) > 0) {
                temp.flow += f;
                e[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    int maxflow(int s,int t){
        this->s = s;
        this->t = t;
        init();
        int flow = 0;
        while(bfs()) {
            memset(cur,0,sizeof cur);
            flow += dfs(s,INF);
            //printf(">%d<\n",flow);
        }
        for(int i = 1;i <= n;i++) {
            if(d[i] != -1) be[i] = 1;
            else be[i] = -1;
        }
        return flow;
    }
}D;
int tot;
vector<pair<int,int>> g[maxn];

void build_gomory_hu(){
    vector<int> u;
    for(int i = 1;i <= tot;i++) u.push_back(i);
    queue<vector<int>> q;
    q.push(u);
    while(!q.empty()) {
        u = q.front();
        q.pop();
        /*
        puts("```");
        for(auto& v:u) printf("%d ",v);puts("<<");
        */
        if((int)u.size() <= 1) continue;
        //printf("%d %d ->",u[0],u[1]);
        int temp = D.maxflow(u[0],u[1]);
        //printf("%d\n",temp);

        g[u[0]].push_back(make_pair(u[1],temp));
        g[u[1]].push_back(make_pair(u[0],temp));
        //printf("-> %d %d %d\n",u[0],u[1],temp);

        vector<int> t1,t2;
        //printf("%d\n",(int)u.size());
        for(int i = 0;i < u.size();i++) {
            if(D.be[u[i]] == 1) {
                t1.push_back(u[i]);
            }
            else{
                t2.push_back(u[i]);
            }
            //printf("%d\n",u[i]);
        }
        /*
        for(int i = 0;i < t1.size();i++) printf("%d ",t1[i]);puts("<<");
        for(int i = 0;i < t2.size();i++) printf("%d ",t2[i]);puts("<<");
        */
        q.push(t1);
        q.push(t2);
    }
}
bool vis[maxn];
void dfs(int s,int o,int a,int &ans){
    if(o != s) ans += a;
    vis[o] = 1;
    //printf("%d %d %d\n",s,o,a);
    for(auto& u:g[o]){
        if(vis[u.first]) continue;
        //printf("...%d %d %d\n",o,u.first,u.second);
        dfs(s,u.first,min(a,u.second),ans);
    }
}

int main() {
    int T,CASE = 0;
    scanf("%d",&T);
    while(T--) {
        ++CASE;
        D.clear();
        tot = 0;
        scanf("%d%d",&n,&m);
        for(int i = 0;i < n*4 + 3;i++) {
            getchar();
            scanf("%[^\n]",s[i]);
        }
        //for(int i = 0;i < n*4 + 3;i++) printf("%s\n",s[i]);
        for(int i = 0;i < n*4 + 3;i++) {
            for(int j = 0;j < m * 6 + 3;j++) {
                if(s[i][j] == '*') {
                    ID[i][j] = ++tot;
                    //printf(">>> %d %d\n",i,j);
                    for(int d = 0;d < 3;d++) {
                        int nx = i + fx[d];
                        int ny = j + fy[d];
                        //printf("%d %d -> %c\n",nx,ny,s[nx][ny]);
                        if(ok(nx,ny)&&s[nx][ny] == ' ') {
                            nx = i + sx[d];
                            ny = j + sy[d];
                            if(ok(nx,ny)&&s[nx][ny] == '*') {
                                //printf("%d %d\n",tot,ID[nx][ny]);
                                D.addedge(tot,ID[nx][ny],1);
                                //D.addedge(ID[nx][ny],tot,1);
                            }
                        }
                    }
                }
            }
        }
        for(int i = 1;i <= tot;i++) g[i].clear();
        D.n = tot;
        build_gomory_hu();
        int ans = 0;
        for(int i = 1;i <= tot;i++) {
            memset(vis,0,sizeof vis);
            dfs(i,i,INF,ans);
            //printf("%d %d\n",i,ans);
        }
        printf("Case #%d: %d\n",CASE,ans >> 1);
        /*
        for(int i = 1;i <= tot;i++) {
            for(int j = 1;j <= tot;j++) {
                printf("%d ",sp[i][j]);
            }
            puts("");
        }
        */
    }
    return 0;
}
