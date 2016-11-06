#include <bits/stdc++.h>

const long mod = 10000000000ll;
int u[14], v[14];

long encode(int u[14]) {
  long r = 0;
  for (int i = 13; i >= 0; --i) r = (r << 4) + u[i];
  return r;
}

void decode(long r) {
  for (int i = 0; i < 14; ++i) {
    u[i] = r & 15;
    r >>= 4;
  }
}

inline void merge(int u[14], int a, int b) {
  int past = u[b], now = u[a];
  for (int i = 0; i < 14; ++i) {
    if (u[i] == past) u[i] = now;
  }
}

inline void minify(int u[14]) {
  static int mark[20];
  memset(mark, -1, sizeof(mark));
  for (int i = 0, sz = 0; i < 14; ++i) {
    if (mark[u[i]] == -1) mark[u[i]] = sz++;
    u[i] = mark[u[i]];
  }
}

long run(int n, int m) {
  std::map<long, long> f, g;
  for (int i = 0; i < 14; ++i) u[i] = i;
  f[encode(u)] = 1;
  size_t mx = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      g.clear();
      mx = std::max(mx, f.size());
      for (auto it = f.begin(); it != f.end(); ++it) {
        decode(it->first); it->second %= mod;
        if (i == 0) {
          if (j == 0) {
            u[1] = 0;
            minify(u); g[encode(u)] += it->second;
          } else if (j == m) {
            g[encode(u)] += it->second;
          } else {
            memcpy(v, u, sizeof(u));
            merge(v, 2 * j - 1, 2 * j + 1);
            v[2 * j] = v[2 * j - 1] = 14;
            minify(v); g[encode(v)] += it->second;
            u[2 * j + 1] = u[2 * j] = 14;
            minify(u); g[encode(u)] += it->second;
          }
        } else if (i == n) {
          if (j == 0) {
            g[encode(u)] += it->second;
          } else if (j == m) {
            u[m] = u[m - 1];
            minify(u); g[encode(u)] += it->second;
          } else {
            if (u[j - 1] != u[j]) {
              memcpy(v, u, sizeof(u));
              merge(v, j - 1, j);
              for (int k = j; k < 13; ++k) v[k] = v[k + 1];
              v[13] = 14;
              minify(v); g[encode(v)] += it->second;
            }
            if (u[j] != u[j + 1]) {
              merge(u, j, j + 1);
              for (int k = j; k < 13; ++k) u[k] = u[k + 1];
              u[13] = 14; u[j] = u[j - 1];
              minify(u); g[encode(u)] += it->second;
            }
          }
        } else {
          if (j == 0) {
            memcpy(v, u, sizeof(u));
            for (int i = 13; i >= 3; --i) v[i] = v[i - 2];
            v[2] = v[1] = 14;
            minify(v); g[encode(v)] += it->second;
            for (int i = 13; i >= 3; --i) u[i] = u[i - 2];
            u[2] = u[0]; u[0] = u[1] = 14;
            minify(u); g[encode(u)] += it->second;
          } else if (j == m) {
            if (u[m * 2 - 1] != u[m * 2]) {
              memcpy(v, u, sizeof(u));
              merge(v, m * 2 - 1, m * 2);
              v[m * 2 - 1] = v[m * 2 + 1];
              for (int k = m * 2; k < 14; ++k) v[k] = k;
              minify(v); g[encode(v)] += it->second;
            }
            if (u[m * 2] != u[m * 2 + 1]) {
              merge(u, m * 2, m * 2 + 1);
              for (int k = m * 2; k < 14; ++k) u[k] = k;
              minify(u); g[encode(u)] += it->second;
            }
          } else {
            int a = 2 * j - 1, b = 2 * j, c = 2 * j + 1, d = 2 * j + 2;
            if (u[a] != u[b]) {
              merge(u, a, b);
              memcpy(v, u, sizeof(u)); // 5
              v[a] = v[b] = 13;
              minify(v); g[encode(v)] += it->second;
              memcpy(v, u, sizeof(u)); // 7
              v[a] = v[c], v[b] = v[c] = 14;
              minify(v); g[encode(v)] += it->second;
              memcpy(v, u, sizeof(u)); // 8
              v[a] = v[c], v[b] = v[d], v[c] = v[d] = 14;
              minify(v); g[encode(v)] += it->second;
              if (u[c] != u[d]) {
                merge(u, c, d);
                memcpy(v, u, sizeof(u)); // 0
                v[a] = v[b] = 13, v[c] = v[d] = 14;
                minify(v); g[encode(v)] += it->second;
                memcpy(v, u, sizeof(u)); // 2
                v[a] = v[d] = 13, v[c] = v[b] = 14;
                minify(v); g[encode(v)] += it->second;
              }
            }
            decode(it->first);
            if (u[c] != u[d]) {
              merge(u, c, d);
              memcpy(v, u, sizeof(u)); // 1
              v[c] = v[d] = 14;
              minify(v); g[encode(v)] += it->second;
              memcpy(v, u, sizeof(u)); // 3
              v[d] = v[b], v[b] = v[c] = 14;
              minify(v); g[encode(v)] += it->second;
              memcpy(v, u, sizeof(u)); // 4
              v[d] = v[b], v[c] = v[a], v[a] = v[b] = 14;
              minify(v); g[encode(v)] += it->second;
            }
            g[it->first] += it->second; // 6
            decode(it->first);
            if (u[b] != u[c]) {
              merge(u, b, c);
              memcpy(v, u, sizeof(u)); // 9
              v[b] = v[c] = 14;
              minify(v); g[encode(v)] += it->second;
              memcpy(v, u, sizeof(u)); // 10
              v[c] = v[a], v[a] = v[b] = 14;
              minify(v); g[encode(v)] += it->second;
              memcpy(v, u, sizeof(u)); // 11
              v[b] = v[d], v[c] = v[d] = 14;
              minify(v); g[encode(v)] += it->second;
              if (u[a] != u[d]) {
                merge(u, a, d);
                memcpy(v, u, sizeof(u)); // 12
                v[a] = v[b] = 13, v[c] = v[d] = 14;
                minify(v); g[encode(v)] += it->second;
                memcpy(v, u, sizeof(u)); // 13
                v[a] = v[d] = 13, v[b] = v[c] = 14;
                minify(v); g[encode(v)] += it->second;
              }
            }
          }
        }
      }
      f.swap(g);
    }
  }
  memset(u, 0, sizeof(u));
  for (int i = m + 1; i < 14; ++i) u[i] = i - m;
  std::cout << "max state size: " << mx << std::endl;
  return f[encode(u)] % mod;
}

int main() {
  std::cout << run(2, 2) << std::endl;
  std::cout << run(3, 3) << std::endl;
  std::cout << run(10, 6) << std::endl;
  return 0;
}
