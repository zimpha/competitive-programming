import java.util.*;
import java.math.*;

public class Solution {
  public static void main(String args[]) {
    Scanner sc = new Scanner(System.in);
    BigInteger n = new BigInteger(sc.next());
    int m = sc.nextInt();
    int p = sc.nextInt();
    int s = 1 << m;
    long ret[] = new long[s];
    for (int i = 0; i < s; ++i) {
      ret[i] = 1;
    }
    long trans[][] = new long[s][s];
    for (int i = 0; i < s; ++i) {
      for (int j = 0; j < s; ++j) {
        trans[i][j] = valid(i, j, m);
      }
    }
    char bits[] = n.subtract(BigInteger.ONE).toString(2).toCharArray();
    for (int b = 0; b < bits.length; ++b) {
      if (bits[bits.length - b - 1] == '1') {
        long tmp[] = new long[s];
        for (int i = 0; i < s; ++i) {
          for (int j = 0; j < s; ++j) {
            tmp[i] += trans[i][j] * ret[j];
          }
          tmp[i] %= p;
        }
        ret = tmp;
      }
      trans = mul(trans, trans, p);
    }
    long res = 0;
    for (long x: ret) res += x;
    System.out.println(res % p);
  }

  static long[][] mul(long a[][], long b[][], int mod) {
    int n = a.length;
    long c[][] = new long[n][n];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        c[i][j] = 0;
        for (int k = 0; k < n; ++k) {
          c[i][j] += a[i][k] * b[k][j];
        }
        c[i][j] %= mod;
      }
    }
    return c;
  }
  static int valid(int a, int b, int m) {
    for (int i = 1; i < m; ++i) {
      int cnt = (a >> i & 1) + (a >> (i - 1) & 1) +
                (b >> i & 1) + (b >> (i - 1) & 1);
      if (cnt == 0 || cnt == 4) return 0;
    }
    return 1;
  }
}
