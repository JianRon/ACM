#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;
int add(int a,int b) {return a + b < mod ? a + b : a + b - mod;}

struct errTree {
    const static int maxn = 1e6 + 10;
    const static int maxc = 26;
    int ch[maxn][maxc],fail[maxn],len[maxn], sz, last, s[maxn], cur;
    int dp[2][maxn];
    int node(int l) {
        sz++;
        memset(ch[sz], 0, sizeof ch[sz]);
        fail[sz] = 0;
        len[sz] = l;
        return sz;
    }
    void init() {
        sz = -1;
        last = 0;
        s[cur = 0] = '$';
        node(0);
        node(-1);
        fail[0] = 1;
    }
    int getfail(int x) {
        while(s[cur - len[x] - 1] != s[cur]) x = fail[x];
        return x;
    }
    int insert(char cc) {
        int c = cc - 'a';
        s[++cur] = cc;
        int now = getfail(last);
        if(!ch[now][c]) {
            int x = node(len[now] + 2);
            if(dp[0][now] == 0) dp[0][x] = add(add(dp[1][now], dp[1][now]), 1);
            else dp[0][x] = add(add(dp[0][now], dp[0][now]), add(dp[1][now], dp[1][now]));
            fail[x] = ch[getfail(fail[now])][c];
            ch[now][c] = x;
            dp[1][x] = add(dp[0][fail[x]], dp[1][fail[x]]);
        }
        last = ch[now][c];
        return add(dp[0][last], dp[1][last]);
    }
}pam;

const int maxn = 1e6 + 10;
char s[maxn];

int main() {

    int T = 1;
    while(T--) {
        pam.init();
        scanf("%s",s + 1);
        int n = strlen(s + 1);
        int ans = 0;
        for(int i = 1;i <= n;++i) ans = add(ans,pam.insert(s[i]));
        printf("%d\n", ans);
    }
    return 0;
}
