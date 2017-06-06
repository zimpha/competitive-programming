Sum[Length[Solve[3*a*a + 3*a*d + d*d == c*c && a > 0 && c > 0 && c <= 10^100 , {a, c}, Integers]], {d, 1, 100}]
