import java.io.*;
import java.math.*;
import java.util.*;


public class Solution {

	public static void main(String[] args) throws IOException{
		BigInteger F[] = new BigInteger[50];
		F[0] = F[1] = BigInteger.ONE;
		for (int i = 2; i < 50; ++ i) F[i] = F[i - 1].add(F[i - 2]);
		Scanner cin = new Scanner(System.in);
		int K = cin.nextInt();
		BigInteger ret = BigInteger.ZERO;
		for (int i = 0; i < K; ++ i) ret = ret.add(F[i]);
		System.out.println(ret);
	}

}
