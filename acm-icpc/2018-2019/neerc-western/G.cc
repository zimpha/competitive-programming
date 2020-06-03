#include <cstdio>
#include <set>
#include <vector>

int main() {
  int q;
  scanf("%d", &q);
  std::set<int> valid;
  for (int i = 0; i < q; ++i) valid.insert(i + 1);
  std::vector<int> pid;
  for (int i = 0; i < q; ++i) {
    char op[10];
    scanf("%s", op);
    if (op[0] == 'C') {
      pid.push_back(*valid.begin());
      valid.erase(valid.begin());
      printf("%d\n", pid.back());
    } else {
      int x;
      scanf("%d", &x);
      valid.insert(pid[x - 1]);
    }
  }
  return 0;
}
