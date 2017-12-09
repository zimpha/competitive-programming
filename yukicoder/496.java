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
        Task496 solver = new Task496();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task496 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int m = in.nextInt();
            int q = in.nextInt();
            int f = in.nextInt();
            int[][] dp = new int[n + 1][];
            for (int i = 0; i <= n; ++i) {
                dp[i] = new int[m + 1];
                Arrays.fill(dp[i], 1000000000);
            }
            dp[0][0] = 0;
            for (int i = 0; i < q; i++) {
                int x = in.nextInt();
                int y = in.nextInt();
                int z = in.nextInt();
                for (int a = n; a >= x; --a) {
                    for (int b = m; b >= y; --b) {
                        dp[a][b] = Math.min(dp[a][b], z + dp[a - x][b - y]);
                    }
                }
            }
            int ret = (n + m) * f;
            for (int i = 0; i <= n; ++i) {
                for (int j = 0; j <= m; ++j) {
                    ret = Math.min(ret, dp[i][j] + Math.abs(n - i) * f + Math.abs(m - j) * f);
                }
            }
            out.println(ret);
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

    }
}

