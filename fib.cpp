#include <bits/stdc++.h>

int fib(ll n) {
    ll x = 0, y = 1, t;
    for(int d = 62 - builtin_clzll(++n);d >= 0;d--) {
        t = (x * x + y * y) % p;
        y = (x + x + y) % p;
        x = t;
        if(n >> d & 1) x = y, y = (y + t) % p;
     }
     return x;
}
