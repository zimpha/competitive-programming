#include <cstdio>
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

const int N = 1000 + 10, mod = 1e9 + 7;

using int64 = long long;

int dp[N][2][2][2];

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}

class RestrictedLeaves {
  public:
    void dfs(int u) {
      for (auto &v: edges[u]) dfs(v);
      if (edges[u].empty()) {
        dp[u][0][0][0] = 1;
        dp[u][1][1][1] = 1;
        return;
      }
      static int f[2][2][2][2];
      memset(f, 0, sizeof(f));
      int now = 0, next = 1;
      for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) {
        add(f[now][0][a][b], dp[edges[u][0]][0][a][b]);
        add(f[now][0][a][b], dp[edges[u][0]][1][a][b]);
        add(f[now][1][a][b], dp[edges[u][0]][0][a][b]);
      }
      for (auto &v: edges[u]) {
        if (v == edges[u][0]) continue;
        memset(f[next], 0, sizeof(f[next]));
        for (int e = 0; e < 2; ++e) for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) {
          for (int ee = 0; ee < 2; ++ee) for (int aa = 0; aa < 2; ++aa) for (int bb = 0; bb < 2; ++bb) {
            if (!dp[v][ee][aa][bb]) continue;
            if (e && ee) continue;
            if (b && aa) continue;
            add(f[next][e][a][bb], (int64)f[now][e][a][b] * dp[v][ee][aa][bb] % mod);
          }
        }
        std::swap(now, next);
      }
      memcpy(dp[u], f[now], sizeof(f[now]));
    }
    std::vector<std::vector<int>> edges;
    int count(vector<int> parent) {
      int n = parent.size();
      edges.assign(n, {});
      for (int i = 1; i < n; ++i) {
        edges[parent[i]].push_back(i);
      }
      for (int i = 0; i < n; ++i) {
        std::sort(edges[i].begin(), edges[i].end());
      }
      memset(dp, 0, sizeof(dp));
      dfs(0);
      int ret = 0;
      for (int e = 0; e < 2; ++e) for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) {
        if (a && b) continue;
        add(ret, dp[0][e][a][b]);
      }
      return ret;
    }
};

// CUT begin
ifstream data("RestrictedLeaves.sample");

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

bool do_test(vector<int> parent, int __expected) {
  time_t startClock = clock();
  RestrictedLeaves *instance = new RestrictedLeaves();
  int __result = instance->count(parent);
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
    vector<int> parent;
    from_stream(parent);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(parent, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1584106285;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
    cout << "RestrictedLeaves (1000 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
