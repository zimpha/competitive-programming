import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
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
        Task004 solver = new Task004();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task004 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            boolean[] dp = new boolean[n * 100 + 1];
            dp[0] = true;
            int sum = 0;
            for (int i = 0; i < n; i++) {
                int w = in.nextInt();
                sum += w;
                for (int j = sum; j >= w; --j) {
                    dp[j] |= dp[j - w];
                }
            }
            if (sum % 2 == 0 && dp[sum / 2]) {
                out.println("possible");
            } else {
                out.println("impossible");
            }
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

