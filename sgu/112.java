import java.io.*;
import java.math.*;
import java.util.*;

public class Solution {

	public static void main(String[] args) throws IOException{
		Scanner cin = new Scanner(System.in);
		int a = cin.nextInt(), b = cin.nextInt();
		BigInteger A = BigInteger.valueOf(a);
		BigInteger B = BigInteger.valueOf(b);
		A = A.pow(b); B = B.pow(a);
		System.out.println(A.subtract(B));
	}
}

