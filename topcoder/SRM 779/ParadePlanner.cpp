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

using int64 = long long;

const int N = 500 + 10;

int g[N][N];
int64 ways[N][N];
int common[N][N];

class ParadePlanner {
    public:
    long long count(int n, int seed, int threshold, vector<int> toggle) {
      memset(g, 0, sizeof(g));
      memset(ways, 0, sizeof(ways));
      memset(common, 0, sizeof(common));
      int64 state = seed;
      for (int x = 0; x < n; ++x) for (int y = x + 1; y < n; ++y) {
        state = (state * 1103515245 + 12345) % (1 << 31);
        if (state < threshold) g[x][y] = g[y][x] = 1;
      }
      for (size_t i = 0; i < toggle.size(); i += 2) {
        int x = toggle[i], y = toggle[i + 1];
        if (g[x][y]) g[x][y] = g[y][x] = 0;
        else g[x][y] = g[y][x] = 1;
      }
      std::vector<int> deg(n);
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) deg[i] += g[i][j];
      }
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          for (int k = 0; k < n; ++k) if (k != i && k != j) {
            common[i][j] += g[i][k] && g[j][k];
          }
          if (!g[i][j]) continue;
          for (int k = 0; k < n; ++k) if (k != i && g[j][k]) {
            ways[i][j] += deg[k] - 1;
          }
        }
      }
      int64 ret = 0;
      for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
        ret += ways[i][j] * ways[j][i] * 2;
      }
      int64 loop4 = 0;
      for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (g[i][j]) {
        if (i == j) continue;
        for (int k = 0; k < n; ++k) if (i != k && j != k && g[i][k]) {
          assert(common[j][k] > 0);
          loop4 += common[j][k] - 1;
        }
      }
      int64 tri = 0;
      for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (i == j || !g[i][j]) continue;
        for (int k = 0; k < n; ++k) if (i != k && j != k) {
          if (!g[i][k] || !g[j][k]) continue;
          tri += (deg[k] - 2) * 2;
          tri += deg[k] - 1;
        }
      }
      return ret - loop4 - tri;
    }
};

// CUT begin
ifstream data("ParadePlanner.sample");

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

bool do_test(int N, int seed, int threshold, vector<int> toggle, long long __expected) {
  time_t startClock = clock();
  ParadePlanner *instance = new ParadePlanner();
  long long __result = instance->count(N, seed, threshold, toggle);
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
    int N;
    from_stream(N);
    int seed;
    from_stream(seed);
    int threshold;
    from_stream(threshold);
    vector<int> toggle;
    from_stream(toggle);
    next_line();
    long long __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(N, seed, threshold, toggle, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1582646747;
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
    cout << "ParadePlanner (900 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
