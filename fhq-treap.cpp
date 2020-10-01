namespace Treap {
    mt19937 gen;
    int ch[maxn][2];
    long long val[maxn];
    int key[maxn];
    int sz[maxn], tot, root;
    int newnode(long long x) {
        ++tot;
        ch[tot][0] = ch[tot][1] = 0;
        val[tot] = x;
        sz[tot] = 1;
        key[tot] = gen();
        return tot;
    }
    void maintain(int x) {
        sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
    }
    int merge(int x,int y) {
        if(!x || !y) return x | y;
        if(key[x] < key[y]) {
            ch[x][1] = merge(ch[x][1], y);
            maintain(x);
            return x;
        }
        else {
            ch[y][0] = merge(x, ch[y][0]);
            maintain(y);
            return y;
        }
    }
    void split(int now, long long k, int &x, int &y) {
        if(!now) x = y = 0;
        else {
            if(val[now] <= k)
                x = now,split(ch[now][1], k, ch[now][1], y);
            else
                y = now,split(ch[now][0], k, x, ch[now][0]);
            maintain(now);
        }
    }
    int order_of_key(long long k) {
        int x, y, res;
        split(root, k, x, y);
        res = sz[y];
        root = merge(x, y);
        return res;
    }
    void insert(long long k) {
        int x, y;
        split(root, k, x, y);
        root = merge(merge(x, newnode(k)), y);
    }
    void clear() {
        tot = 0;
        root = 0;
    }
}
