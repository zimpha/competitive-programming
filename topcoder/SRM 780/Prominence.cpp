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

using int64 = long long;

class Prominence {
  public:
    long long sumOfProminences(int n, vector<int> coef, vector<int> idx, vector<int> val) {
      std::vector<int> h(n);
      for (int i = 0; i < n; ++i) {
        int p = i % 2;
        int64 a = coef[p * 3];
        int64 b = coef[p * 3 + 1];
        int64 c = coef[p * 3 + 2];
        h[i] = (((a * i + b) % 1000000007) * i + c) % 1000000007;
      }
      for (size_t j = 0; j < idx.size(); ++j) {
        h[idx[j]] = val[j];
      }
      std::vector<int> l(n), r(n), lm(n), rm(n);
      for (int i = 0; i < n; ++i) {
        lm[i] = h[i];
        int j = i - 1;
        while (j >= 0 && h[j] <= h[i]) {
          lm[i] = std::min(lm[i], lm[j]);
          j = l[j];
        }
        l[i] = j;
      }
      for (int i = n - 1; i >= 0; --i) {
        rm[i] = h[i];
        int j = i + 1;
        while (j < n && h[j] <= h[i]) {
          rm[i] = std::min(rm[i], rm[j]);
          j = r[j];
        }
        r[i] = j;
      }
      int64 ret = 0;
      for (int i = 0; i < n; ++i) {
        //printf("i=%d h=%d l=%d r=%d lm=%d rm=%d\n", i, h[i], l[i], r[i], lm[i], rm[i]);
        bool is_peak = true;
        if (i) is_peak &= h[i] > h[i - 1];
        if (i + 1 < n) is_peak &= h[i] > h[i + 1];
        if (!is_peak) continue;
        int mx = 0;
        if (l[i] != -1) mx = std::max(mx, lm[i]);
        if (r[i] != n) mx = std::max(mx, rm[i]);
        ret += h[i] - mx;
      }
      return ret;
    }
};

// CUT begin
ifstream data("Prominence.sample");

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

bool do_test(int N, vector<int> coef, vector<int> idx, vector<int> val, long long __expected) {
  time_t startClock = clock();
  Prominence *instance = new Prominence();
  long long __result = instance->sumOfProminences(N, coef, idx, val);
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
    vector<int> coef;
    from_stream(coef);
    vector<int> idx;
    from_stream(idx);
    vector<int> val;
    from_stream(val);
    next_line();
    long long __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(N, coef, idx, val, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1584069924;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
    cout << "Prominence (450 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
