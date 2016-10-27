// x=AO=CO <= BO=DO=y, AB<BC<CD<AD, a<b<c<d
// x=\sqrt{2a^2 + 2d^2 - 4y^2} / 2 = \sqrt{2b^2 + 2c^2 - 4y^2} / 2
// a^2 + d^2 = b^2 + c^2
// a^2 + d^2 = 2(x^2+y^2) => u^2+v^2=x^2+y^2, a=u-v, d=u+v, u > x
// r(n) = #{(x, y)| x^2 + y^2 = n}, f(n) = n(n^2-3n+2)/6
// => ans = \sum_{i=1}^{n/4} f(r(i))
#include <bits/stdc++.h>

const int N = 100000000 + 10;

int p[N], mp[N], m;
std::vector<int> ip;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!mp[i]) mp[i] = p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
  for (int i = 0; i < m; ++i) {
    if (p[i] % 4 == 1) ip.push_back(p[i]);
  }
  p[0] = 0; p[1] = 1;
  for (int i = 2; i < N; ++i) {
    int n = i;
    if (n % 2 == 0) p[i] = p[i - 1];
    else {
      int last = mp[n], cnt = 1, flag = true;
      for (n /= mp[n]; n != 1 && flag; n /= mp[n]) {
        if (last == mp[n]) ++cnt;
        else {
          if (last % 4 == 1) flag = false;
          else if (cnt & 1) flag = false;
          last = mp[n], cnt = 1;
        }
      }
      if (last % 4 == 1 || cnt % 2 == 1) flag = false;
      p[i] = p[i - 1] + flag;
    }
  }
}

inline long f(long n) {
  return n * (n * n - n * 3 + 2) / 6;
}

inline long calc(long n, long m, long B) {
  long ret = 0;
  if (B & 1) {
    if (B == 1) return 0;
    for (int s = 1; m <= n; m *= 2, s *= -1) {
      ret += p[n / m] * f((B - s) / 2);
    }
  } else {
    if (B == 2) return 0;
    for (; m <= n; m *= 2) ret += p[n / m];
    ret *= f(B / 2);
  }
  return ret;
}

void dfs1(int d, long upp, long now, int B);
bool dfs2(int d, long upp, long now, int B);
long ret;

void dfs1(int d, long upp, long now, int B) {
  ret += calc(upp, now, B);
  for (; d < m; ++d) {
    if (!dfs2(d, upp, now, B)) break;
  }
}

bool dfs2(int d, long upp, long now, int B) {
  if (d == m || ip[d] > upp / now) return false;
  for (int e = 1; ; ++e) {
    now *= ip[d];
    dfs1(d + 1, upp, now, B * (e + 1));
    if (ip[d] > upp / now) break;
  }
  return true;
}

long run(long n) {
  m = ip.size();
  ret = 0;
  dfs1(0, n / 4, 1, 1);
  return ret;
}

int main() {
  sieve();
  std::cout << run(10000) << std::endl;
  std::cout << run(1000000) << std::endl;
  std::cout << run(10000000000ll) << std::endl;
  return 0;
}
