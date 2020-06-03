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


class FairSplit {
    public:
    int64 count_eq(int64 lx, int64 rx, int64 ly, int64 ry) {
        if (ry < lx) return 0;
        ly = std::max(ly, lx);
        if (ly >= rx) return (rx - lx + 1) * (ry - ly + 1);
        int64 ret = (ly - lx) * (ry - ly + 1);
        int64 u = std::min(rx, ry) - ly + 1;
        ret += u * (u + 1) / 2;
        ret += u * std::max(int64(0), ry - rx);
        return ret;
    }
    int64 count_le(int64 lx, int64 rx, int64 ly, int64 ry) {
        if (ry < lx) return 0;
        ly = std::max(ly, lx);
        if (ly > rx) return (rx - lx + 1) * (ry - ly + 1);
        int64 ret = (ly - lx) * (ry - ly + 1);
        int64 u = std::min(rx, ry) - ly + 1;
        ret += u * (u - 1) / 2;
        ret += u * std::max(int64(0), ry - rx);
        return ret;
    }
    bool check(int a, int b) {
        int s = 0;
        for (int i = a; i <= b; ++i) s += i;
        std::vector<int> dp(s + 1);
        dp[0] = 1;
        for (int i = a; i <= b; ++i) {
            for (int j = s; j >= i; --j) dp[j] |= dp[j - i];
        }
        return s % 2 == 0 && dp[s / 2];
    }
    long long count(int loA, int hiA, int loB, int hiB) {
        int64 ret = 0;
        for (int a = 0; a < 4 && a <= hiA; ++a) {
            for (int b = 0; b < 4 && b <= hiB; ++b) {
                if ((a + b) * (b - a + 4 + 1) % 4 != 0) continue;
                int rx = (hiA - a) / 4, lx = (std::max(0, loA - a) + 3) / 4;
                int ry = (hiB - b) / 4, ly = (std::max(0, loB - b) + 3) / 4;
                if (lx > rx || ly > ry) continue;
                if (a < b) ret += count_eq(lx, rx, ly, ry);
                else ret += count_le(lx, rx, ly, ry);
            }
        }
        for (int m = 2; (int64)m * m < 1e10; m += 2) {
            for (int a = 0; a < 4; ++a) {
                int b = (a + m) % 4;
                if ((a + b) * (b - a + 4 + 1) % 4 != 0) continue;
                if (a > hiA || a + m > hiB) continue;
                int rx = (hiA - a) / 4, lx = (std::max(0, loA - a) + 3) / 4;
                int ry = (hiB - a - m) / 4, ly = (std::max(0, loB - a - m) + 3) / 4;
                int64 l = std::max(lx, ly), r = std::min(rx, ry);
                int64 u = (int64)m * m / 4;
                if (u >= a) l = std::max<int64>(l, (u - a) / 4 + 1);
                if (l <= r) ret -= r - l + 1;
            }
        }
        return ret;
    }
};

// CUT begin
ifstream data("FairSplit.sample");

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

bool do_test(int loA, int hiA, int loB, int hiB, long long __expected) {
    time_t startClock = clock();
    FairSplit *instance = new FairSplit();
    long long __result = instance->count(loA, hiA, loB, hiB);
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
        int loA;
        from_stream(loA);
        int hiA;
        from_stream(hiA);
        int loB;
        from_stream(loB);
        int hiB;
        from_stream(hiB);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(loA, hiA, loB, hiB, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1579239387;
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
        cout << "FairSplit (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
