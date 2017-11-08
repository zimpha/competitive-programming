import java.math.*;
import java.util.*;

public class Solution {
  static public void main(String args[]) {
    Scanner sc = new Scanner(System.in);
    BigInteger n = new BigInteger(sc.next());
    BigInteger zero = BigInteger.ZERO;
    BigInteger one = BigInteger.ONE;
    BigInteger two = BigInteger.valueOf(2);
    if (n.mod(two).equals(one)) {
      System.out.println(n.shiftRight(1));
    } else if (n.mod(BigInteger.valueOf(4)).equals(zero)) {
      System.out.println(n.shiftRight(1).subtract(one));
    } else {
      System.out.println(n.shiftRight(1).subtract(two));
    }
  }
};
