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
#include <cassert>

using namespace std;

using ll = long long;

inline ll mul_mod(ll a, ll b, ll mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  ll k = (ll)((long double)a * b / mod);
  ll res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

ll pow_mod(ll a, ll n, ll m) {
  ll res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (~n & 1) return false;
    const int u[] = {2,3,5,7,325,9375,28178,450775,9780504,1795265022,0};
    ll e = n - 1, a, c = 0; // 原理：http://miller-rabin.appspot.com/
    while (~e & 1) e >>= 1, ++c;
    for (int i = 0; u[i]; ++i) {
      if (n <= u[i]) return true;
      a = pow_mod(u[i], e, n);
      if (a == 1) continue;
      for (int j = 1; a != n - 1; ++j) {
        if (j == c) return false;
        a = mul_mod(a, a, n);
      }
    }
    return true;
}

class EllysPrimePals {
    public:
    std::vector<std::pair<int, int>> candidate[10];
    int add[10];
    std::vector<std::string> o;
    std::string ret;
    int s, m, n;
    bool check() {
      for (int i = 0; i < n; ++i) {
        ll now = 0;
        for (int j = 0; j < m; ++j) {
          int e = (o[i][j] - '0' - add[j] + 10) % 10;
          now = now * 10 + e;
        }
        if (!is_prime(now)) return false;
      }
      return true;
    }
    bool search(int d) {
      if (d == s) {
        if (check()) {
          ret = std::string(m, '0');
          for (int i = 0; i < m; ++i) {
            ret[i] = add[i] + '0';
          }
          return true;
        }
        return false;
      }
      for (auto &&e: candidate[d]) {
        add[d] = e.first;
        add[m - 1 - d] = e.second;
        if (search(d + 1)) return true;
      }
      return false;
    }
    string getKey(vector<string> numbers) {
      o = numbers;
      n = numbers.size();
      m = numbers[0].size();
      if (m == 1) {
        for (int d = 0; d < 10; ++d) {
          bool valid = true;
          for (int i = 0; i < n; ++i) {
            int x = (numbers[i][0] - '0' - d + 10) % 10;
            if (!is_prime(x)) valid = false;
          }
          if (valid) return std::string(1, d + '0');
        }
        return "No solution";
      }
      s = m / 2 + m % 2;
      for (int b = 0; b < s; ++b) {
        for (int d = 0; d < 10; ++d) {
          int last = -1;
          bool valid = true;
          for (int i = 0; i < n && valid; ++i) {
            int x = numbers[i][b] - '0';
            int y = numbers[i][m - 1 - b] - '0';
            int u = (x - d + 10) % 10;
            int e = (y - u + 10) % 10;

            if (b == 0 && d == 4 && m == 5) {
              //std::cout << x << ' ' << y << ' ' << u << ' ' << e << std::endl;
            }
            if (last == -1) last = e;
            if (last != e) valid = false;
            if (b == 0 && u == 0) valid = false;
            last = e;
          }
          if (b == 0 && d == 0) valid = false;
          if (valid) {
            candidate[b].emplace_back(d, last);
            //std::cout << b << ' ' << d << ' ' << last << std::endl;
          }
        }
      }
      if (!search(0)) return "No solution";
      else return ret;
    }
};

// CUT begin
ifstream data("EllysPrimePals.sample");

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

bool do_test(vector<string> numbers, string __expected) {
    time_t startClock = clock();
    EllysPrimePals *instance = new EllysPrimePals();
    string __result = instance->getKey(numbers);
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
        vector<string> numbers;
        from_stream(numbers);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numbers, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498289816;
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
        cout << "EllysPrimePals (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
