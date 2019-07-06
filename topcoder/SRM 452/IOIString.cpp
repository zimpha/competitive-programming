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
const int mod = 1e9 + 7;

class IOIString {
    public:
    bool ok(char x, char y) {
        return x == '?' || x == y;
    }
    int countIOIs(vector<string> mask) {
        std::string s;
        for (auto &x: mask) s += x;
        int n = s.size(), m = 0;
        int64 ret = 1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '?') ret = ret * 2 % mod;
        }
        std::vector<int> sum(n + 1);
        for (int i = n - 1; i >= 0; --i) {
            sum[i] = sum[i + 1] + (s[i] == 'I');
        }

        auto valid = [&] (int l, int r) { // [l, r]
            if (l > r) return true;
            return sum[l] - sum[r + 1] == 0;
        };

        ret -= sum[0] == 0;
        for (int i = 0; i < n; ++i) {
            ret -= valid(0, i - 1) && valid(i + 1, n - 1) && ok(s[i], 'I');
            for (int d = 1; d < n; d += 2) {
                bool flag = valid(0, i - 1) && ok(s[i], 'I');
                for (int c = 2; i + (c - 1) * d < n; ++c) {
                    int r = i + d * (c - 1);
                    int l = r - d;
                    flag &= valid(l + 1, r - 1) && ok(s[r], 'I');
                    if (flag && valid(r + 1, n - 1)) {
                        --ret;
                    }
                }
            }
        }
        return (ret + mod) % mod;
    }
};

// CUT begin
ifstream data("IOIString.sample");

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

bool do_test(vector<string> mask, int __expected) {
    time_t startClock = clock();
    IOIString *instance = new IOIString();
    int __result = instance->countIOIs(mask);
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
        vector<string> mask;
        from_stream(mask);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(mask, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1562407914;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "IOIString (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
