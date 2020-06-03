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

class IterateOverACube {
    public:
    int64 cnt(int n, int s) {
        int64 r = 0;
        for (int x = 0; x < n && x <= s; ++x) {
            int u = std::max(0, (s - x) - (n - 1));
            int v = std::min<int64>(n - 1, s - x);
            u = std::min(u, n);
            r += (int64)u * n;
            r += int64(s - x - u + s - x - v + 2) * (v - u + 1) / 2;
        }
        return r;
    }
    vector<int> findCell(int N, long long index) {
        ++index;
        int l = 0, r = N * 3 - 3;
        while (l < r) {
            int m = (l + r - 1) >> 1;
            if (cnt(N, m) >= index) r = m;
            else l = m + 1;
        }
        if (l) index -= cnt(N, l - 1);
        for (int x = 0; x < N; ++x) {
            int yl = std::max(0, l - x - (N - 1));
            int yr = std::min(N - 1, l - x);
            if (yl > yr) continue;
            if (yr - yl + 1 >= index) {
                return {x, yl + index - 1, l - x - (yl + index - 1)};
            } else {
                index -= yr - yl + 1;
            }
        }
        return {0, 0, 0};
    }
};

// CUT begin
ifstream data("IterateOverACube.sample");

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

bool do_test(int N, long long index, vector<int> __expected) {
    time_t startClock = clock();
    IterateOverACube *instance = new IterateOverACube();
    vector<int> __result = instance->findCell(N, index);
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
        long long index;
        from_stream(index);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, index, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1579230188;
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
        cout << "IterateOverACube (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
