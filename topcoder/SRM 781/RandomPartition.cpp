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

class RandomPartition {
  public:
    int expectedSum(vector<int> nums, int N, int M, int B1, int B2) {
      std::vector<int64> h(N * 2);
      for (int i = 0; i < (int)nums.size(); ++i) h[i] = nums[i];
      for (int i = nums.size(); i < N * 2; ++i) {
        h[i] = (h[i - 1] * B1 + h[i - 2] * B2) % M;
      }
      std::sort(h.begin(), h.end());
      int64 sum = 0;
      for (int i = 0; i < N; ++i) sum += h[N * 2 - 1 - i] - h[i];
      int64 inv = 1;
      for (int i = 0; i < 786433 - 2; ++i) inv = inv * N % 786433;
      return sum * inv % 786433;
    }
};

// CUT begin
ifstream data("RandomPartition.sample");

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

bool do_test(vector<int> nums, int N, int M, int B1, int B2, int __expected) {
  time_t startClock = clock();
  RandomPartition *instance = new RandomPartition();
  int __result = instance->expectedSum(nums, N, M, B1, B2);
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
    vector<int> nums;
    from_stream(nums);
    int N;
    from_stream(N);
    int M;
    from_stream(M);
    int B1;
    from_stream(B1);
    int B2;
    from_stream(B2);
    next_line();
    int __answer;
    from_stream(__answer);

    cases++;
    if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
      continue;

    cout << "  Testcase #" << cases - 1 << " ... ";
    if ( do_test(nums, N, M, B1, B2, __answer)) {
      passed++;
    }
  }
  if (mainProcess) {
    cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
    int T = time(NULL) - 1584726151;
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
    cout << "RandomPartition (450 Points)" << endl << endl;
  }
  return run_test(mainProcess, cases, argv[0]);
}
// CUT end
