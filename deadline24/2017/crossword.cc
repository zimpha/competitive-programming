#include <cassert>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

std::vector<std::string> dict;
char P[100][100], buffer[10000];
char G[100][100];
map<char, int> score;
int n, m;
int total;

struct node {
  int score;
  int x, y;
  string s;
  char dir;

  node() {}
  node(int _sc, int _x, int _y, const std::string& _s, char _d):
    score(_sc), x(_x), y(_y), s(_s), dir(_d) {}
};

inline int eval_H(int x, int y, const std::string &s) {
  if (y + (int)s.size() > m) return 0;
  int ret = 0, cx = 0, cX = 0;
  for (auto &&c: s) ret += score[c];
  for (int i = 0; i < (int)s.size(); ++i) {
    cx += P[x][y + i] == 'x';
    cX += P[x][y + i] == 'X';
    if (P[x][y + i] == '2') ret += score[s[i]];
    if (P[x][y + i] == '3') ret += score[s[i]] * 2;
  }
  for (int i = 0; i < cx; ++i) ret *= 2;
  for (int i = 0; i < cX; ++i) ret *= 3;
  return ret;
}

inline int eval_V(int x, int y, const std::string &s) {
  if (x + (int)s.size() > n) return 0;
  int ret = 0, cx = 0, cX = 0;
  for (auto &&c: s) ret += score[c];
  for (int i = 0; i < (int)s.size(); ++i) {
    cx += P[x + i][y] == 'x';
    cX += P[x + i][y] == 'X';
    if (P[x + i][y] == '2') ret += score[s[i]];
    if (P[x + i][y] == '3') ret += score[s[i]] * 2;
  }
  for (int i = 0; i < cx; ++i) ret *= 2;
  for (int i = 0; i < cX; ++i) ret *= 3;
  return ret;
}

void update_H(const std::string &s, node &ret) {
  int now = 0;
  for (auto &&c: s) now += score[c];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j + (int)s.size() <= m; ++j) {
      int tmp = eval_H(i, j, s);
      if (tmp > ret.score) {
        ret = node(tmp, i, j, s, 'H');
      }
    }
  }
}

void clear(const node &u) {
  if (u.dir == 'H') {
    for (int i = 0; i < (int)u.s.size(); ++i) {
      P[u.x][u.y + i] = '.';
      G[u.x][u.y + i] = u.s[i];
    }
  } else {
    for (int i = 0; i < (int)u.s.size(); ++i) {
      P[u.x + i][u.y] = '.';
      G[u.x + i][u.y] = u.s[i];
    }
  }
}

void update_V(const std::string &s, node &ret) {
  int now = 0;
  for (auto &&c: s) now += score[c];
  for (int i = 0; i + (int)s.size() <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      int tmp = eval_V(i, j, s);
      if (tmp > ret.score) {
        ret = node(tmp, i, j, s, 'V');
      }
    }
  }
}

bool ok_H(int x, int y, const std::string &s) {
  int common = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    if (G[x][y + i] != ' ' && G[x][y + i] != s[i]) return false;
    common += G[x][y + i] != ' ';
  }
  return common == 1;
}

bool ok_V(int x, int y, const std::string &s) {
  int common = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    if (G[x + i][y] != ' ' && G[x + i][y] != s[i]) return false;
    common += G[x + i][y] != ' ';
  }
  return common == 1;
}

void update_H(const std::string &s, const node &u, node &v) {
  int l = s.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j + l <= m; ++j) {
      if (!ok_H(i, j, s)) continue;
      int tmp = eval_H(i, j, s);
      if (tmp > v.score) {
        v = node(tmp, i, j, s, 'H');
      }
    }
  }
}

void update_V(const std::string &s, const node &u, node &v) {
  int l = s.size();
  for (int i = 0; i + l <= n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!ok_V(i, j, s)) continue;
      int tmp = eval_V(i, j, s);
      if (tmp > v.score) {
        v = node(tmp, i, j, s, 'V');
      }
    }
  }
}

void solve() {
  int d;
  scanf("%d", &d);
  std::string filename = "/home/zimpha/Downloads/sets/dict" + to_string(d) + ".in";
  ifstream fin(filename, ifstream::in);
  std::string s;
  dict.clear();
  while (fin >> s) {
    dict.push_back(s);
  }
  fin.close();
  scanf("%d%d", &m, &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", P[i]);
    for (int j = 0; j < m; ++j) {
      G[i][j] = ' ';
    }
  }
  int L;
  scanf("%d", &L);
  score.clear();
  for (int i = 0; i < L; ++i) {
    char c[10];
    int v;
    scanf("%s%d", c, &v);
    score[c[0]] = v;
  }
  int B, Q;
  scanf("%d%d", &B, &Q);
  scanf("%s", buffer);

  node first;
  first.score = 0;

  static int cnt[256];
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < B; ++i) {
    cnt[(int)buffer[i]]++;
  }
  for (auto &&s: dict) {
    for (auto &&c: s) {
      cnt[(int)c]--;
    }
    bool flag = true;
    for (int i = 0; i < 256; ++i) {
      if (cnt[i] < 0) flag = false;
    }
    if (flag) {
      update_H(s, first);
      update_V(s, first);
    }
    for (auto &&c: s) {
      cnt[(int)c]++;
    }
  }
  std::vector<node> result = {first};
  int cur = B;
  for (int it = 0; it < 1; ++it) {
    first = result.back();
    for (auto &&c: first.s) {
      cnt[(int)c]--;
      if (cur < Q) {
        cnt[(int)buffer[cur++]]++;
      }
    }
    clear(first);
    node second;
    second.score = 0;
    for (auto &&s: dict) {
      for (auto &&c: s) {
        cnt[(int)c]--;
      }
      bool flag = true;
      for (int i = 0; i < 256; ++i) {
        if (cnt[i] < 0) flag = false;
      }
      if (flag) {
        update_V(s, first, second);
        update_H(s, first, second);
      }
      for (auto &&c: s) {
        cnt[(int)c]++;
      }
    }
    if (second.score == 0) break;
    result.push_back(second);
  }
  int sum = 0;
  for (auto &&e: result) sum += e.score;
  printf("%d %d\n", (int)result.size(), sum);
  total += sum;
  for (auto &&e: result) {
    printf("%d %d %s %c\n", e.y + 1, e.x + 1, e.s.c_str(), e.dir);
  }
  /*
  clear(result.back());
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      putchar(G[i][j]);
    }
    puts("");
  }*/
}

int main() {
  int T;
  total = 0;
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  std::cerr << total << std::endl;
  return 0;
}
