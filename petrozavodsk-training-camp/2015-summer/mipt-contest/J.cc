#include <cstdio>
#include <cstdlib>
#include <vector>

char query(int x, int y) {
  printf("? %d %d\n", x, y);
  fflush(stdout);
  static char op[10];
  scanf("%s", op);
  return op[0];
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> path = {1, 2, 3};
  std::vector<char> type;
  type.push_back(query(1, 2));
  type.push_back(query(2, 3));
  type.push_back(query(3, 1));
  for (int i = 4; i <= n; ++i) {
    int x = 0, y = 1, z = 2;
    for (size_t j = 0; j < path.size(); ++j) {
      if (type[j] != type[(j + 1) % path.size()]) {
        x = j;
        y = (j + 1) % path.size();
        z = (j + 2) % path.size();
        break;
      }
    }
    char t = query(i, path[y]);
    if (t == type[x]) {
      path.insert(path.begin() + z, i);
      type[y] = type[x];
      type.insert(type.begin() + z, query(i, path[z + 1]));
    } else {
      path.insert(path.begin() + y, i);
      type.insert(type.begin() + y, t);
      type[x] = query(i, path[(y - 1 + path.size()) % path.size()]);
    }
    /*for (auto &x: path) printf("%d ", x);
    puts("");
    for (auto &c: type) printf("%c", c);
    puts("");*/
  }
  int x = 0;
  for (size_t j = 0; j < path.size(); ++j) {
    if (type[j] != type[(j + 1) % path.size()]) {
      x = j;
      break;
    }
  }
  putchar('!');
  for (int i = 1; i <= n; ++i) {
    printf(" %d", path[(x + i) % n]);
  }
  puts("");
  return 0;
}
