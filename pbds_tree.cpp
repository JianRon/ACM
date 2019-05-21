/*
t.insert(*);//插入元素
t.erase(*);//删除元素
t.order_of_key(*);//求k在树中是第几大
t.find_by_order(*);//求树中的第k大
t.lower_bound(*);//求前驱
t.upper_bound(*);//求后继
不可有重复元素，可以用 pair解决，第二维存时间戳
下标从0开始
*/

// can't be deleted
#define _EXT_CODECVT_SPECIALIZATIONS_H 1
#define _EXT_ENC_FILEBUF_H 1
#undef __MINGW32__

#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> Tree;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> Tree;
int main() {
    int q;
    scanf("%d",&q);
    Tree t;
    int id = 0;
    while(q--) {
        int opt;
        ll x;
        id++;
        scanf("%d%lld",&opt,&x);
        if(opt == 1) t.insert((x << 20) + id);
        else if(opt == 2) t.erase(t.lower_bound((x<<20)));
        else {
            ll res;
            if(opt == 3) res = t.order_of_key((x<<20)) + 1;
            if(opt == 4) res = *t.find_by_order(x-1) >> 20;
            if(opt == 5) res = *--t.lower_bound(x << 20) >> 20;
            if(opt == 6) res = *t.lower_bound((x+1) << 20) >> 20;
            printf("%lld\n",res);
        }
    }
}
