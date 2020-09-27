#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

// Two Efficient Algorithms for Linear Suffix Array Construction
#define pushS(x) sa[--cur[(int)s[x]]] = x
#define pushL(x) sa[cur[(int)s[x]]++] = x
class SuffixArray {
public:
  std::vector<int> sa;
  std::vector<int> rank;

  template <class T> void build(const T *s, int n);
  template <class T> void build(const T *s, int n, int m);

  int size() const {
    return sa.size() - 1;
  }

private:
  using SLTypes = std::vector<bool>;
  int *buffer, *freq, *cur;
  int len;

  void buildRankTable();
  template <class T> void computeLCPArray(const T *s);
  template <class T> void countFrequency(const T *s, int n, int m);
  template <class T> void induce(const T *s, int *sa, int m, const SLTypes &t);
  template <class T> void sa_is(const T *s, int *sa, int n, int m);
};

template <class T>
void SuffixArray::build(const T *s, int n) {
  this->len = n;
  int m = *std::max_element(s, s + n) + 1;
  build(s, n, m);
  buildRankTable();
}

template <class T>
void SuffixArray::build(const T *s, int n, int m) {
  sa.resize(n + 1);
  if (n == 0) sa[0] = 0;
  else {
    // memory usage: sa + buffer + types
    // = 4 * (n + max(m * 2, n)) + 2 * n / 8 + O(1) bytes
    std::vector<int> buffer((std::max(m, (n + 1) / 2) + 1) * 2);
    this->buffer = &buffer[0];
    sa_is<T>(s, &sa[0], n + 1, m);
  }
}

void SuffixArray::buildRankTable() {
  int n = size() + 1;
  rank.resize(n);
  for (int i = 0; i < n; ++i) rank[sa[i]] = i;
}

template <class T>
void SuffixArray::countFrequency(const T *s, int n, int m) {
  memset(freq, 0, sizeof(int) * m);
  for (int i = 0; i < n; ++i) ++freq[(int)s[i]];
  for (int i = 1; i < m; ++i) freq[i] += freq[i - 1];
  memcpy(cur, freq, sizeof(int) * m);
}

template <class T>
void SuffixArray::induce(const T *s, int *sa, int m, const SLTypes &t) {
  const int n = t.size();
  memcpy(cur + 1, freq, sizeof(int) * (m - 1));
  for (int i = 0; i < n; ++i) {
    int p = sa[i] - 1;
    if (p >= 0 && t[p]) pushL(p);
  }
  memcpy(cur, freq, sizeof(int) * m);
  for (int i = n - 1; i > 0; --i) {
    int p = sa[i] - 1;
    if (p >= 0 && !t[p]) pushS(p);
  }
}

template <class T>
void SuffixArray::sa_is(const T *s, int *sa, int n, int m) {
  SLTypes t(n); memset(sa, 0, sizeof(int) * n);
  for (int i = n - 2; ~i; --i) {
    t[i] = (s[i] == s[i + 1]) ? t[i + 1] : s[i] > s[i + 1];
  }
  freq = buffer, cur = buffer + m;
  countFrequency(s, n, m);
  for (int i = 1; i < n; ++i) if (t[i - 1] > t[i]) pushS(i);
  induce(s, sa, m, t);
  int n1 = 0, order = 0;
  for (int i = 0, p; i < n; ++i) {
    if ((p = sa[i]) && t[p - 1] > t[p]) sa[n1++] = p;
  }
  int *s1 = sa + n1;
  memset(s1, -1, sizeof(int) * (n - n1));
  s1[(sa[0] - 1) / 2] = order++;
  for (int i = 1; i < n1; ++i) {
    bool diff = true;
    for (int x = sa[i - 1], y = sa[i]; ; ++x, ++y) {
      if (s[x] != s[y] || t[x] != t[y]) break;
      else if (t[x] > t[x + 1] && t[y] > t[y + 1]) {
        diff = (s[x + 1] != s[y + 1]); break;
      }
    }
    s1[(sa[i] - 1) / 2] = (order += diff) - 1;
  }
  for (int i = 0, x = 0; i < n - n1; ++i) {
    if (~s1[i]) s1[x++] = s1[i];
  }
  if (order != n1) {
    sa_is<int>(s1, sa, n1, order);
    for (int i = 0; i < n1; ++i) s1[sa[i]] = i;
  }
  for (int i = 1, j = 0; i < n; ++i) {
    if (t[i - 1] > t[i]) sa[s1[j++]] = -i;
  }
  memset(s1, 0, sizeof(int) * (n - n1));
  freq = buffer, cur = buffer + m;
  countFrequency(s, n, m);
  for (int i = n1 - 1; ~i; --i) pushS(-sa[i]);
  induce(s, sa, m, t);
}

