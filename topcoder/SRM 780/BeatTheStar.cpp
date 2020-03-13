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

class BeatTheStar {
  public:
    double doesItMatter(int N, int G) {
      int m = (N + 1) * N / 2 + 1;
      std::vector<double> f(m), g(m);
      f[0] = 1;
      for (int i = 1; i < G; ++i) {
        g.assign(m, 0);
        for (int j = 0; j < m; ++j) {
          g[j] += f[j] * 0.5;
          if (i + j < m) g[i + j] += f[j] * 0.5;
        }
        f.swap(g);
      }
      auto a = f;
      f.assign(m, 0); f[0] = 1;
      for (int i = N; i > G; --i) {
        g.assign(m, 0);
        for (int j = 0; j < m; ++j) {
          g[j] += f[j] * 0.5;
          if (i + j < m) g[i + j] += f[j] * 0.5;
        }
        f.swap(g);
      }
      auto b = f;
      double ret = 0;
      for (int x = 0; x < m; ++x) if (a[x]) {
        for (int y = 0; y < m; ++y) if (b[y]) {
          if (x + y < (N + 1) * N / 2 - x - y && x + y + G > (N + 1) * N / 2 - x - y - G) ret += a[x] * b[y];
        }
      }
      return ret;
    }
};

// CUT begin
ifstream data("BeatTheStar.sample");

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

template <typename T>
string to_string(T t) {
  stringstream s;
  s << t;
  return s.str();
}

string to_string(string t) {
  return "\"" + t + "\"";
}

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int N, int G, double __expected) {
  time_t startClock = clock();
  BeatTheStar *instance = new BeatTheStar();
  double __result = instance->doesItMatter(N, G);
  double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
  delete instance;

  if (double_equal(__expected, __result)) {
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
    int G;
    from_stream(G);
    next_line();
    double __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(N, G, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1584069556;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
    cout << "BeatTheStar (250 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
