#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10;

using int64 = long long;

char s[N];

std::vector<int> pos[N * 2];
std::vector<int> cnt,  a;
int balance;
int64 ret;

void add(int v) {
  a.push_back(v);
  balance += v;
  int delta = 0;
  if (pos[balance - 1].empty()) delta = pos[balance].size();
  else {
    auto p = std::upper_bound(pos[balance].begin(), pos[balance].end(), pos[balance - 1].back()) - pos[balance].begin();
    delta = pos[balance].size() - p;
  }
  pos[balance].push_back(a.size());
  cnt.push_back(delta);
  ret += delta;
}

void del() {
  ret -= cnt.back();
  pos[balance].pop_back();
  balance -= a.back();
  cnt.pop_back();
  a.pop_back();
}

int main() {
  scanf("%s", s);
  balance = N;
  pos[balance].push_back(0);
  for (int i = 0; s[i]; ++i) {
    if (s[i] == ')') add(-1);
    else if (s[i] == '(') add(1);
    else del();
    printf("%lld\n", ret);
  }
  return 0;
}
