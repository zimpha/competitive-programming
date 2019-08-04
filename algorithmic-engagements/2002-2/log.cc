#include <cstdio>
#include <vector>

static char logo[5][60];

struct Pattern {
  char s[3][4];
  std::vector<int> x, y;
  int n;

  void init() {
    x.clear();
    y.clear();
    n = 0;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (s[j][i] == '#') {
          ++n;
          x.push_back(i);
          y.push_back(j);
        }
      }
    }
  }
  
  void out() {
    for (int i = 0; i < 3; ++i) printf("%s\n", s[i]);
  }

  int valid(int mask, int r, int c, int u, int v) {
    for (int i = 0; i < n; ++i) {
      int xx = x[i] - x[0] + u;
      int yy = y[i] - y[0] + v;
      //printf("%d %d\n", xx, yy);
      if (xx < 0 || xx >= r || yy < 0 || yy >= c) return -1;
      int p = xx * c + yy - u * c - v;
      if (logo[yy][xx] != '#' || (mask >> p & 1)) return -1;
      mask |= 1 << p;
    }
    return mask >> 1;
  }

  void rot() {
    char t[3][3];
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        t[2 - j][i] = s[i][j];
      }
    }
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        s[i][j] = t[i][j];
      }
    }
  }

  void flip() {
    for (int i = 0; i < 3; ++i) {
      std::swap(s[i][0], s[i][2]);
    }
  }
};

int main() {
  int n;
  scanf("%d", &n);
  std::vector<Pattern> pats;
  for (int i = 0; i< n; ++i) {
    Pattern pat;
    for (int j = 0; j < 3; ++j) {
      scanf("%s", pat.s[j]);
    }
    for (int _ = 0; _ < 2; ++_) {
      for (int j = 0; j < 4; ++j) {
        pat.rot();
        pat.init();
        pats.push_back(pat);
      }
      pat.flip();
    }
  }
  int m;
  scanf("%d", &m);
  for (int cas = 1; cas <= m; ++cas) {
    int r, c;
    scanf("%d%d", &r, &c);
    int sc = 1 << (3 * c);
    for (int i = 0; i < c; ++i) scanf("%s", logo[i]);
    std::vector<int> f(sc, -1);

    auto update = [](int &x, int y) {
      if (x == -1 || x > y) x = y;
    };

    //pats[2].out();
    //printf("%d\n", pats[2].valid(0, r, c, 0, 1));
    //return 0;

    f[0] = 0;
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        std::vector<int> g(sc, -1);
        for (int mask = 0; mask < sc; ++mask) {
          if (f[mask] == -1) continue;
          if (logo[j][i] == '.' || (logo[j][i] == '#' && (mask & 1))) update(g[mask >> 1], f[mask]);
          else {
            for (auto &pat: pats) {
              int new_mask = pat.valid(mask, r, c, i, j);
              if (new_mask != -1) {
                update(g[new_mask], f[mask] + 1);
              }
            }
          }
        }
        f.swap(g);
      }
    }
    if (f[0] == -1) puts("NIE");
    else printf("%d\n", f[0]);
  }
  return 0;
}
