#include<bits/stdc++.h>
#define fst first
#define snd second
using namespace std;

typedef vector<double> vd;
typedef vector<vd>     mt;
typedef vector<int>    vi;
const double INF = 2e18;
const int    sz  = 3e3 + 2;
const double eps = 1e-6;

void check(double a[][sz],double b[],double c[],vi& B,vi& N,double v) {
//    return ;
    for(auto u : B) {
            printf("%d %f :: ", u, b[u]);
        for(auto v : N) {
            printf("%d->%f ",v, a[u][v]);
        }
        puts("");
    }
    printf("v == %f ",v);
    for(auto u : N) {
        printf("%d -> %f ",u,c[u]);
    }
    puts("");
    puts("");
}

void pivot(double a[][sz],double b[],double c[],vi& B,vi& N,double& v, int l, int e) {
    for(auto it = N.begin();it != N.end();++it) if(*it == e) {
        swap(*it,N.back());
        N.pop_back();
        break;
    }
    for(auto it = B.begin();it != B.end();++it) if(*it == l) {
        swap(*it,B.back());
        B.pop_back();
        break;
    }
    b[e] = b[l] / a[l][e];
    for(int j : N) a[e][j] = a[l][j] / a[l][e];
    a[e][l] = 1 / a[l][e];
    for(int i : B) {
        b[i] = b[i] - a[i][e] * b[e];
        for(int j : N) a[i][j] -= a[i][e] * a[e][j];
        a[i][l] = -a[i][e] * a[e][l];
    }
    v += c[e] * b[e];
    for(int j : N)  c[j] -= c[e] * a[e][j];
    c[l] = -c[e] * a[e][l];
    N.emplace_back(l);
    B.emplace_back(e);
}

void get_optimal_solution(double a[][sz],double b[],double c[],vi& B,vi& N,double& v) {
    int m = B.size(),n = N.size();
    vd delta(n + m + 1,0);
    while(true) {
//        puts("::");
//        check(a, b, c, B, N, v);
        int e = -1;
        for(int u : N) if(c[u] > eps) {
//            printf("%f %d\n",c[u], u);
            if(e == -1 || c[u] > c[e]) e = u;
        }
        if(e == -1) break;
        double tmp = 0;
        for(int u : B) {
//            printf(" ?? %f %d\n",a[u][e],e);
            if(a[u][e] > eps) {
                delta[u] = b[u] / a[u][e];
            }
            else delta[u] = INF;
        }
        int l = B.front();
        for(int u : B) if(delta[u] < delta[l]) l = u;
        if(delta[l] == INF) {
            puts("Unbounded");
            exit(0);
            break;
        }
        else {
//            printf("%d %d >> %f\n",l,e,a[l][e]);
            pivot(a,b,c,B,N,v,l,e);
        }
    }
}

double newc[sz];
void initialize_simplex(double a[][sz],double b[],double c[],vi& B,vi& N,double& v) {
    int k = B[0];
    for(auto u : B) if(b[k] > b[u]) k = u;
    if(b[k] >= eps) return;
    N.push_back(0);
    for(int u : B) a[u][0] = -1;
    newc[0] = -1;
//    check(a,b,newc,B,N,v);
    pivot(a,b,newc,B,N,v,k,0);
//    check(a,b,newc,B,N,v);
    get_optimal_solution(a,b,newc,B,N,v);
//    check(a,b,newc,B,N,v);

//    printf("??");
    int flag = 0;
    for(auto it = N.begin();it != N.end();++it) if(*it == 0) {
        swap(*it,N.back());
        N.pop_back();
        flag = 1;
        break;
    }
    for(auto it = B.begin();it != B.end();++it) if(*it == 0) {
        swap(*it,B.back());
        B.pop_back();
        break;
    }
    for(auto u : B) if(c[u] > eps || c[u] < -eps){
//        printf("%d %f %f\n",u,c[u],b[u]);
        for(auto x : N) c[x] -= c[u] * a[u][x];
        v += c[u] * b[u];
        c[u] = 0;
        a[u][0] = 0;
    }
    if(flag || (b[0] <= eps && b[0] >= -eps)) return;
    else {
        puts("Infeasible");
        exit(0);
    }
}

