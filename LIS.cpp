/**
O(nm/w)求最长上升子序列
（未优化）
*/
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long  ull;
const int maxn = 3e3 + 10;
int up;

struct bits{
    static const int bt = 64;
    static const int bound = 50;
    
    ull bit[bound];

    bits(){memset(bit,0,sizeof bit);}
    void init() {
        memset(bit,0,sizeof bit);
    }

    ull plus(ull& a,ull b) {
        ull t = a;
        return (ull)((a += b) < max(t,b));
    }
    bits operator + (const bits& b){
        bits res;
        ull carry1 = 0,carry2 = 0;
        for(int i = 0;i < up;i++) {
            carry1 = 0;
            plus(res.bit[i],bit[i]);
            carry1 |= plus(res.bit[i],carry2);
            carry1 |= plus(res.bit[i],b.bit[i]);
            carry2 = carry1;
        }
        return res;
    }
    bits operator | (const bits& b){
        bits res;
        for(int i = 0;i < up;i++) {
            res.bit[i] = b.bit[i]|bit[i];
        }
        return res;
    }
    bits operator & (const bits& b) {
        bits res;
        for(int i = 0 ;i < up;i++) {
            res.bit[i] = b.bit[i]&bit[i];
        }
        return res;
    }
    ull operator [] (const int& x){
        int a = x / bt;
        int b = x % bt;
        return bit[a] >> b & 1ull;
    }
    void set(int x){
        bit[x>>6] |= 1ull<<(x&((1<<6)-1));
    }
    void reset(int x){
        bit[x>>6] &= ~(1ull<<(x&((1<<6)-1)));
    }
    bits flip(){
        bits res;
        for(int i = 0;i < up;i++) {
            res.bit[i] = ~bit[i];
        }
        return res;
    }
};
int al;
bits L[maxn];
bits M[26],MF[26];

void ALG_B(int n,int m,char* y,char* x,int *l) {
    up = 1 + (m+1) / 64;
    for(int i = 0;i <= n;i++)  L[i].init();
    for(int i = 0;i <= 26;i++) M[i].init();
    for(int i = 1;i <= m;i++)  M[x[i]-'a'].set(i);
    for(int i = 0;i < 26;i++)  MF[i] = M[i].flip();
    l[0] = 0;
    for(int i = 1;i <= m;i++) L[0].set(i);
    for(int i = 1;i <= n;i++) {
        //bits temp = L[i-1] + (L[i-1] & M[y[i] - 'a']);
        L[i] = (L[i-1] + (L[i-1] & M[y[i] - 'a'])) | (L[i-1]&MF[y[i]-'a']);
        l[i] = l[i-1];
        if(L[i][m+1]) ++l[i];
        if(l[i] + n - i <= al) return;
        L[i].reset(m+1);
    }
    //for(int i = 0;i <= n;i++) printf("%d ",l[i]);puts("");
}

int l[maxn];
char a[maxn],b[maxn],s[maxn];
char ans[maxn];

void Print(int n,int m){
    int pos = n,cnt = 0;

    for(int i = m;i >= 1;i--) {
        if(L[pos][i] == 1) continue;
        while(L[pos-1][i] == 0) pos--;
        ans[cnt++] = a[pos];
        pos--;
    }
    //printf("%d\n",cnt);

    ans[cnt] = 0;
    reverse(ans,ans+cnt);
}

int main() {
    //freopen("in.txt","r",stdin);
    //clock_t st = clock();
    int T,CASE = 0;
    scanf("%d",&T);
    while(T--) {
        al = 0;
        scanf("%s",s+1);
        int n = strlen(s+1);
        //printf("%d\n",n);
        for(int i = 1;i < n;i++) {
            if(al > min(i,n-i)) break;
            int p = i,q = n - i;
            strncpy(a+1,s+1,sizeof(char) * i);
            strncpy(b+1,s+1+i,sizeof(char) * (n - i));
            a[i+1] = '\0';
            b[n-i+1] = '\0';
            if(p > q) {
                swap(p,q);
                swap(a,b);
            }
            //printf("%d %d>>\n",i,n-i);
            l[p] = 0;
            ALG_B(p,q,a,b,l);

            if(l[p] > al) {
                Print(p,q);
                al = l[p];
            }
        
        }
        ans[al] = 0;
        printf("Case #%d: %d\n",++CASE,al<<1);
        if(al)  printf("%s%s\n",ans,ans);
    }
    //clock_t ed = clock();
    //printf("%f sec\n",(double)(ed - st) / CLOCKS_PER_SEC);
    return 0;
}
