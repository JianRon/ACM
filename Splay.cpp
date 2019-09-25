#include<bits/stdc++.h>
#define son(v,d) node[v].son[d]
#define sz(v)    node[v].sz
#define mx(v)    node[v].mx
#define mi(v)    node[v].mi
#define val(v,d)   node[v].val[d]
#define mxval(v,d)   node[v].mxval[d]
#define key(v)   node[v].key
#define lazy(v,d)  node[v].lazy[d]
using namespace std;

typedef long long ll;
const int maxn = 1e5 + 10;
const ll  pow32 = 1LL << 32;
struct Fractor {
    ll a, b; /// a / b
    Fractor() {}
    Fractor(ll a,ll b) : a(a), b(b) {}
    bool operator < (const Fractor& other) const {
        if(a == -1) return false;
        if(other.a == -1) return true;
        if(a == pow32 && other.b == pow32) return false;
        if(other.a == pow32 && b == pow32) return true;
        return a * other.b < b * other.a;
    }
    bool operator == (const Fractor& other) const {
        return a == other.a && b == other.b;
    }
    bool operator <= (const Fractor& other) const {
        return *this == other || *this < other;
    }
    bool operator >= (const Fractor& other) const {
        return ! (*this < other);
    }
};
void norm(Fractor& a) {
    ll g = __gcd(a.a,a.b);
    a.a /= g,a.b /= g;
}

struct Node {
    int son[2];
    Fractor key, mx, mi;
    ll val[2],lazy[2],mxval[2];
    int sz;
    Node() {}
}node[maxn << 1];

void travel(int root) {
    if(son(root,0)) travel(son(root,0));
    printf("%d :: %4lld/%lld 0->%lld 1->%lld\n",root, key(root).a,key(root).b,val(root,0),val(root,1));
    if(son(root,1)) travel(son(root,1));
}
int tot;
int newnode(Fractor key,ll* val) {
    ++tot;
    node[tot].mi = node[tot].mx = node[tot].key = key;
    node[tot].sz  = 1;
    mxval(tot,0) = val(tot,0) = val[0];
    mxval(tot,1) = val(tot,1) = val[1];
    node[tot].lazy[0] = node[tot].lazy[1] = 0;
    return tot;
}

void pushup(int o) {
    if(!o) return;
    mi(o) = mx(o) = key(o);
    sz(o) = 1;
    mxval(o,0) = val(o,0);
    mxval(o,1) = val(o,1);
    for(int i : {0,1}) if(son(o,i)){
        sz(o) += sz(son(o,i));
        mx(o) =  max(mx(o),mx(son(o,i)));
        mi(o) =  min(mi(o),mi(son(o,i)));
        for(int d : {0,1})
        mxval(o,d) = max(mxval(o,d),mxval(son(o,i),d));
    }
}

