#include <bits/stdc++.h>

using LL = long long;

std::vector<int> get_begin(int a, int b) {
  std::vector<int> s;
  s.push_back(a);
  s.push_back(b);
  for (; s.back() % 2;) {
    std::map<int, int> cnt;
    for (size_t i = 0; i < s.size(); ++i) {
      for (size_t j = 0; j < i; ++j) {
        int v = s[i] + s[j];
        if (v > s.back()) cnt[v]++;
      }
    }
    for (auto &e: cnt) if (e.second == 1) {
      s.push_back(e.first);
      break;
    }
  }
  s.push_back(s.back() + 1);
  return s;
}

LL U(int a, int b, LL n) {
  std::vector<int> st = get_begin(a, b);
  std::vector<int> diff;
  std::set<int> candidate;
  auto add = [&](int v) {
    if (candidate.count(v)) candidate.erase(v);
    else candidate.insert(v);
  };
  for (size_t i = 0; i < st.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (st[i] % 2 == st[j] % 2) continue;
      int v = st[i] + st[j];
      if (v > st.back()) add(v);
    }
  }
  int prev = st.back(), even = -1, T = -1;
  for (size_t i = 1; i < st.size(); ++i) {
    if (st[i] % 2 == 0) even = st[i];
  }
  assert(even != -1);
  std::vector<int> fail;
  for (int i = 0; T == -1; ++i) {
    int v = *candidate.begin();
    candidate.erase(v);
    diff.push_back(v - prev);
    add(2 + v);
    add(even + v);
    prev = v;
    if (i == 0) fail.push_back(-1);
    else {
      int j = fail[i - 1];
      while (j >= 0 && diff[j + 1] != diff[i]) j = fail[j];
      if (diff[j + 1] == diff[i]) ++j;
      fail.push_back(j);
      if (j != -1 && i + 1 == 2 * (j + 1) && j >= 10) {
        T = j + 1;
        break;
      }
    }
  }
  if (n <= st.size()) return st[n - 1];
  n -= st.size();
  int sum = 0;
  for (int i = 0; i < T; ++i) sum += diff[i];
  LL ret = st.back();
  ret += n / T * sum;
  for (int i = 0; i < n % T; ++i) ret += diff[i];
  return ret;
}

LL run(LL k) {
  LL ret = 0;
  for (int n = 2; n <= 10; ++n) {
    ret += U(2, 2 * n + 1, k);
  }
  return ret;
}

int main() {
  std::cout << run(100000000000ll) << std::endl;
  return 0;
}
