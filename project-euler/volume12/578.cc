#include <bits/stdc++.h>

using ll = long long;

inline ll sqr(ll x) {return x * x;}
inline ll cub(ll x) {return x * x * x;}

const int SZ = 100000000, MN = 10000;
int pi[SZ], pl[SZ], m;
void sieve() {
    m = 0; for (int i = 2; i < SZ; ++ i) pi[i] = 1;
    for (int i = 2; i < SZ; ++i) {
        if (pi[i]) pl[m++] = i;
        for (int j = 0; j < m && pl[j] * i < SZ; ++j) {
            pi[pl[j] * i] = 0;
            if (i % pl[j] == 0) break;
        }
    }
    for (int i = 2; i < SZ; ++ i) pi[i] += pi[i - 1];
}
std::map<ll, ll> cache;
ll phi(ll x, ll a) {
    if (a == 1 || !x) return (x + 1) / 2;
    ll &r = cache[(x << 10) + a]; if (r) return r;
    return r = phi(x, a - 1) - phi(x / pl[a - 1], a - 1);
}
ll get_pi(ll n) {
    if (n < SZ) return pi[n];
    ll a = get_pi(pow(n, .25));
    ll b = get_pi(sqrt(n));
    ll c = get_pi(pow(n, 1./3));
    ll r = phi(n, a) + (b + a - 2) * (b - a + 1) / 2;
    for (int i = a + 1; i <= b; ++i) {
        ll w = n / pl[i - 1];
        r -= get_pi(w);
        if (i <= c) {
            int upp = get_pi(sqrt(w));
            for (int j = i; j <= upp; ++j) r += j - 1 - get_pi(w / pl[j - 1]);
        }
    }
    return r;
}

ll solve(ll n, int d = 0, int e = 43) {
    ll p = pl[d], ret = 0;
    if (p * p > n) return std::max<ll>(0, get_pi(n) - d) + 1;
    for (int j = 0; j <= e && n >= 1; ++j, n /= p) {
        ret += solve(n, d + 1, j ? j : e);
    }
    return ret;
}

int main() {
    sieve();
    std::cout << solve(100) << std::endl;
    std::cout << solve(1000000) << std::endl;
    std::cout << solve(10000000000000ll) << std::endl;
    return 0;
}
