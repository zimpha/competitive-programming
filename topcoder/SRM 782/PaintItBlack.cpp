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

const int N = 200 + 10;

class PaintItBlack {
  public:
    std::vector<int> edges[N];

    vector<int> findWalk(int n, int u, vector<int> a, vector<int> b) {
      for (int i = 0; i < n; ++i) edges[i].clear();
      for (size_t i = 0; i < a.size(); ++i) {
        edges[a[i]].push_back(b[i]);
        edges[b[i]].push_back(a[i]);
      }
      return vector<int>();
    }
};

// CUT begin
ifstream data("PaintItBlack.sample");

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

template <typename T> string to_string(vector<T> ts) {
  stringstream s;
  s << "[ ";
  for (int i = 0; i < ts.size(); ++i) {
    if (i > 0) s << ", ";
    s << to_string(ts[i]);
  }
  s << " ]";
  return s.str();
}

bool do_test(int n, int u, vector<int> a, vector<int> b, vector<int> __expected) {
  time_t startClock = clock();
  PaintItBlack *instance = new PaintItBlack();
  vector<int> __result = instance->findWalk(n, u, a, b);
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
    int n;
    from_stream(n);
    int u;
    from_stream(u);
    vector<int> a;
    from_stream(a);
    vector<int> b;
    from_stream(b);
    next_line();
    vector<int> __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(n, u, a, b, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1585486133;
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
    cout << "PaintItBlack (1000 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
