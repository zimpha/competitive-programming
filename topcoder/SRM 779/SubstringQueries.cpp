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
using uint64 = unsigned long long;
const uint64 seed = 65537;

class SubstringQueries {
    public:
    long long solve(string s, int k) {
      int n = s.size();
      s = s + s;
      std::vector<uint64> hash(n * 2 + 1), pw(n * 2 + 1, 1);
      hash[n * 2] = 0;
      for (int i = 1; i <= n * 2; ++i) {
        pw[i] = pw[i - 1] * seed;
      }
      for (int i = n * 2 - 1; i >= 0; --i) {
        hash[i] = hash[i + 1] * seed + s[i];
      }
      std::vector<int> idx(n);
      for (int i = 0; i < n; ++i) idx[i] = i;

      auto cmp = [&](int x, int y, int len) {
        int l = 0, r = len;
        while (l < r) {
          int m = (l + r + 1) >> 1;
          auto h1 = hash[x] - hash[x + m] * pw[m];
          auto h2 = hash[y] - hash[y + m] * pw[m];
          if (h1 == h2) l = m;
          else r = m - 1;
        }
        if (l == len) return 0;
        return s[x + l] < s[y + l] ? -1 : 1;
      };

      std::sort(idx.begin(), idx.end(), [&](int x, int y) {
        auto r = cmp(x, y, n);
        if (r == 0) return x < y;
        else return r == -1;
      });

      int64 bound = (int64)k * n, ret = 0;
      for (int x = 1; x <= n; ++x) {
        int s = 0;
        while (s < n && idx[s] + x > bound) ++s;
        int best = idx[s];
        for (int i = s + 1; i < n; ++i) if (idx[s] + x <= bound) {
          if (cmp(idx[s], idx[i], x) == 0) best = std::min(best, idx[i]);
          else break;
        }
        ret += best;
      }
      if (k == 1) return ret;
      int best = idx[0];
      for (int i = 1; i < n; ++i) {
        if (cmp(idx[i], idx[0], n) == 0) best = std::min(best, idx[i]);
        else break;
      }
      ret += (bound - n * 2) * best;
      for (int64 x = bound - n + 1; x <= bound; ++x) {
        int s = 0;
        while (s < n && idx[s] + x > bound) ++s;
        int best = idx[s];
        for (int i = s + 1; i < n; ++i) if (idx[s] + x <= bound) {
          if (cmp(idx[s], idx[i], n) == 0) best = std::min(best, idx[i]);
          else break;
        }
        ret += best;
      }
      return ret;
    }
};

// CUT begin
ifstream data("SubstringQueries.sample");

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

bool do_test(string S, int k, long long __expected) {
    time_t startClock = clock();
    SubstringQueries *instance = new SubstringQueries();
    long long __result = instance->solve(S, k);
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
        string S;
        from_stream(S);
        int k;
        from_stream(k);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1582652522;
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
        cout << "SubstringQueries (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
