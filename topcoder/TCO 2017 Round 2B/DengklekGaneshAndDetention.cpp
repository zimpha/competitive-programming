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

const int N = 1000000 + 10;

class DengklekGaneshAndDetention {
    public:
    struct node {
      double p, e, ep;
      node(): p(0), e(0), ep(0) {}
    } dp[N][2];
    double getExpected(int n, int valInit, int valMul, int valAdd, int valMod) {
      std::vector<int> val(n), lamps(n), probs(n);
      val[0] = valInit;
      for (int i = 1; i < n; ++i) {
        val[i] = (1ll * val[i - 1] * valMul + valAdd) % valMod;
      }
      for (int i = 0; i < n; ++i) {
        lamps[i] = val[i] % 2;
        probs[i] = val[i] % 101;
      }
      std::vector<int> pre(n + 1), suf(n + 1);
      for (int i = n - 1; i >= 0; --i) {
        pre[i] = pre[i + 1] + lamps[i];
        suf[i] = suf[i + 1] + !lamps[i];
      }
      memset(dp, 0, sizeof(dp));
      dp[0][0].p = 1;
      double ret = 0;
      for (int i = 0; i < n; ++i) {
        for (int o = 0; o < 2; ++o) {
          if (dp[i][o].p < 1e-100) continue;
          int now = o ^ lamps[i];
          auto add = [](double p, double &v1, double p2, double v2) {
            v1 = (v1 * p + p2 * v2) / (p + p2);
          };
          if (now) {
            double head = probs[i] / 100.0, tail = 1.0 - head;
            if (probs[i]) {
              add(dp[i + 1][o].p, dp[i + 1][o].ep, head * dp[i][o].p, i - dp[i][o].ep);
              dp[i + 1][o].p += dp[i][o].p * head;
              ret += dp[i][o].p * head * dp[i][o].ep;
            }
            if (100 - probs[i]) {
              add(dp[i + 1][o ^ 1].p, dp[i + 1][o ^ 1].ep, tail * dp[i][o].p, dp[i][o].ep);
              dp[i + 1][o ^ 1].p += dp[i][o].p * tail;
              ret += dp[i][o].p * tail * (o ? pre[i] : suf[i]);
            }
          } else {
            add(dp[i + 1][o].p, dp[i + 1][o].ep, dp[i][o].p, dp[i][o].ep + 1);
            dp[i + 1][o].p += dp[i][o].p;
          }
        }
      }
      return ret;
    }
};

// CUT begin
ifstream data("DengklekGaneshAndDetention.sample");

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

bool do_test(int N, int valInit, int valMul, int valAdd, int valMod, double __expected) {
    time_t startClock = clock();
    DengklekGaneshAndDetention *instance = new DengklekGaneshAndDetention();
    double __result = instance->getExpected(N, valInit, valMul, valAdd, valMod);
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
        int valInit;
        from_stream(valInit);
        int valMul;
        from_stream(valMul);
        int valAdd;
        from_stream(valAdd);
        int valMod;
        from_stream(valMod);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, valInit, valMul, valAdd, valMod, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499532148;
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
        cout << "DengklekGaneshAndDetention (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
