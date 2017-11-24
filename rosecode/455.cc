#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

const int n = 65, N = 2000 + 10;

std::string s[n];
int target;
char A[N], B[N];
bool valid[256][256];
bool mark[n];
std::vector<int> seq;

bool match(const char *s, const char *t, int l) {
  for (int i = 0; i < l; ++i) {
    if (!valid[s[i]][t[i]]) return false;
  }
  return true;
}

bool dfs(int x, int y) {
  if (x == target && y == target) {
    for (size_t i = 0; i < seq.size(); ++i) {
      if (i) putchar(',');
      printf("%s", s[seq[i]].c_str());
    }
    return true;
  }
  if (x == y) {
    for (int i = 0; i < n; ++i) if (!mark[i] && s[i].size() + x <= target) {
      seq.push_back(i);
      mark[i] = 1;
      memcpy(A + x, s[i].c_str(), sizeof(char) * s[i].size());
      if (dfs(x + s[i].size(), y)) return true;
      mark[i] = 0;
      seq.pop_back();
    }
  } else if (x < y) {
    for (int i = 0; i < n; ++i) if (!mark[i] && s[i].size() + x <= target) {
      seq.push_back(i);
      mark[i] = 1;
      bool valid = false;
      if (x + s[i].size() <= y) valid = match(s[i].c_str(), B + x, s[i].size());
      else valid = match(B + x, s[i].c_str(), y - x);
      if (valid) {
        memcpy(A + x, s[i].c_str(), sizeof(char) * s[i].size());
        if (dfs(x + s[i].size(), y)) return true;
      }
      mark[i] = 0;
      seq.pop_back();
    }
  } else {
    for (int i = 0; i < n; ++i) if (!mark[i] && s[i].size() + y <= target) {
      mark[i] = 1;
      bool valid = false;
      if (y + s[i].size() <= x) valid = match(s[i].c_str(), A + y, s[i].size());
      else valid = match(A + y, s[i].c_str(), x - y);
      if (valid) {
        memcpy(B + y, s[i].c_str(), sizeof(char) * s[i].size());
        if (dfs(x, y + s[i].size())) return true;
      }
      mark[i] = 0;
    }
  }
  return false;
}

int main() {
  memset(valid, 0, sizeof(valid));
  valid['A']['T'] = 1;
  valid['T']['A'] = 1;
  valid['C']['G'] = 1;
  valid['G']['C'] = 1;
  target = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
    target += s[i].size();
  }
  target /= 2;
  std::sort(s, s + n);
  dfs(0, 0);
  return 0;
}
