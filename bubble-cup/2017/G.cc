#include <cstdio>
#include <unordered_set>
#include <unordered_map>

using uint64 = unsigned long long;

const int N = 100, seed = 65537;
char s[N];

std::unordered_map<uint64, int> words;
std::unordered_set<uint64> mark;

int dfs(int d, uint64 hs) {
  if (s[d] == 0) {
    if (mark.count(hs)) return 0;
    mark.insert(hs);
    auto it = words.find(hs);
    if (it == words.end()) return 0;
    else return it->second;
  }
  int ret = 0;
  if (s[d] == '?') {
    ret += dfs(d + 1, hs);
    for (char c = 'a'; c <= 'e'; ++c) {
      ret += dfs(d + 1, hs * seed + c);
    }
  } else {
    ret += dfs(d + 1, hs * seed + s[d]);
  }
  return ret;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    uint64 hs = 0;
    for (int j = 0; s[j]; ++j) {
      hs = hs * seed + s[j];
    }
    words[hs] += 1;
  }
  for (int i = 0; i < m; ++i) {
    scanf("%s", s);
    mark.clear();
    printf("%d\n", dfs(0, 0));
  }
  return 0;
}