#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 10;

char s[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%s", s);
  std::vector<int> J, O, I;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'J') J.push_back(i);
    if (s[i] == 'O') O.push_back(i);
    if (s[i] == 'I') I.push_back(i);
  }

  auto check = [&] (int x) {
    x = std::lower_bound(J.begin(), J.end(), x) - J.begin();
    if (x + m > J.size()) return -1;
    x = J[x + m - 1];
    x = std::lower_bound(O.begin(), O.end(), x) - O.begin();
    if (x + m > O.size()) return -1;
    x = O[x + m - 1];
    x = std::lower_bound(I.begin(), I.end(), x) - I.begin();
    if (x + m > I.size()) return -1;
    return I[x + m - 1];
  };
  
  int ret = -1;
  for (int i = 0; i < n; ++i) if (s[i] == 'J') {
    int u = check(i);
    if (u == -1) break;
    if (ret == -1 || ret > u - i + 1 - m * 3) ret = u - i + 1 - m * 3;
  }
  printf("%d\n", ret);
  return 0;
}
