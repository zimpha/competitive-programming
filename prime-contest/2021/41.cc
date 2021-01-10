#include <vector>
#include <cassert>
#include <cstdio>
#include <string>
#include <queue>
#include <algorithm>

using i64 = long long;

struct AhoCorasick {
  static const int C = 3;
  struct node {
    int go[C], link;
    bool mark;
    void init() {
      go[0] = go[1] = go[2] = link = -1;
      mark = false;
    }
  };

  AhoCorasick() {
    init();
  }

  std::vector<node> trans;
  int root;

  int size() { return trans.size(); }

  void alloc() {
    trans.emplace_back();
    trans.back().init();
  }

  void init() {
    root = trans.size();
    alloc();
  }
  void ins(const char *s) {
    int p = root;
    for (int i = 0; s[i]; ++i) {
      int o = s[i] - 'a';
      assert(0 <= o && o < C);
      if (trans[p].go[o] == -1) {
        trans[p].go[o] = size();
        alloc();
      }
      p = trans[p].go[o];
    }
    trans[p].mark = true;
  }
  void build() {
    std::queue<int> queue;
    for (int o = 0; o < C; ++o) {
      int &u = trans[root].go[o];
      if (u != -1) {
        trans[u].link = root;
        queue.push(u);
      } else u = root;
    }
    for (; !queue.empty(); queue.pop()) {
      int u = queue.front();
      trans[u].mark |= trans[trans[u].link].mark;
      for (int o = 0; o < C; ++o) {
        int &v = trans[u].go[o];
        if (v != -1) {
          trans[v].link = trans[trans[u].link].go[o];
          queue.push(v);
        } else v = trans[trans[u].link].go[o];
      }
    }
  }
  int go(const char *s) {
    int p = root;
    for (int i = 0; s[i]; ++i) {
      int o = s[i] - 'a';
      assert(0 <= o && o < C);
      p = trans[p].go[o];
    }
    return p;
  }
};

bool check_valid(const std::string &s, int state, const AhoCorasick &forbid) {
  for (auto c: s) {
    assert('a' <= c && c <= 'c');
    state = forbid.trans[state].go[c - 'a'];
    if (forbid.trans[state].mark) return false;
  }
  return true;
}

void generate_from_forbid(std::string &s, int state, int len, const AhoCorasick &forbid, std::vector<std::string> &ret) {
  if (forbid.trans[state].mark) return;
  if (!s.empty() && check_valid(s, state, forbid)) {
    ret.push_back(s);
  }
  if (static_cast<int>(s.size()) == len) return;
  for (int c = 0; c < 3; ++c) {
    s.push_back(c + 'a');
    generate_from_forbid(s, forbid.trans[state].go[c], len, forbid, ret);
    s.pop_back();
  }
}

std::vector<std::string> generate_minimal_squares(int max_len) {
  if (max_len == 0) return {};
  auto ret = generate_minimal_squares(max_len / 2);
  AhoCorasick forbid;
  for (auto &s: ret) {
    auto t = s + s;
    forbid.ins(t.c_str());
  }
  forbid.build();

  std::string s;
  generate_from_forbid(s, forbid.root, max_len, forbid, ret);
  return ret;
}

i64 table[] = {
  1ll, 3ll, 6ll, 12ll, 18ll, 30ll, 42ll, 60ll, 78ll, 108ll, 144ll, 204ll, 264ll, 342ll, 456ll, 618ll, 798ll, 1044ll, 1392ll, 1830ll, 2388ll, 3180ll, 4146ll, 5418ll, 7032ll, 9198ll, 11892ll, 15486ll, 20220ll, 26424ll, 34422ll, 44862ll, 58446ll, 76122ll, 99276ll, 129516ll, 168546ll, 219516ll, 285750ll, 372204ll, 484446ll, 630666ll, 821154ll, 1069512ll, 1392270ll, 1812876ll, 2359710ll, 3072486ll, 4000002ll, 5207706ll, 6778926ll, 8824956ll, 11488392ll, 14956584ll, 19470384ll, 25346550ll, 32996442ll, 42957300ll, 55921896ll, 72798942ll, 94766136ll, 123368406ll, 160596120ll, 209059806ll, 272143380ll, 354271314ll, 461181036ll, 600356406ll, 781520994ll, 1017362166ll, 1324371090ll, 1724034504ll, 2244278358ll, 2921521164ll, 3803130042ll, 4950798954ll, 6444761514ll, 8389549680ll, 10921197582ll, 14216853012ll, 18506985300ll, 24091726728ll, 31361678988ll, 40825520274ll, 53145145482ll, 69182396616ll, 90058945560ll, 117235364616ll, 152612592438ll, 198665414208ll, 258615015792ll, 336655224582ll, 438245025942ll, 570491023872ll, 742643501460ll, 966745068408ll, 1258471821174ll, 1638231187596ll, 2132586986466ll, 2776120525176ll, 3613847436684ll, 4704369434772ll, 6123969129810ll, 7971950000520ll, 10377579748374ll, 13509138183162ll, 17585681474148ll, 22892370891330ll, 29800413809730ll, 38793041799498ll, 50499301907904ll, 65738067298920ll, 85575306401886ll, 111398667487824ll, 145014533047950ll, 188774390188008ll, 245739297342390ll, 319894038598554ll, 416425845608070ll, 542087279517756ll, 705668533667544ll};

void prepare_table() {
  const int n = 120;
  auto str = generate_minimal_squares(n / 2);
  printf("max_num_of_word=%d\n", (int)str.size());
  
  printf("build AhoCorasick\n");
  AhoCorasick ac;
  for (auto &s: str) {
    if (static_cast<int>(s.size()) > (n + 1) / 3) continue;
    auto t = s + s;
    ac.ins(t.c_str());
  }
  ac.build();
  printf("ac.size()=%d\n", ac.size());

  puts("calculate answer part 1");
  std::vector<std::vector<i64>> dp(n + 1, std::vector<i64>(ac.size()));
  for (int state = 0; state < ac.size(); ++state) {
    dp[0][state] = !ac.trans[state].mark;
  }
  table[0] = 1;
  for (int len = 1; len <= n; ++len) {
    for (int state = 0; state < ac.size(); ++state) {
      if (ac.trans[state].mark) continue;
      for (int o = 0; o < 3; ++o) {
        int go = ac.trans[state].go[o];
        dp[len][state] += dp[len - 1][go];
      }
    }
    table[len] = dp[len][ac.root];
  }

  puts("calculate answer part 2");
  for (auto &s: str) {
    if (s.size() <= (n + 1) / 3) continue;
    int state = ac.go(s.c_str());
    std::reverse(s.begin(), s.end());
    int state_rev = ac.go(s.c_str());
    std::reverse(s.begin(), s.end());

    for (int len = 2 * s.size(); len <= n; ++len) {
      for (int start = 0; start + 2 * static_cast<int>(s.size()) <= len; ++start) {
        int o = s.back() - 'a';
        i64 prefix = start == 0;
        if (start) {
          for (int p = 0; p < 3; ++p) if (p != o) {
            prefix += dp[start - 1][ac.trans[state_rev].go[p]];
          }
        }
        i64 suffix = dp[len - start - 2 * s.size()][state];
        table[len] -= prefix * suffix;
      }
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) printf("%lld\n", table[i]);
  return 0;
}
