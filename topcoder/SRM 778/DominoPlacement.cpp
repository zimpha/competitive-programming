#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const int mod = 1e9 + 7;

int dp[2][1 << 18];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

class DominoPlacement {
 public:
  int countWays(vector<string> T) {
    int n = T.size(), m = T[0].size();
    std::vector<std::string> s;
    if (n < m) {
      std::swap(n, m);
      s.assign(n, std::string(m, '.'));
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          s[i][j] = T[j][i];
        }
      }
    } else {
      s = T;
    }
    for (int i = 0; i < n; ++i) s[i].push_back('#');
    s.push_back(std::string(m, '#'));
    memset(dp, 0, sizeof(dp));
    int *f = dp[0], *g = dp[1];
    int ms = 1 << (m + 1);
    f[0] = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        memset(g, 0, sizeof(*g) * ms);
        for (int msk = 0; msk < ms; ++msk) if (f[msk]) {
          int mask = msk, ways = f[msk];
          if (j == 0) mask = ((msk << 1) | (msk >> m & 1)) & (ms - 1);
          if (j == 0 && (mask & 1)) continue;
          int new_mask = (mask >> (j + 2) << (j + 2)) | (mask & ((1 << j) - 1));
          if (s[i][j] == '#') {
            if ((~mask >> j & 1) && (~mask >> (j + 1) & 1)) add(g[new_mask], ways);
          } else {
            if ((~mask >> j & 1) && (~mask >> (j + 1) & 1)) add(g[new_mask], ways); // put #
            if ((~mask >> j & 1) && (mask >> (j + 1) & 1)) add(g[new_mask], ways); // put ^
            if (~mask >> j & 1) add(g[new_mask | (1 << j)], ways); // put v
            if (~mask >> (j + 1) & 1) add(g[new_mask | (1 << (j + 1))], ways); // put >
            if ((mask >> j & 1) && (~mask >> (j + 1) & 1)) add(g[new_mask], ways); // put <
          }
        }
        std::swap(f, g);
      }
    }
    return f[0];
  }
};

// CUT begin
ifstream data("DominoPlacement.sample");

string next_line() {
  string s;
  getline(data, s);
  return s;
}

template <typename T> void from_stream(T &t) {
  stringstream ss(next_line());
  ss >> t;
}

void from_stream(string &s) {
  s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
  int len;
  from_stream(len);
  ts.clear();
  for (int i = 0; i < len; ++i) {
    T t;
    from_stream(t);
    ts.push_back(t);
  }
}

template <typename T>
string to_string(T t) {
  stringstream s;
  s << t;
  return s.str();
}

string to_string(string t) {
  return "\"" + t + "\"";
}

bool do_test(vector<string> T, int __expected) {
  time_t startClock = clock();
  DominoPlacement *instance = new DominoPlacement();
  int __result = instance->countWays(T);
  double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
  delete instance;

  if (__result == __expected) {
    cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
    return true;
  }
  else {
    cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
    cout << "           Expected: " << to_string(__expected) << endl;
    cout << "           Received: " << to_string(__result) << endl;
    return false;
  }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
  int cases = 0, passed = 0;
  while (true) {
    if (next_line().find("--") != 0)
      break;
    vector<string> T;
    from_stream(T);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(T, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1581874354;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2);
  set<int> cases;
  bool mainProcess = true;
  for (int i = 1; i < argc; ++i) {
    if ( string(argv[i]) == "-") {
      mainProcess = false;
    } else {
      cases.insert(atoi(argv[i]));
    }
  }
  if (mainProcess) {
    cout << "DominoPlacement (900 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
