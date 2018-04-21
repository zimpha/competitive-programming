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

class DengklekGaneshAndChains {
    public:
    string getBestChains(vector<string> chains, vector<int> lengths) {
      int n = chains.size();
      int k = chains[0].size();
      for (auto &&s: chains) {
        auto t = s + s;
        for (int i = 0; i < k; ++i) {
          auto u = t.substr(i, k);
          assert(u.size() == k);
          if (u > s) s = u;
        }
      }
      std::sort(chains.begin(), chains.end(), std::greater<std::string>());
      //for (auto &&s: chains) std::cout << s << std::endl;
      std::string ret;
      for (auto &&l: lengths) {
        std::string add = "";
        for (int i = 0; i < n; ++i) {
          if (chains[i].size()) {
            add = chains[i].substr(0, l);
            break;
          }
        }
        int tar = -1;
        for (int i = 0; i < n; ++i) {
          if (chains[i].size() == 0) continue;
          if (chains[i].substr(0, l) == add) tar = i;
        }
        chains[tar] = "";
        ret += add;
      }
      return ret;
    }
};

// CUT begin
ifstream data("DengklekGaneshAndChains.sample");

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

bool do_test(vector<string> chains, vector<int> lengths, string __expected) {
    time_t startClock = clock();
    DengklekGaneshAndChains *instance = new DengklekGaneshAndChains();
    string __result = instance->getBestChains(chains, lengths);
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
        vector<string> chains;
        from_stream(chains);
        vector<int> lengths;
        from_stream(lengths);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(chains, lengths, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499529614;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "DengklekGaneshAndChains (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
