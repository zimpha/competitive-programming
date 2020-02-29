#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

std::vector<std::vector<int>> perm;
std::map<std::vector<int>, int> mp;

void prepare() {
  std::vector<int> p = {0, 1, 2, 3, 4, 5};
  do {
    perm.push_back(p);
    mp[p] = perm.size() - 1;
  } while (std::next_permutation(p.begin(), p.end()));
}

std::vector<int> encode(std::vector<int> a) {
  std::sort(a.begin(), a.end());
  int sum = 0;
  for (auto &x: a) sum ^= x;
  for (size_t i = 0; i < a.size(); i += 6) {
    if (i / 6 % 2 == 1) {
      std::reverse(a.begin() + i, a.begin() + std::min(i + 6, a.size()));
    }
    std::vector<int> b(6);
    if (i + 6 <= a.size()) {
      for (int j = 0; j < 6; ++j) b[j] = a[i + perm[sum][j]];
      for (int j = 0; j < 6; ++j) a[i + j] = b[j];
    }
  }
  return a;
}

int get_idx(const std::vector<int> &a, int x, int e) {
  std::vector<std::pair<int, int>> b(6);
  for (int i = 0; i < 6; ++i) b[i] = {a[x + i], i};
  std::sort(b.begin(), b.end());
  if (e) std::reverse(b.begin(), b.end());
  std::vector<int> p(6);
  for (int i = 0; i < 6; ++i) p[b[i].second] = i;
  return mp[p];
}

std::vector<int> decode(std::vector<int> a) {
  if (encode(a) == a) return a;
  int blocks = (a.size() + 1) / 6;
  for (int i = 0; i < blocks; ++i) {
    // missing in i-th block
    int last = -1, valid = true;
    for (int j = 0; j < blocks; ++j) if (j != i) {
      int now = j < i ? get_idx(a, j * 6, j & 1) : get_idx(a, 6 * j - 1, j & 1);
      if (last == -1) last = now;
      if (now != last) valid = false;
    }
    if (valid) {
      auto b = a;
      for (auto &x: a) last ^= x;
      b.push_back(last);
      return b;
    }
  }
  int sum = get_idx(a, 0, 0);
  for (auto &x: a) sum ^= x;
  a.push_back(sum);
  return a;
}

int main() {
  prepare();
  static char run[20];
  int T;
  scanf("%s%d", run, &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    if (run[0] == 't') a = encode(a);
    else a = decode(a);
    for (size_t i = 0; i < a.size(); ++i) {
      if (i) putchar(' ');
      printf("%d", a[i]);
    }
    puts("");
  }
  return 0;
}
