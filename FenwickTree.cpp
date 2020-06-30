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
pair<int,int> p[maxn];

int main() {
    scanf("%d", &n);
    for(int i = 1;i <= n;++i) {
        int tmp;
        scanf("%d",&tmp);
        p[tmp].first = i;
    }
    for(int i = 1;i <= n;++i) {
        int tmp;
        scanf("%d",&tmp);
        p[tmp].second = i;
    }
    sort(p + 1,p + 1 + n);
    int ans = 0;
    for(int i = 1;i <= n;++i) {
        if(ask(p[i].second) > 0) ++ans;
        update(p[i].second, 1);
    }
    printf("%d\n", ans);
    return 0;
}
