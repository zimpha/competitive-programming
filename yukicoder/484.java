import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Chiaki.Hoshinomori
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Task484 solver = new Task484();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task484 {
        long[][][] dp;
        long[] A;

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            A = in.nextLongArray(n);
            dp = new long[2][][];
            dp[0] = new long[n][];
            dp[1] = new long[n][];
            for (int i = 0; i < n; i++) {
                dp[0][i] = new long[n];
                dp[1][i] = new long[n];
                Arrays.fill(dp[0][i], -1);
                Arrays.fill(dp[1][i], -1);
            }
            long ret = 1l << 60;
            for (int i = 0; i < n; i++) {
                ret = Math.min(ret, solve(i, i, 0));
            }
            out.println(ret);
        }

        private long solve(int l, int r, int s) {
            if (dp[s][l][r] >= 0) return dp[s][l][r];
            long ret = 1l << 60;
            if (l == 0 && r == A.length - 1) {
                if (s == 0) dp[s][l][r] = A[l];
                else dp[s][l][r] = A[r];
                return dp[s][l][r];
            }
            if (s == 0) {
                if (l > 0) {
                    ret = Math.min(ret, solve(l - 1, r, 0) + 1);
                }
                if (r + 1 < A.length) {
                    ret = Math.min(ret, solve(l, r + 1, 1) + r - l + 1);
                }
                ret = Math.max(ret, A[l]);
            } else {
                if (l > 0) {
                    ret = Math.min(ret, solve(l - 1, r, 0) + r - l + 1);
                }
                if (r + 1 < A.length) {
                    ret = Math.min(ret, solve(l, r + 1, 1) + 1);
                }
                ret = Math.max(ret, A[r]);
            }
            return dp[s][l][r] = ret;
        }

    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }

        public long[] nextLongArray(int n) {
            long[] r = new long[n];
            for (int i = 0; i < n; i++) {
                r[i] = nextLong();
            }
            return r;
        }

    }
}