std::vector<std::string> duval(char s[]){
  std::vector<std::string> ret;
  int n = strlen(s) + 1; // zero used here
  int start = 0, mid = 1, cur = 0;
  for (int i = 0; i < n; ++i){
    if (s[i] == s[cur]){
      if (++cur == mid) cur = start;
    } else if (s[i] > s[cur]){
      mid = i + 1;
      cur = start;
    } else if (s[i] < s[cur]){
      int temp = mid - start;
      while (start + temp <= i){
        ret.emplace_back(s + start, s + start + temp);
        start += temp;
      }
      i = cur = start;
      mid = start + 1;
    }
  }
  return ret;
}

std::vector<std::pair<std::string, int>> get_opt(const std::vector<std::string> &lyndon) {
  std::vector<std::pair<std::string, int>> opt;
  std::string last = "";
  int cnt = 0;
  for (auto &x: lyndon) {
    if (x != last) {
      if (last != "") opt.emplace_back(last, cnt);
      last = x;
      cnt = 1;
    } else {
      cnt += 1;
    }
  }
  opt.emplace_back(last, cnt);
  return opt;
}

const int N = 1e6 + 10;

char s[N];

int main() {
  freopen("prisoner.in", "r", stdin);
  freopen("prisoner.out", "w", stdout);
  int n, m;
  scanf("%d%d%s", &m, &n, s);
  if (m == 1) {
    puts(s);
    return 0;
  }
  auto lyndon = duval(s);
  auto opt = get_opt(lyndon);
  if (m >= (int)opt.size() && m <= (int)lyndon.size()) {
    std::reverse(lyndon.begin(), lyndon.end());
    for (auto &x: lyndon) printf("%s", x.c_str());
  } else if (m < (int)opt.size()) {
    for (; m > 2; --m) {
      for (int i = 0; i < opt.back().second; ++i) {
        printf("%s", opt.back().first.c_str());
      }
      opt.pop_back();
    }
    int nn = 0;
    for (auto &e: opt) {
      for (int i = 0; i < e.second; ++i) {
        for (auto &c: e.first) s[nn++] = c;
      }
    }
    for (int i = 0; i < nn; ++i) s[nn + i] = s[i];
    s[nn * 2] = 0;
    lyndon = duval(s);
    opt = get_opt(lyndon);
    for (auto &e: opt) if (e.first.size() * e.second == nn) {
      for (int i = 0; i < e.second; ++i) {
        printf("%s", e.first.c_str());
      }
      break;
    }
  } else {
    SuffixArray sa;
    sa.build(s, n);
    std::set<std::pair<int, int>> suf;
    std::vector<std::string> ret;
    for (int last = n, now = n; m > 1; --m) {
      while (now >= m) {
        --now;
        suf.emplace(sa.rank[now], now);
      }
      int st = suf.begin()->second;
      ret.emplace_back(s + st, s + last);
      for (int i = st; i < last; ++i) {
        suf.erase(std::make_pair(sa.rank[i], i));
      }
      last = st;
      if (m == 2) ret.emplace_back(s, s + last);
    }
    for (auto &x: ret) printf("%s", x.c_str());
  }
  puts("");
  return 0;
}
