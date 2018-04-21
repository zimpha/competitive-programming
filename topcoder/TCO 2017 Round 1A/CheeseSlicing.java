package main;

import java.util.Arrays;

public class CheeseSlicing {
    int[] dp;
    public int totalArea(int A, int B, int C, int S) {
        dp = new int[101 * 101 * 101];
        Arrays.fill(dp, -1);
        return solve(A, B, C, S);
    }

    private int id(int A, int B, int C) {
        return A * 101 * 101 + B * 101 + C;
    }
    int solve(int A, int B, int C, int S) {
        int min = Math.min(A, Math.min(B, C));
        if (min < S) return 0;
        int e = id(A, B, C);
        if (dp[e] != -1) return dp[e];
        dp[e] = 0;
        dp[e] = Math.max(dp[e], solve(A - S, B, C, S) + B * C);
        dp[e] = Math.max(dp[e], solve(A, B - S, C, S) + A * C);
        dp[e] = Math.max(dp[e], solve(A, B, C - S, S) + A * B);
        return dp[e];
    }
}
