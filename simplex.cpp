#include<bits/stdc++.h>
using namespace std;

typedef vector<double> vd;
typedef vector<vd>     mt;
typedef vector<int>    vi;
const double INF = 2e18;
const double eps = 1e-6;
void pivot(mt& a,vd& b,vd& c,vi& B,vi& N,double& v, int l, int e) {
    b[e] = b[l] / a[l][e];
    for(auto j : N) if(j != e) a[e][j] = a[l][j] / a[l][e];
    a[e][l] = 1 / a[l][e];
    for(auto i : B) if(i != l) {
        b[i] = b[i] - a[i][e] * b[e];
        for(auto j : N) if(j != e) {
            a[i][j] -= a[i][e] * a[e][j];
        }
        a[i][l] = -a[i][e] * a[e][l];
    }
    v += c[e] * b[e];
    for(auto j : N) if(j != e) {
        c[j] -= c[e] * a[e][j];
    }
    c[l] = -c[e] * a[e][l];
    for(auto &u : N) if(u == e) u = l;
    for(auto &u : B) if(u == l) u = e;
}

void debug(mt a,vd b,vd c,vi N,vi B,double v) {
    puts("a >> ");
    for(auto i:B) {
        for(auto j:N) {
            printf("(%d %d) => %.2f ",i,j,a[i][j]);
        }
        puts("");
    }
    puts("B : ");
    for(auto u:B) printf("%d ",u);
    puts("\nN : ");
    for(auto u:N) printf("%d ",u);
    puts("\nb : ");
    for(auto u:b) printf("%.2f ",u);
    puts("\nc : ");
    for(auto u:c) printf("%.2f ",u);
    puts("\nv : ");
    printf("%.2f",v);

}

void get_optimal_solution(mt& a,vd& b,vd& c,vi& B,vi& N,double& v) {
    int m = B.size(),n = N.size();
    vd delta(n + m + 1,0);
    while(true) {
        int e = -1;
        for(auto j : N) if(c[j] > 0) {
            e = j;
            break;
        }
        if(e == -1) break;
        double tmp = 0;
        for(auto i : B) {
            if(a[i][e] > eps) {
                delta[i] = b[i] / a[i][e];
            }
            else delta[i] = INF;
        }
        int l = B.front();
        for(auto u : B) if(delta[u] < delta[l]) l = u;
        if(delta[l] == INF) {
            puts("unbounded");
            break;
        }
        else pivot(a,b,c,B,N,v,l,e);
    }
}

void initialize_simplex(mt& a,vd& b,vd& c,vi& B,vi& N,double& v) {
    int k = B[0];
    for(auto u : B) if(b[k] > b[u]) k = u;
    if(b[k] >= eps) return;
    N.push_back(0);
    for(auto u : B) a[u][0] = -1;
//    puts("ok");
    vd newc(c.size(),0);
    newc[0] = -1;
    pivot(a,b,newc,B,N,v,4,0);
//    debug(a,b,newc,N,B,v);
    get_optimal_solution(a,b,newc,B,N,v);
//    debug(a,b,newc,N,B,v);
    if(abs(v) <= eps) {
        for(auto i : B) if(i == 0) {
            pivot(a,b,newc,B,N,v,i,N[0]);
        }
        for(auto it = N.begin();it != N.end();++it) if(*it == 0) {
            N.erase(it);
            break;
        }
        for(auto i : B) {
            if(abs(c[i]) >= eps) {
                for(auto j : N) {
                    c[j] += c[i] * a[i][j];
                }
                c[i] = 0;
            }
        }
    }
    else puts("infeasible");
}

vd simplex(mt& a,vd& b,vd& c,vi& B,vi& N,double& v) {
    initialize_simplex(a,b,c,B,N,v);
    get_optimal_solution(a,b,c,B,N,v);
//    debug(a,b,c,B,B,v);
    int n = N.size(),m = B.size();
    vd res(n,0);
    for(int i = 0;i < m;++i)
        if(B[i] < n) res[B[i]] = b[i];
    return res;
}

void pivot_test() {
    vi N = {0,1,2};
    vi B = {3,4,5};
    mt a = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{1,1,3,0,0,0},{2,2,5,0,0,0},{4,1,2,0,0,}};
    vd b = {0,0,0,30,24,36};
    vd c = {3,1,2,0,0,0};
    double v = 0;
    pivot(a,b,c,B,N,v,5,0);

    puts("a >> ");
    for(auto i:B) {
        for(auto j:N) {
            printf("(%d %d) => %.2f ",i + 1,j + 1,a[i][j]);
        }
        puts("");
    }
    puts("B : ");
    for(auto u:B) printf("%d ",u);
    puts("\nN : ");
    for(auto u:N) printf("%d ",u);
    puts("\nb : ");
    for(auto u:b) printf("%.2f ",u);
    puts("\nc : ");
    for(auto u:c) printf("%.2f ",u);
    puts("\nv : ");
    printf("%.2f",v);
}
void test_init() {
    vd c = {0,2,-1,0,0};
    vd b = {0,0,0,2,-4};
    mt a = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,2,-1,0,0},{0,1,-5,0,0}};
    vi B = {3,4},N = {1,2};
    double v = 0;
    initialize_simplex(a,b,c,B,N,v);
    debug(a,b,c,N,B,v);
}
void test_simplex() {
    vd c = {0,3,1,2,0,0,0};
    vd b = {0,0,0,0,30,24,36};
    mt a = {{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,1,1,3,0,0,0},{0,2,2,5,0,0,0},{0,4,1,2,0,0,0}};
    vi B = {4,5,6},N = {1,2,3};
    double v = 0;
    simplex(a,b,c,B,N,v);
    debug(a,b,c,N,B,v);
}
int n;

int pos(int i,int j) {
    return i * (n - 1) + j;
}

const int maxn = 51;
int arr[maxn][maxn];

int main() {
//    test_simplex();
    int n;
    scanf("%d",&n);
    int sz = 1 + (n << 1) + (n * n);
    for(int i = 1;i <= n;++i) {
        for(int j = 1;j <= n;++j) {
            scanf("%d",&arr[i][j]);
        }
    }
    mt a(sz,vd(sz));
    vd b(sz),c(sz);
    vi B(n*n),N(n << 1);
    iota(N.begin(),N.end(),1);
    iota(B.begin(),B.end(),1+(n<<1));
    double ans = 0;
    simplex(a,b,c,B,N,ans);
//    printf("%.f\n",ans);

    return 0;
}

