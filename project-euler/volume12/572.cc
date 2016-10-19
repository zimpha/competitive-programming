#include <bits/stdc++.h>

long solve(long u, long v, long w, int n) {
  int ret = 0;
  for (int a = -n; a <= n; ++a) {
    for (int e = -n; e <= n; ++e) {
      int i = u - a - e;
      if (i < -n || i > n) continue;
      int bd = v - (i - i * i - a * e - a * i - e * i);
      for (int b = -n; b <= n; ++b) {
        if (b == 0 && bd != 0) continue;
        if (b != 0 && bd % b != 0) continue;
        int low = -n, upp = n;
        if (b != 0) low = upp = bd / b;
        low = std::max(-n, low);
        upp = std::min(n, upp);
        for (int d = low; d <= upp; ++d) {
          int cg = a - a * a - bd;
          int ch = b - a * b - b * e;
          int fg = d - a * d - e * d;
          int fh = e - b * d - e * e;
          if (a * e * i - b * d * i - a * fh + b * fg + d * ch - e * cg != w) continue;
          std::vector<int> fv, gv, hv;
          for (int c = -n; c <= n; ++c) {
            fv.clear(); gv.clear(); hv.clear();
            if (1 - a - i == 0 || c == 0) {
              if (b == 0) {
                for (int f = -n; f <= n; ++f) {
                  if ((1 - e - i) * f == c * d) fv.push_back(f);
                }
              } else fv.push_back(0);
            } else {
              if (b != 0 && (1 - a - i) * c % b == 0) {
                int f = (1 - a - i) * c / b;
                if (f >= -n && f <= n) fv.push_back(f);
              }
            }
            if (c == 0) {
              if (cg == 0) {
                for (int g = -n; g <= n; ++g) gv.push_back(g);
              }
              if (ch == 0) {
                for (int h = -n; h <= n; ++h) hv.push_back(h);
              }
            } else {
              if (cg == 0) gv.push_back(0);
              else {
                if (cg % c == 0) {
                  int g = cg / c;
                  if (g >= -n && g <= n) gv.push_back(g);
                }
              }
              if (ch == 0) hv.push_back(0);
              else {
                if (ch % c == 0) {
                  int h = ch / c;
                  if (h >= -n && h <= n) hv.push_back(h);
                }
              }
            }
            for (auto &&f: fv) for (auto &&g: gv) for (auto &&h: hv) {
              if (f * g == fg && f * h == fh && (1 - a - i) * g == h * d && (1 - e - i) * h == b * g) ++ret;
            }
            /*
            for (int g = -n; g <= n; ++g) {
              for (int f = -n; f <= n; ++f) {
                for (int h = -n; h <= n; ++h) {
                  if (cg == c * g && ch == c * h && fg == f * g && fh == f * h) {
                    if ((1 - a - i) * c != b * f) continue;
                    if ((1 - e - i) * f != c * d) continue;
                    if ((1 - a - i) * g != h * d) continue;
                    if ((1 - e - i) * h != b * g) continue;
                    ++ret;
                  }
                }
              }
            }*/
          }
        }
      }
    }
  }
  return ret;
}

long run(int n) {
  return solve(0, 0, 0, n) + solve(1, 0, 0, n) + solve(2, -1, 0, n) + solve(3, -3, 1, n);
}

int main() {
  std::cout << run(1) << std::endl;
  std::cout << run(2) << std::endl;
  std::cout << run(200) << std::endl;
  return 0;
}
