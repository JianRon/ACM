#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int lowbit(int x) {return x & -x;}
int n;
int bit[maxn];

int ask(int x) {
    int res = 0;
    while(x <= n) {
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
int a[maxn];

int main() {
    scanf("%d", &n);
    for(int i = 1;i <= n;++i) scanf("%d", &a[i]);
    long long ans = 0;
    for(int i = 1;i <= n;++i) {
        ans += ask(a[i]);
        update(a[i], 1);
    }
    printf("%lld\n", ans);
    return 0;
}
