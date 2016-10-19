#include <bits/stdc++.h>

//https://en.wikipedia.org/wiki/Biconjugate_gradient_stabilized_method
class BICGSTAB {
public:
  static constexpr double eps = 1.0e-12;
  typedef std::pair<int, double> element_t;
  typedef std::vector<element_t> row_t;
  typedef std::vector<double> vec_t;

  std::vector<row_t> A;
  int n;

  vec_t solve(vec_t b, vec_t x) {
    vec_t r0, r[2], p[2], v[2], t, s;
    double R[2], w[2], alpha, beta;
    r[0] = r0 = sub(b, mul(x));
    if (is_zero(r0)) return x;
    R[0] = alpha = w[0] = 1;
    v[0] = p[0] = vec_t(n);
    for (int it = 0; it < 1000; ++it) {
      int i = it & 1 ^ 1;
      R[i] = dot(r0, r[i ^ 1]);
      beta = (R[i] / R[i ^ 1]) * (alpha / w[i ^ 1]);
      p[i] = add(r[i ^ 1], mul(beta, sub(p[i ^ 1], mul(w[i ^ 1], v[i ^ 1]))));
      v[i] = mul(p[i]);
      alpha = R[i] / dot(r0, v[i]);
      s = sub(r[i ^ 1], mul(alpha, v[i]));
      t = mul(s);
      w[i] = dot(t, s) / dot(t, t);
      x = add(add(x, mul(alpha, p[i])), mul(w[i], s));
      if (is_zero(sub(b, mul(x)))) return x;
      r[i] = sub(s, mul(w[i], t));
    }
    return x;
  }

private:
  vec_t mul(const vec_t &x) {
    vec_t res(n);
    for (int i = 0; i < n; ++i) {
      for (auto &&e: A[i]) {
        int j = e.first;
        double v = e.second;
        res[i] += v * x[j];
      }
    }
    return res;
  }
  vec_t mul(const double x, const vec_t &a) {
    vec_t res(n);
    for (int i = 0; i < n; ++i) res[i] = x * a[i];
    return res;
  }
  vec_t add(const vec_t & a, const vec_t &b) {
    vec_t res(n);
    for (int i = 0; i < n; ++i) res[i] = a[i] + b[i];
    return res;
  }
  vec_t sub(const vec_t & a, const vec_t &b) {
    vec_t res(n);
    for (int i = 0; i < n; ++i) res[i] = a[i] - b[i];
    return res;
  }
  double dot(const vec_t &a, const vec_t &b) {
    double ret = 0;
    for (size_t i = 0; i < n; ++i) ret += a[i] * b[i];
    return ret;
  }
  bool is_zero(const vec_t &v) {
    for (auto &&x: v) if (fabs(x) > eps) return false;
    return true;
  }
} solver;

typedef std::vector<int> state;

std::map<state, int> cache;

double run() {
  return 0;
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}
