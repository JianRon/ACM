/*
pb_ds--treap

t.insert(*);//插入元素
t.erase(*);//删除元素
t.order_of_key(*);//求k在树中是第几大(返回严格小的数量)
t.find_by_order(*);//求树中的第k大
t.lower_bound(*);//求前驱
t.upper_bound(*);//求后继
不可有重复元素，可以用 pair解决，第二维存时间戳
下标从0开始
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
template<typename T>
using Tree = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

int main() {
    int q;
    scanf("%d",&q);
    Tree<ll> t;
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