void pushdown(int o) {
    for(int d : {0,1}) {
        if(lazy(o,d)) {
            for(int s : {0,1}) {
//                printf("%d %d -> %d\n",o,s,son(o,s));
                if(son(o,s)) {
                        val(son(o,s),d) = max(val(son(o,s),d),lazy(o,d));
                        lazy(son(o,s),d) = max(lazy(son(o,s),d),lazy(o,d));
                }
            }
            lazy(o, d) = 0;
        }
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
    assert(k != 0);
    pushdown(o);
    int d = get_dir(o,k);
    if(d == 1) k -= sz(son(o,0)) + 1;
    if(d != -1) {
        int& o2 = son(o,d);
        pushdown(o2);
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

void split(int o,int k,int& left,int& right) {
    left = right = 0;
    if(!o) return;
    if(!k) {
        right = o;
        return;
    }
    splay(o,k);
    left = o;
    right = son(o,1);
    son(o,1) = 0;
    pushup(left);
}

int& merge(int &left,int right) {
    if(!left) return left = right;
//    printf("MERGE:: left > %d\n",left);
    splay(left,sz(left));
    son(left,1) = right;
    pushup(left);
    return left;
}

void insert(int &o,int k,int rt) {
    int left = 0,right = 0;
    --k;
    if(k) {
        split(o,k,left,right);
        o = merge(merge(left,rt),right);
    }
    else {
//        printf("INSERT:: rt > %d\n",rt);
        o = merge(rt,o);
    }
}

int suf(int& o,Fractor v) {
    int k = 0,tmp = o;
    while(true) {
//        printf("SUF:: %lld %lld %d\n",v.a,v.b,tmp);
        assert(tmp != 0);
        if(son(tmp,0)&&v <= mx(son(tmp,0))) {
            tmp = son(tmp,0);
        }
        else if(v <= key(tmp)) {
            k += 1 + sz(son(tmp,0));
            break;
        }
        else {
            k += 1 + sz(son(tmp,0));
            tmp = son(tmp, 1);
        }
    }
//    printf("SUF::%d %d\n",sz(o),k);
    splay(o,k);
//    puts("ok");
    return k;
}
int pre(int &o,Fractor v) {
    int k =0 ,tmp = o;
    while(true) {
//        printf("PRE:: %lld/%lld %lld/%lld %d\n",v.a,v.b,mi(son(tmp,1)).a,mi(son(tmp,1)).b,tmp);
        if(son(tmp,1)&&v >= mi(son(tmp,1))) {
            k += 1 + sz(son(tmp,0));
            tmp = son(tmp,1);
        }
        else if(v >= key(tmp)) {
            k += 1 + sz(son(tmp,0));
            break;
        }
        else {
            tmp = son(tmp,0);
        }
    }
//    printf("%d %d\n",sz(o),k);
    splay(o, k);
    return k;
}

bool find_suf(int &o,Fractor v,int &k) {
    k = suf(o, v);
    return key(o) == v;
}
bool find_pre(int &o,Fractor v,int &k) {
    k = pre(o, v);
    return key(o) == v;
}

/// [l,r]
ll ask(int &o, int l,int r,int d) {
    int left = 0,mid = 0,right = 0;
    split(o,l-1,left,mid);
    split(mid,r-l+1,mid,right);
//    puts("left >> ");travel(left);
//    puts("mid >> ");travel(mid);
//    puts("right >> ");travel(right);
    ll res = mxval(mid,d);
//    printf("%lld\n",res);
    o = merge(left,merge(mid,right));
    return res;
}
void update(int &o, int l, int r, ll v,int d) {
    int left = 0,mid = 0,right = 0;
    split(o,l-1,left,mid);
    split(mid,r-l+1,mid,right);
//    printf("%d %d %d\n",sz(left),sz(mid),sz(right));
    val(mid,d) = max(val(mid,d),v);
    lazy(mid,d) = max(lazy(mid,d),v);
    o = merge(left,merge(mid,right));
}

int main() {
    int n;
    char cmd[2];
    scanf("%d",&n);
    ll last = 0;
    ll val[2] = {0};
    int root = newnode(Fractor(-1,0),val);
    insert(root,1,newnode(Fractor(0,1),val));
//    travel(root);
    while(n--) {
        Fractor s,t;
        ll h;
        scanf("%s%lld%lld%lld%lld",cmd,&s.a,&s.b,&t.a,&t.b);
        s.a ^= last;
        s.b ^= last;
        t.a ^= last;
        t.b ^= last;
        norm(s);
        norm(t);
//        printf("s,t :: %lld/%lld %lld/%lld\n",s.a,s.b,t.a,t.b);
        int l = 0,r = 0,left;
        if(cmd[0] == 'S') {
            ll res = 0;
            find_suf(root,s,l);
            find_suf(root,t,r);
//            printf("suf::[%d %d]\n",l,r);
            res = max(res,ask(root,l,r,1));
            find_pre(root,s,l);
            find_pre(root,t,r);
//            printf("pre::[%d %d]\n",l,r);
            res = max(res,ask(root,l,r,0));
            printf("%lld\n",last = res);
        }
        else {
            int nothing;
            scanf("%lld",&h);
            h ^= last;
            bool el = find_suf(root,s,l);
//            puts("1");
            if(!el) {
                val[1] = val(root,1);
                find_pre(root,s,nothing);
//                puts("2");
                val[0] = val(root,0);
//                printf("l == %d\n",l);
                insert(root,l,newnode(s,val));
//                travel(root);
            }
            bool er = find_suf(root,t,r);
            if(!er) {
                val[1] = val(root,1);
                find_pre(root,t,nothing);
                val[0] = val(root,0);
                insert(root,r,newnode(t,val));
//                travel(root);
            }
//            printf("%d %d\n",l,r);
            update(root,l,r-1,h,0);
//            travel(root);
            update(root,l+1,r,h,1);
        }
//        puts("fineshed");travel(root);
    }
    return 0;
}
