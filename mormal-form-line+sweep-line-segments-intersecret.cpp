#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef pair<int,int> pii;
const int maxn = 3e5 + 10;


// A*X + B*Y + C = 0
struct line {
    int A, B, C;
    line() {}
    line(int x1,int y1,int x2,int y2) {
        A = y1 - y2;
        B = x2 - x1;
        C = -A * x1 - B * y1;
        if(A < 0) A = -A, B = -B, C = -C;
        int g = __gcd(abs(A), __gcd(abs(B), abs(C)));
        A /= g, B /= g, C /= g;
    }
};

bool operator == (const line& a, const line& b) {
    return a.A == b.A && a.B == b.B && a.C == b.C;
}

double x;
bool operator < (const line& a, const line& b) {
    double y1 = (-a.A * x - a.C) / a.B;
    double y2 = (-b.A * x - b.C) / b.B;
    return y1 < y2;
}

struct car {
    int x, y, dx, dy, s;
    line l;
    double vx, vy;
}a[maxn];


long long det(int a, int b, int c, int d){
	return a * 1ll * d - b * 1ll * c;
}

bool inter(const line &a, const line &b, long long &D, long long &Dx, long long &Dy){
	D = det(a.A, a.B, b.A, b.B);
	if (D == 0) return false;
	Dx = -det(a.C, a.B, b.C, b.B);
	Dy = -det(a.A, a.C, b.A, b.C);
	return true;
}

int sg(int x){
	return x < 0 ? -1 : 1;
}

int sg(long long a, long long b, int c){
	if (b < 0) a = -a, b = -b;
	return a - c * b < 0 ? -1 : (a - c * b > 0);
}

bool inter(int i, int j, double &len){
	if (i == -1 || j == -1)
		return false;
	long long D, Dx, Dy;
	if (!inter(a[i].l, a[j].l, D, Dx, Dy))
		return false;
	if (sg(Dx, D, a[i].x) != 0 && sg(a[i].dx) != sg(Dx, D, a[i].x))
		return false;
	if (sg(Dx, D, a[j].x) != 0 && sg(a[j].dx) != sg(Dx, D, a[j].x))
		return false;
	double x = Dx / double(D);
	double y = Dy / double(D);
	double di = (a[i].x - x) * (a[i].x - x) + (a[i].y - y) * (a[i].y - y);
	double dj = (a[j].x - x) * (a[j].x - x) + (a[j].y - y) * (a[j].y - y);
	return len * len >= di / a[i].s && len * len >= dj / a[j].s;
}
set<pair<line,int>> q;
void  get_neighbours(int i,int &l,int &r) {
    l = r = -1;
    auto it = q.lower_bound({a[i].l, -1});
    if(it != q.end()) r = it->y;
    if(!q.empty()&&it != q.begin()) {
        --it;
        l = it->y;
    }
}
vector<set<pair<line, int>>::iterator> del;
vector<pair<double,pair<int,int>>> g;
int n;
bool check(double t) {
    del.resize(n);
    g.clear();
    for(int i = 1;i <= n;++i) {
        double x1 = a[i].x;
        double x2 = a[i].x + a[i].vx * t;
        if(x1 > x2) swap(x1, x2);
        g.push_back({x1,{i, 0}});
        g.push_back({x2,{i, 1}});
    }
    sort(g.begin(),g.end());
    q.clear();
    for(const auto& u : g) {
        x = u.x;
        int i = u.y.x;
        int l, r;

        if(u.y.y == 0) {
            get_neighbours(i, l, r);
            if(r != -1&&a[r].l == a[i].l) return true;
            if(inter(i, l, t)) return true;
            if(inter(i, r, t)) return true;
            del[i] = q.insert({a[i].l, i}).x;
        }
        else {
            q.erase(del[i]);
            get_neighbours(i, l, r);
            if(inter(l, r, t)) return true;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for(int i = 1;i <= n;++i) {
        scanf("%d%d%d%d%d", &a[i].x, &a[i].y, &a[i].dx, &a[i].dy, &a[i].s);
        a[i].l = line(a[i].x, a[i].y, a[i].x + a[i].dx, a[i].y + a[i].dy);
        double dis = sqrt(a[i].dx * a[i].dx + a[i].dy * a[i].dy);
        a[i].vx = a[i].dx / dis * a[i].s;
        a[i].vy = a[i].dy / dis * a[i].s;
        a[i].s *= a[i].s;
    }
    double l = 0,r = 1e13;
    int flag = 0;
    for(int i = 0;i < 100;++i) {
        double m = (l + r) / 2;
//        printf("%.16f %d\n", m, i);
        if(check(m)) {
            flag = 1,r = m;
//            puts("1");
        }
        else {
//            puts("0");
            l = m;
        }
    }
    if(flag) printf("%.16f\n", l);
    else puts("No show :(");
	return 0;
}