vd simplex(double a[][sz],double b[],double c[],vi& B,vi& N,double& v) {
    //    check(a, b, c, B, N, v);
    initialize_simplex(a,b,c,B,N,v);
//    check(a, b, c, B, N, v);
    get_optimal_solution(a,b,c,B,N,v);
//    check(a, b, c, B, N, v);
//    printf("%f\n", v);
    int n = N.size(),m = B.size();
    vd res(n+1,0);
    for(int u : B) {
        if(u <= n) res[u] = b[u];
    }
    return res;
}

int n, m1, m2;

double a[sz][sz];
double b[sz],c[sz];
vector<int> B, N;
double v;
const int maxn = 51;
int arr[maxn][maxn];
int ans[maxn][maxn];
int tot;

typedef pair<int, int> pii;
void add_con(const int& tb,const vector<pii> &ta) {
    ++tot;
    b[tot] = tb;
    for(auto u : ta) {
        if(u.fst == 0) u.fst = n + 1;
        a[tot][u.fst] = u.snd;
    }
}
int pos(int i,int j) {
    return (i - 1) * n + j;
}
void test() {
    tot = 2;
    B.push_back(3);
    B.push_back(4);
    N.push_back(1);
    N.push_back(2);
    add_con(2,{pii(1,2), pii(2,-1)});
    add_con(-4,{pii(1,1), pii(2,-5)});
    c[1] = 2,c[2] = -1;
    simplex(a,b,c,B,N,v);
}
int main() {
//    test();
//    int T;
//    scanf("%d",&T);
//    while(T--) {
//        scanf("%d%d%d",&n,&m1,&m2);
//        tot = n + 1;
//        c[n] = -1;
//        for(int i = 1;i <= n;++i) {
//            add_con(1,{pii(i,1), pii(i-1,-1)});
//            add_con(0,{pii(i,-1), pii(i-1,1)});
//        }
//        for(int i = 0;i <= n;++i) {
//            add_con(i,{pii(i,1)});
//        }
//        for(int i = 1;i <= m1;++i) {
//            int l, r, k;
//            scanf("%d%d%d",&l,&r,&k);
//            add_con(-k,{pii(l-1,1),pii(r,-1)});
//        }
//        for(int i = 1;i <= m2;++i) {
//            int l, r, k;
//            scanf("%d%d%d",&l,&r,&k);
//            add_con(-k,{pii(r,1),pii(l-1,-1),pii(n,-1),pii(0,1)});
//        }
//        N.resize(n + 1);
//        iota(N.begin(),N.end(),1);
//        B.resize(tot - (n + 1));
//        iota(B.begin(),B.end(),n + 2);
//        simplex(a, b, c, B, N, v);
//        printf("%f\n",v);
//    }
    int n, m, t;
    scanf("%d%d%d",&n,&m,&t);
    for(int i = 1;i <= n;++i) {
        int tmp;
        scanf("%d",&tmp);
        c[i] = tmp;
    }
    tot = n;
    for(int i = 1;i <= m;++i) {
        vector<pii> tmp;
        int b,ac;
        for(int j = 1;j <= n;++j) {
            scanf("%d",&ac);
            tmp.push_back(pii(j,ac));
        }
        scanf("%d",&b);
        add_con(b,tmp);
    }
    vector<int> B, N;
    N.resize(n);
    iota(N.begin(), N.end(), 1);
    B.resize(m);
    iota(B.begin(), B.end(), n+1);
    vd ans = simplex(a,b,c,B,N,v);
    printf("%.10f\n",v);
    if(t)
    for(int i = 1;i <= n;++i) printf("%.10f%c",ans[i],i == n ?'\n':' ');
    return 0;
}

