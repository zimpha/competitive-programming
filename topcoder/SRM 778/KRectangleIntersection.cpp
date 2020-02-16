#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

using int64 = long long;

class KRectangleIntersection {
 public:
 long long maxIntersection(vector<int> xl, vector<int> yl, vector<int> xh, vector<int> yh, int m) {
   int n = xl.size();
   int64 ret = 0;
   for (auto x1: xl) for (auto x2: xh) if (x1 < x2) {
     std::vector<std::pair<int, int>> ys;
     for (int i = 0; i < n; ++i) if (xl[i] <= x1 && x2 <= xh[i]) {
       ys.emplace_back(yl[i], yh[i]);
     }
     std::sort(ys.begin(), ys.end());
     std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
     for (auto &e: ys) {
       pq.push(e.second);
       while (pq.size() > m) pq.pop();
       if (pq.size() == m && pq.top() > e.first) {
         ret = std::max(ret, (int64)(x2 - x1) * (pq.top() - e.first));
       }
     }
   }
   return ret;
 }
};

// CUT begin
ifstream data("KRectangleIntersection.sample");

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

bool do_test(vector<int> xl, vector<int> yl, vector<int> xh, vector<int> yh, int k, long long __expected) {
  time_t startClock = clock();
  KRectangleIntersection *instance = new KRectangleIntersection();
  long long __result = instance->maxIntersection(xl, yl, xh, yh, k);
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
    vector<int> xl;
    from_stream(xl);
    vector<int> yl;
    from_stream(yl);
    vector<int> xh;
    from_stream(xh);
    vector<int> yh;
    from_stream(yh);
    int k;
    from_stream(k);
    next_line();
    long long __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(xl, yl, xh, yh, k, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1581871081;
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
    cout << "KRectangleIntersection (250 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
