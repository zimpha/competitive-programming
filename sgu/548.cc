#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;

void run() {
  int n; scanf("%d", &n);
  priority_queue<PII, vector<PII>, greater<PII>> Q;
  for (int i = 1, x; i < n; ++i) {
    char s[10]; scanf("%s%d", s, &x);
    if (s[0] == 'd') Q.push(PII(x, i + 1));
    else {
      if (i == n - 1) {
        if (Q.size() < x) puts("-1");
        else {
          int tot = 0;
          vector<int> pt;
          for (; !Q.empty(); Q.pop()) {
            tot += Q.top().first;
            pt.push_back(Q.top().second);
          }
          printf("%d\n%d\n", tot, (int)pt.size());
          sort(pt.begin(), pt.end());
          for (auto &v: pt) printf("%d ", v); puts("");
        }
      }
      else while (Q.size() >= x) Q.pop();
    }
  }
}

int main() {
  run();
  return 0;
}
