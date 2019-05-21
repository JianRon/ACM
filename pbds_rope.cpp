// Loj :: n = 1e5 q = 1e5 tims 840ms

#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
typedef long long ll;
rope<int> s,rs,tmp;

int main() {
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i = 1;i <= n;i++) s.push_back(i),rs.push_back(n-i+1);
    while(q--) {
        int l, r;
        scanf("%d%d",&l,&r);
        l--,r--;
        tmp = s.substr(l,r-l+1);
        s = s.substr(0,l) + rs.substr(n-r-1,r-l+1) + s.substr(r+1,n-r-1);
        rs = rs.substr(0,n-r-1) + tmp + rs.substr(n-l,l);
    }
    for(int i = 0;i < n;i++) {
        printf("%d%c",s[i],i == n-1?'\n':' ');
    }
}
