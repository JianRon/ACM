#include <bits/stdc++.h>
using namespace std;


random_device rd;
mt19937 G(rd());

const int maxn = 1e5 + 10;
struct Node{
    int ch[2],key,value,sz,cnt,mx,mi;
    Node() {ch[0] = ch[1] = 0,key = G(),sz = 0,cnt = 0;mx = INT_MIN,mi = INT_MAX;}
    Node(int val) {ch[0] = ch[1] = 0,value = val,key = G(), sz = 1,cnt = 1;mx = val,mi = val;}
};

int tot,root;
Node g[maxn];

int cmp(const Node& a,int val) {
    return a.value < val;
}
void update(int u,int tag) {
    Node& o = g[u];
    o.sz += tag;
    o.cnt += tag;
}
void Prt(int v) {
    printf("%d : value = %d key = %d sz = %d cnt = %d mi = %d mx = %d lson = %d rson = %d\n",
             v,g[v].value,g[v].key,g[v].sz,g[v].cnt,g[v].mi,g[v].mx,g[v].ch[0],g[v].ch[1]);
}
void maintain(int v) {
    if(!v) return;
    Node& o = g[v];
    o.mi = o.value;
    o.mx = o.value;
    o.sz = o.cnt;
    if(o.ch[0]) {
        o.sz += g[o.ch[0]].sz;
        o.mi = min(o.mi,g[o.ch[0]].mi);
        o.mx = max(o.mx,g[o.ch[0]].mx);
    }
    if(o.ch[1]) {
        o.sz += g[o.ch[1]].sz;
        o.mi = min(o.mi,g[o.ch[1]].mi);
        o.mx = max(o.mx,g[o.ch[1]].mx);
    }
}
//  0 left rotate
//  1 right  rotate
void rotate(int& o,int d) {
    int k = g[o].ch[d^1];g[o].ch[d^1] = g[k].ch[d];g[k].ch[d] = o;
    maintain(o),maintain(k);o = k;
}

void insert(int val,int& v) {
    if(!v) {
        v = ++tot;
        g[tot] = Node(val);
        return;
    }
    if(g[v].value == val) {
        update(v,1);
        return;
    }
    int d = cmp(g[v],val);
    insert(val,g[v].ch[d]);
    // printf(" >> %d %d %d\n",g[g[v].ch[d]].value,g[g[v].ch[d]].key,g[v].key);
    if(g[g[v].ch[d]].key > g[v].key) rotate(v,d^1);
    maintain(v);
}

void del(int val,int& v) {
    if(!v) return;
    if(g[v].value == val) {
        if(g[v].cnt > 1) {
            update(v,-1);
            return;
        }
        int d = g[g[v].ch[1]].key > g[g[v].ch[0]].key;
        if(g[v].ch[1] == 0||g[v].ch[0] == 0) v = g[v].ch[0] | g[v].ch[1];
        else rotate(v,d^1),del(val,g[v].ch[d^1]);
    }
    else {
        int d = cmp(g[v],val);
        del(val,g[v].ch[d]);
    }
    maintain(v);
}
int find(int x,int &v){
    if(v == 0) return -1;
    if(x == g[v].value)
        return g[g[v].ch[0]].sz + 1;
    int d = cmp(g[v],x);
    if(d == 1) return find(x,g[v].ch[d]) + g[v].cnt + g[g[v].ch[0]].sz;
    return find(x,g[v].ch[d]);
}

int kth_element(int x,int &v) {
    if(x <= g[g[v].ch[0]].sz + g[v].cnt && x > g[g[v].ch[0]].sz)
        return g[v].value;
    int d = x > g[g[v].ch[0]].sz;
    if(d) x -= g[g[v].ch[0]].sz + g[v].cnt;
    return kth_element(x,g[v].ch[d]);
}

int pre(int x,int &v) {
//    if(!v) {
//        printf("ERROR::PRE::ZERO %d\n",x);
//        Prt(root);
//        return -1;
//    }
//    if(x == 200417) Prt(v);
    if(g[v].value < x&&x <= g[g[v].ch[1]].mi) return g[v].value;
    if(g[v].value >= x) return pre(x,g[v].ch[0]);
    return pre(x,g[v].ch[1]);
}

int suf(int x,int &v) {
//    if(!v) {
//        printf("ERROR::SUF::ZERO %d\n",x);
//        Prt(root);
//        return -1;
//    }
    if(g[v].value > x&&x >= g[g[v].ch[0]].mx) return g[v].value;
    if(g[v].value <= x) return suf(x,g[v].ch[1]);
    return suf(x,g[v].ch[0]);
}


void travel(int v) {
    if(!v) return;
    travel(g[v].ch[0]);
    Prt(v);
    travel(g[v].ch[1]);
}
void cmp() {
    fstream f1("out.txt"),f2("D:/webdownload/input5.out");
    int id = 0;
    vector<int> err;
    while(f1) {
        //cout << (++id) << " : " << endl;
        int a,b;
        f1 >> a;
        f2 >> b;
        //cout << a << " " << b << endl;
        ++id;
        if(a != b) {
            err.push_back(id);
            cerr << "ERROR" << id << " " << a << " " << b << endl;
        }
    }
    cout << "ERR.size " << err.size() << endl;
}
int main() {
//    cmp();

//    freopen("D:/webdownload/input5.in","r",stdin);
//    freopen("out.txt","w",stdout);
//    fstream fin("D:/webdownload/input5.out");
    int q;
    scanf("%d",&q) ;
    while(q--) {
        int opt,x;
        scanf("%d%d",&opt,&x);
        if(opt == 1) insert(x,root);
        else if(opt == 2) del(x,root);
        else {
            int res;
            if(opt == 3) res = find(x,root);
            else if(opt == 4) res = kth_element(x,root);
            else if(opt == 5) res = pre(x,root);
            else res = suf(x,root);
            printf("%d\n",res);
        }
        //travel(root);
        //Prt(0);
    }
    return 0;
}
