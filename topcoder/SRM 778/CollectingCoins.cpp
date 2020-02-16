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
#include <functional>

using namespace std;

using int64 = long long;

class CollectingCoins {
 public:
  long long maxValue(int m, int k, vector<int> v, vector<int> d) {
    std::vector<int64> base(k * 4 + 1);
    for (int x = 1; x <= k; ++x) {
      for (size_t i = 0; i < v.size(); ++i) {
        base[x] += (int64)v[i] * (x - 1 - (x - 1) / d[i]);
      }
    }
    for (int x = k + 1; x <= 4 * k; ++x) {
      for (int i = 1; i <= k; ++i) {
        base[x] = std::max(base[x], base[x - i] + base[i]);
      }
    }

    if (m <= 4 * k) {
      int64 best = 0;
      for (int i = 1; i < k && i <= m; ++i) {
        best = std::max(best, base[m - i] + base[i + 1]);
      }
      return best;
    }

    std::function<std::vector<int64>(int)> solve = [&] (int n) {
      std::vector<int64> res(k * 2 + 1);
      assert(n >= k + 1);
      if (n + k <= 4 * k) {
        for (int x = -k; x <= k; ++x) res[x + k] = base[n + x];
        return res;
      }
      auto tmp = solve(n / 2);
      int nn = n / 2 * 2;
      for (int x = -k; x <= k; ++x) {
        for (int y = -k; y <= k; ++y) {
          int u = x + n / 2 + y + n / 2;
          if (nn - k <= u && u <= nn + k) {
            res[u - (nn - k)] = std::max(res[u - (nn - k)], tmp[x + k] + tmp[y + k]);
          }
        }
      }
      if (n & 1) {
        for (int i = 0; i < 2 * k; ++i) tmp[i] = res[i + 1];
        tmp.back() = 0;
        for (int i = 1; i <= k; ++i) {
          tmp[2 * k] = std::max(tmp[2 * k], tmp[2 * k - i] + base[i]);
        }
        res = tmp;
      }
      return res;
    };

    auto ret = solve(m);

    int64 best = 0;
    for (int i = 1; i < k; ++i) {
      best = std::max(best, ret[k - i] + base[i + 1]);
    }

    return best;
  }
};

// CUT begin
ifstream data("CollectingCoins.sample");

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

bool do_test(int m, int k, vector<int> v, vector<int> d, long long __expected) {
  time_t startClock = clock();
  CollectingCoins *instance = new CollectingCoins();
  long long __result = instance->maxValue(m, k, v, d);
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
    int m;
    from_stream(m);
    int k;
    from_stream(k);
    vector<int> v;
    from_stream(v);
    vector<int> d;
    from_stream(d);
    next_line();
    long long __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(m, k, v, d, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1581872618;
    double PT = T / 60.0, TT = 75.0;
    cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
    cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
    cout << "CollectingCoins (600 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
