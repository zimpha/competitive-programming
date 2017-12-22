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
        Task458 solver = new Task458();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task458 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int[] dp = new int[n + 1];
            Arrays.fill(dp, -1);
            boolean[] mark = new boolean[n + 1];
            dp[0] = 0;
            for (int i = 2; i <= n; i++) {
                if (mark[i]) continue;
                for (int j = n; j >= i; --j) {
                    if (dp[j - i] == -1) continue;
                    dp[j] = Math.max(dp[j], dp[j - i] + 1);
                }
                for (int j = i; j <= n; j += i) {
                    mark[j] = true;
                }
            }
            out.println(dp[n]);
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

