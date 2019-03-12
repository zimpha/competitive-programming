#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

struct File {
  int id;
  std::vector<std::pair<int, int>> blocks;
  bool operator < (const File& rhs) const {
    return id < rhs.id;
  }
};

struct Move {
  char type;
  int x, y;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> p(n, -1), ip(n, -1);
  std::vector<File> files(m);
  for (int i = 0; i < m; ++i) {
    int l;
    scanf("%d%d", &files[i].id, &l);
    for (int j = 0; j < l; ++j) {
      int x, y;
      scanf("%d%d", &x, &y);
      files[i].blocks.emplace_back(x - 1, y);
    }
  }
  std::sort(files.begin(), files.end());
  int s = 0;
  for (auto &&file: files) {
    for (auto &&e: file.blocks) {
      for (int i = 0; i < e.second; ++i) {
        ip[s] = e.first + i;
        p[e.first + i] = s++;
      }
    }
  }
  std::vector<Move> moves;
  std::vector<bool> mark(n);
  for (int i = 0; i < n; ++i) if (!mark[i] && ip[i] == -1) {
    if (p[i] == -1) continue;
    std::vector<int> chain;
    int j = i;
    while (j != -1) {
      chain.push_back(j);
      mark[j] = true;
      j = p[j];
    }
    std::reverse(chain.begin(), chain.end());
    for (size_t i = 1; i < chain.size(); ++i) {
      moves.push_back({'K', chain[i], chain[i - 1]});
    }
  }
  for (int i = 0; i < n; ++i) if (!mark[i]) {
    if (p[i] == -1) continue;
    if (p[i] == i) continue;
    std::vector<int> chain;
    int j = i;
    while (!mark[j]) {
      chain.push_back(j);
      mark[j] = true;
      j = p[j];
      assert(j != -1);
    }
    if (s == n) {
      for (size_t i = 0; i + 1 < chain.size(); ++i) {
        moves.push_back({'Z', chain[i], chain.back()});
      }
    } else if (chain.size() == 2) {
      moves.push_back({'Z', chain[0], chain[1]});
    } else {
      moves.push_back({'K', chain.back(), s});
      for (int i = chain.size() - 1; i >= 1; --i) {
        moves.push_back({'K', chain[i - 1], chain[i]});
      }
      moves.push_back({'K', s, chain[0]});
    }
  }
  if (moves.size() == 0) {
    puts("NIC");
  }
  fprintf(stderr, "%d\n", (int)moves.size());
  for (auto &&move: moves) {
    printf("%c %d %d 1\n", move.type, move.x + 1, move.y + 1);
  }
  return 0;
}
