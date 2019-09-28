/**
simplex method
max sum_{i=1}^{n} c[i]x[i]
st. A*x <= b
--------------------------
1、目标值是最小值时，求负数形式的最大值。
2、等于约束拆成大于等于和小于等于
3、大于等于约束，两边乘-1
--------------------------
标准型
sum {a_ij * x_j} <= b_i

松弛型
x_i = b_i - sum {a_ij * x_j} (注意sum 前面是减号)

sz = 约束条件数量 +  变量数量 + 1
a[i][j] 为松弛型中的 a_{ij}
b,c 和原形式对应
N 为所有的{x_i}
B 为所有的{x_j}
v 为最优的值
方案 x[i] = [i belong B] * b[i]
*/

#include<bits/stdc++.h>
using namespace std;

typedef vector<double> vd;
typedef vector<vd>     mt;
typedef vector<int>    vi;
const double INF = 2e18;
const int    sz  = 3e3 + 10;
const double eps = 1e-9;

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
        int e = -1;
        for(int u : N) if(c[u] > 0) {
            if(e == -1 || c[u] > c[e]) e = u;
        }
        if(e == -1) break;
        double tmp = 0;
        for(int u : B) {
            if(a[u][e] > eps) {
                delta[u] = b[u] / a[u][e];
            }
            else delta[u] = INF;
        }
        int l = B.front();
        for(int u : B) if(delta[u] < delta[l]) l = u;
        if(delta[l] == INF) {
            puts("unbounded");
            break;
        }
        else pivot(a,b,c,B,N,v,l,e);
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
    pivot(a,b,newc,B,N,v,k,0);
    get_optimal_solution(a,b,newc,B,N,v);
    if(v == 0) {
        for(int u : B) if(u == 0) {
            pivot(a,b,newc,B,N,v,u,N[0]);
        }
        for(auto it = N.begin();it != N.end();++it) if(*it == 0) {
            swap(*it,N.back());
            N.pop_back();
            break;
        }
        for(int u : B) {
            if(c[u] != 0) {
                for(int j : N) {
                    c[j] -= c[u] * a[u][j];
                }
                v += c[u] * b[u];
                c[u] = 0;
            }
        }
    }
    else puts("infeasible");
}

vd simplex(double a[][sz],double b[],double c[],vi& B,vi& N,double& v) {
    initialize_simplex(a,b,c,B,N,v);
    get_optimal_solution(a,b,c,B,N,v);
    int n = N.size(),m = B.size();
    vd res(n+1,0);
    for(int u : B) {
        if(u <= n) res[u] = b[u];
    }
    return res;
}

int n;

int pos(int i,int j) {
    return (i - 1) * n + j;
}

const int maxn = 51;
int arr[maxn][maxn];
int ans[maxn][maxn];
double a[sz][sz];
double b[sz],c[sz];

int main() {
    scanf("%d",&n);
    vi B(n*n),N(n << 1);
    for(int i = 1;i <= n;++i) {
        for(int j = 1;j <= n;++j) {
            scanf("%d",&arr[i][j]);
            int v = pos(i,j) + (n << 1);
            b[v] = -arr[i][j];
            a[v][i] = a[v][j+n] = -1;
        }
    }
    for(int i = 1;i <= n << 1;++i) c[i] = -1;
    iota(N.begin(),N.end(),1);
    iota(B.begin(),B.end(),1+(n<<1));

    double ans = 0;
    vd res = simplex(a,b,c,B,N,ans);
    printf("%.f\n",-ans * n);
    for(int i = 1;i <= n;++i) {
        for(int j = 1;j <= n;++j) printf("%.f%c",res[i]+res[j+n],j == n?'\n':' ');
    }
    return 0;
}
