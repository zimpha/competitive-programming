#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;

int main() {
  int ret = 0;
  for (int k = 1; k <= 25; ++k) {
    if (k > 20 && k < 25) continue;
    set<vector<PII>> S;
    for (int i = 0; i <= 25; ++i) {
      if (i > 20 && i < 25) continue;
      for (int j = 0; j <= 25; ++j) {
        if (j > 20 && j < 25) continue;
        for (int s = 1; s <= 3; ++s) {
          if (s == 3 && i == 25) continue;
          if (i == 0 && s > 1) continue;
          for (int t = 1; t <= 3; ++t) {
            if (t == 3 && j == 25) continue;
            if (j == 0 && t > 1) continue;
            int score = k * 2 + s * i + t * j;
            vector<PII> v = {PII(i, s), PII(j, t)};
            if (v[0] > v[1]) swap(v[0], v[1]);
            if (score < 100) S.insert(v);
          }
        }
      }
    }
    ret += S.size();
  }
  printf("%d\n", ret);
  return 0;
}
