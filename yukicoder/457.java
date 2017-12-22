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
        Task457 solver = new Task457();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task457 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            char[] s = in.next().toCharArray();
            int n = s.length;
            int[] nx = new int[n];
            int[] ny = new int[n];
            int[] cnt = new int[n + 1];
            for (int i = n - 1; i >= 0; i--) {
                cnt[i] = cnt[i + 1];
                if (s[i] == ')') ++cnt[i];
                nx[i] = i == n - 1 ? n : nx[i + 1];
                ny[i] = i == n - 1 ? n : ny[i + 1];
                if (s[i] == '^') nx[i] = i;
                if (s[i] == '*') ny[i] = i;
            }
            int left = 0, right = 0;
            for (int i = 0; i < n; i++) {
                if (s[i] != '(') continue;
                int a = nx[i];
                if (a >= n - 1) continue;
                a = nx[a + 1];
                if (a >= n - 1) continue;
                a = ny[a + 1];
                if (a != n) {
                    left += cnt[a + 1];
                }
            }
            for (int i = 0; i < n; i++) {
                if (s[i] != '(') continue;
                int a = ny[i];
                if (a >= n - 1) continue;
                a = nx[a + 1];
                if (a >= n - 1) continue;
                a = nx[a + 1];
                if (a != n) {
                    right += cnt[a + 1];
                }
            }
            out.printf("%d %d\n", left, right);
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

    }
}

