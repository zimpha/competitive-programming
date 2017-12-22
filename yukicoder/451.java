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
        Task451 solver = new Task451();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task451 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            long[] b = in.nextLongArray(n);
            long l = 1, r = 1000000000000000000l;
            for (int i = 0; i < n; i++) {
                long ll = 0, rr = 0;
                if (i % 2 == 0) {
                    ll = b[i] - r;
                    rr = b[i] - l;
                } else {
                    ll = l - b[i];
                    rr = r - b[i];
                }
                l = Math.max(1, ll);
                r = Math.min(rr, 1000000000000000000l);
                if (l > r) {
                    out.println("-1");
                    return;
                }
            }
            long[] a = new long[n + 1];
            a[n] = l;
            for (int i = n; i > 0; i--) {
                if (i % 2 == 1) {
                    a[i - 1] = b[i - 1] - a[i];
                } else {
                    a[i - 1] = b[i - 1] + a[i];
                }
            }
            out.println(n + 1);
            for (int i = 0; i <= n; i++) {
                out.println(a[i]);
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

