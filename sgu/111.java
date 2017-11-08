import java.util.*;
import java.io.*;
import java.math.*;

public class Solution {
	public static void main(String[] argv) throws IOException {
		Scanner cin = new Scanner(System.in);
		BigInteger X = cin.nextBigInteger();
		BigInteger left = BigInteger.ONE;
		BigInteger right = X.shiftRight(1);
		while (left.compareTo(right) < 0) {
			BigInteger mid = left.add(right).add(BigInteger.ONE).shiftRight(1);
			if (mid.multiply(mid).compareTo(X) <= 0) left = mid;
			else right = mid.subtract(BigInteger.ONE);
		}
		System.out.println(left);
	}
}
