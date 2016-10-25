#include <bits/stdc++.h>

const int N = 630000;

std::vector<std::pair<int, int>> pd[N];
int p[N], mp[N], m;

void sieve() {
  for (int i = 2; i < N; ++i) if (!mp[i]) {
    p[m++] = i;
    for (int j = i; j < N; j += i) {
      if (!mp[j]) mp[j] = i;
    }
  }
  for (int i = 2; i < N; ++i) {
    std::vector<std::pair<int, int>> &v = pd[i];
    for (int n = i; n != 1; n /= mp[n]) {
      if (v.empty() || v.back().first != mp[n]) v.push_back({mp[n], 1});
      else ++v.back().second;
    }
  }
}

inline long cub(long x) {return x * x * x;}
inline long sqr(long x) {return x * x;}
inline int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
std::set<int> uniq;
std::map<int, int> phi;

bool check(long n) {
  int g = 0;
  for (auto &&x: phi) g = gcd(g, x.second);
  //if (g == 1) std::cout << n << std::endl;
  return g == 1;
}

long ret;
void dfs1(long upp, int d, long g, long n);
bool dfs2(long upp, int d, long g, long n);

void dfs1(long upp, int d, long g, long n) {
  ret += g == 1 && uniq.empty() && check(n);
  for (; d >= 0; --d) {
    if ((long)p[d] * p[d] > upp) continue;
    if (!dfs2(upp, d, g, n)) break;
  }
}

bool dfs2(long upp, int d, long g, long n) {
  if (uniq.size() && p[d] < *uniq.rbegin()) return false;
  std::vector<int> add, del;
  long pw = (long)p[d] * p[d];
  for (auto &&e: pd[p[d] - 1]) {
    if (uniq.count(e.first)) {
      uniq.erase(e.first);
      del.push_back(e.first);
    } else if (!phi.count(e.first) && e.second == 1) {
      uniq.insert(e.first);
      add.push_back(e.first);
    }
    phi[e.first] += e.second;
  }
  if (uniq.count(p[d])) {
    uniq.erase(p[d]);
    del.push_back(p[d]);
  }
  int e = 2;
  if (!phi.count(p[d])) ++e, pw *= p[d];
  int cache = phi[p[d]];
  for (; pw <= upp; ++e) {
    phi[p[d]] = cache + e - 1;
    dfs1(upp / pw, d - 1, gcd(g, e), 1);
    if (pw > upp / p[d]) break;
    pw *= p[d];
  }
  phi[p[d]] = cache;
  for (auto &&e: pd[p[d] - 1]) {
    auto it = phi.find(e.first);
    it->second -= e.second;
    if (it->second == 0) phi.erase(it);
  }
  auto it = phi.find(p[d]);
  if (it->second == 0) phi.erase(it);
  for (auto &&v: add) uniq.erase(v);
  for (auto &&v: del) uniq.insert(v);
  return true;
}

long run(long n) {
  ret = 0;
  dfs1(n, m - 1, 0, 1);
  return ret;
}

int main() {
  sieve();
  std::cout << run(10000) << std::endl;
  std::cout << run(100000000) << std::endl;
  std::cout << run(1000000000000000000ll) << std::endl;
  return 0;
}
