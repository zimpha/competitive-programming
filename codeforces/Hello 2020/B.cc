#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> st, ed;
  for (int i = 0; i < n; ++i) {
    int m;
    scanf("%d", &m);
    std::vector<int> s(m);
    for (int j = 0; j < m; ++j) scanf("%d", &s[j]);
    bool valid = true;
    for (int j = 1; j < m; ++j) {
      if (s[j - 1] < s[j]) valid = false;
    }
    if (valid) {
      st.push_back(s[0]);
      ed.push_back(s.back());
    }
  }
  std::sort(st.begin(), st.end());
  std::sort(ed.begin(), ed.end());
  int64 sum = (int64)n * n;
  for (size_t i = 0, j = 0; i < ed.size(); ++i) {
    while (j < st.size() && st[j] <= ed[i]) ++j;
    sum -= j;
  }
  printf("%lld\n", sum);
  return 0;
}
