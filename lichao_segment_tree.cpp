#include<bits/stdc++.h>
#define fst first
#define snd second
#define lson(v) v << 1
#define rson(v) v << 1 | 1
using namespace std;

typedef pair<int,int> pii;
typedef long long ll;
const int maxn = 1e6 + 10;
pii seg[maxn << 2];
int have[maxn << 2];
int sz;
void init(int n) {
    for(sz=1;sz < n;sz <<= 1);
    memset(have,0,sizeof(int) * (sz << 1));
}
ll val(pii a,int x) {
    return 1LL * a.fst * x + a.snd;
}
int cmp(pii a,pii b,int x) {
    return val(a,x) > val(b,x);
}
void update(int ql,int qr,pii va,int l = 1,int r = sz,int v = 1) {
    int mid = (l + r) >> 1;
    if(ql <= l&&r <= qr) {
        if(!have[v]) {
            have[v] = 1;
            seg[v] = va;
            return;
        }
        pii a = va,b = seg[v];
        if(a.fst > b.fst) swap(a,b);
        int c1 = cmp(a,b,l);
        int c2 = cmp(a,b,r);
        if(c1^c2) {
            if(1LL * a.snd - b.snd <= 1LL * mid * (b.fst - a.fst)) {
                update(ql,qr,a,l,mid,lson(v));
                seg[v] = b;
            }
            else {
                update(ql,qr,b,mid+1,r,rson(v));
                seg[v] = a;
            }
        }
        else {
            seg[v] = c1 ? a : b;
        }
        return;
    }
    if(ql <= mid) update(ql,qr,va,l,mid,lson(v));
    if(qr > mid) update(ql,qr,va,mid+1,r,rson(v));
}
ll query(int v) {
    int x = v;
    v = x + sz - 1;
    ll res = LLONG_MIN;
    while(v >= 1) {
        if(have[v]) res = max(val(seg[v],x),res);
        v >>= 1;
    }
    return res;
}

int n,y;
int b[maxn];
int ans[maxn];

int main() {
    while(scanf("%d%d",&n,&y) != EOF) {

        for(int i = 1;i <= n;++i) scanf("%d",&b[i]);
        sort(b + 1,b + 1 + n);
        init(y);
        b[0] = -y;
        for(int x = y,cur = n;x >= 1;--x) {
            ll last = query(x);
            ll res = max((ll)b[cur] + y,last);
            ll tmp;
            while(cur&&res >= (tmp = max((ll)b[cur-1] + y,max(last,1LL * (n - cur + 1) * x + b[cur])))) {
                res = tmp;
                update(1,sz,pii(n - cur + 1,b[cur]));

                last = query(x);
                --cur;
            }
            ans[x] = (int)res;
        }
        for(int i = 1;i <= y;++i) printf("%d%c",ans[i],i == y ?'\n' : ' ');
    }
    return 0;
}

