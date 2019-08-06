#include <cstdio>
#include <vector>

const int N = 2e4 + 10;

char s[N];

int main() {
  int n;
  scanf("%d%s", &n, s);
  std::vector<int> a = {1};
  int mx = 1, ret = 0, cnt = 0;
  for (int i = 0; i < n; ++i) {
    int x = a.back();
    a.pop_back();
    cnt += s[i] == '1';
    if (s[i] == '1') {
      a.push_back(x + 1);
      a.push_back(x + 1);
      if (a.back() > mx) {
        mx = a.back();
        ret = cnt;
      }
    }
  }
  printf("%d\n", ret);
  return 0;
}
