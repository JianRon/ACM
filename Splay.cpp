#include<bits/stdc++.h>
#define son(v,d) node[v].son[d]
#define sz(v)    node[v].sz
#define mx(v)    node[v].mx
#define val(v)   node[v].val
#define key(v)   node[v].key
#define lazy(v)  node[v].lazy
using namespace std;

const int maxn = 1e5 + 10;
struct Node {
    int son[2];
    int key,mx;
    int val,lazy;
    int sz;
    Node() {}
}node[maxn << 1];

int tot;
int newnode(int key,int val) {
    ++tot;
    node[tot].key = key;
    node[tot].val = val;
    node[tot].sz  = 1;
    node[tot].lazy = 0;
}

void pushup(int o) {
    if(!o) return;
    sz(o) = 1 + sz(son(o,0)) + sz(son(o,1));
    mx(o) = max(max(key(o),key(son(o,0))),key(son(o,1)));
}

void pushdown(int o) {
    if(lazy(o)) {
        key(son(o,0)) = max(key(son(o,0)),lazy(o));
        key(son(o,1)) = max(key(son(o,1)),lazy(o));
        lazy(son(o,0)) = max(lazy(son(o,0)),lazy(o));
        lazy(son(o,1)) = max(lazy(son(o,1)),lazy(o));
        lazy(o) = 0;
    }
}

void rotate(int &o,int d) {
    int k = son(o,d^1);son(o,d^1) = son(k,d);son(k,d) = o;
    pushup(o);pushup(k);o = k;
}
int get_dir(int o,int k) {
    return k == sz(son(o,0)) + 1 ? -1 : (k > sz(son(o,0)) + 1);
}

void splay(int& o,int k) {
    int d = get_dir(o,k);
    if(d == 1) k -= sz(son(o,0)) + 1;
    if(d != -1) {
        int& o2 = son(o,d);
        int d2 = get_dir(o2,k);
        int k2 = d2 ?  k - sz(son(o2,0)) - 1 : k;
        if(d2 != -1) {
            splay(son(o2,d2),k2);
            if(d == d2) rotate(o,d ^ 1);
            else rotate(o2,d);
        }
        rotate(o, d ^ 1);
    }
}

void split(int& o,int k,int& left,int& right) {
    left = right = 0;
    if(!o) return;
    splay(o,k);
    left = o;
    right = son(o,1);
    son(o,1) = 0;
    pushup(left);
}

int& merge(int &left,int right) {
    if(!left) return left = right;
    splay(left,sz(left));
    son(left,1) = right;
    pushup(left);
    return left;
}

void insert(int &o,int k,int rt) {
    int left = 0,right = 0;
    split(o,k-1,left,right);
    merge(merge(left,rt),right);
}

int lower_bound(int& o,int v) {
    int k = 0,tmp = o;
    while(true) {
        if(mx(son(tmp,0)) >= v) tmp = son(tmp,0);
        if(val(tmp) >= v) {
            ++k;
            break;
        }
        else {
            k += 1 + sz(son(tmp,0));
            tmp = son(tmp, 1);
        }
    }
    splay(o,k);
    return k;
}
bool find(int &o,int v,int &k) {
    k = lower_bound(o, v);
    return val(o) == v;
}

int main() {

    return 0;
}
