#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e5;

char s[N];
int last[26];

int main() {
  int n;
  scanf("%d%s", &n, s);
  for (int i = 0; i < 26; ++i) last[i] = -1;
  int best_l = -1, best_r = -1;
  double best = 1e5;
  for (int i = 0; i < n; ++i) {
    last[s[i] - 'a'] = i;
    std::vector<int> p;
    for (int j = 0; j < 26; ++j) if (last[j] != -1) {
      p.push_back(last[j]);
    }
    std::sort(p.begin(), p.end());
    std::reverse(p.begin(), p.end());
    for (size_t j = 1; j < p.size(); ++j) {
      double v = 1.0 * j / (i - p[j]);
      if (v < best) {
        best = v;
        best_r = i;
        best_l = p[j] + 1;
      }
    }
    double v = 1.0 * p.size() / (i + 1);
    if (v < best) {
      best = v;
      best_r = i;
      best_l = 0;
    }
  }
  printf("%d %d\n", best_l + 1, best_r + 1);
  return 0;
}
