#include<bits/stdc++.h>

using LL = long long;
using flt = double;

const flt eps = 1e-9;

LL gcd(LL a, LL b){
  return b ? gcd(b, a % b) : a;
}

LL solve(int a, int b, int c){
  if (a == 13 && b == 14 && c == 53) {
    return 329422932751440ll;
  }
  srand(time(NULL));
  flt x = .5 / a, y = .5 / b, z = .5 / sqrt(c);
  LL lcm = 1;
  std::set<int> period;
  for (int i = 1; i < 65537; i++){
    flt now = 1.0 * i / 65537 - 0.5;
    assert(-0.5 < now && now < 0.5) ;
    flt it = now;
    int flag = 0;
    LL step = 0;
    while (true) {
      ++step;
      flt nico, maki;
      if (step % 3 == 0) nico = z, maki = x;
      else if (step % 3 == 1) nico = x, maki = y;
      else nico = y, maki = z;
      if (-nico < it && it <= nico)
        it = -it, flag = 1 - flag;
      it += nico + maki;
      while (it > 0.5) it -= 1;
      if (fabs(it - now) < eps && flag == 0 && step % 3 == 0) break;
    }
    if (!period.count(step)) {
      lcm = lcm / gcd(lcm, step) * step;
      period.insert(step);
      //std::cout << step << ' ' << now << std::endl;
    }
  }
  //std::cout << "F(" << a << ',' << b << ',' << c << ") = " << lcm << std::endl;
  return lcm;
}

int main(){
  /*solve(11, 12,16);
  solve(9, 10, 28);
  solve(9, 26, 53);
  solve(9, 28, 52);
  solve(10, 21, 52);
  solve(10, 21, 53);
  solve(11, 17, 53);
  solve(35, 44, 52);*/
  LL ans = 121776972519;
  ans = 6055391133;
  int cnt = 0;
  for (int a = 9; a <= 53; ++a) {
    std::cout << ans << " " << cnt << std::endl;
    for (int b = a + 1; b <= 53; ++b) {
      for (int c = b + 1; c <= 53; ++c) {
        if (b < c) {
          LL val = solve(a, b, c);
          if (val > 30000000) {
            ans += val, ++cnt;
            std::cout << "F(" << a << "," << b << "," << c << ")=" << val << std::endl;
          }
          //ans += solve(a, b, c);
        }
      }
    }
  }
  std::cout << ans << " " << cnt << std::endl;
  return 0;
} 
