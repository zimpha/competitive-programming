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
        Task482 solver = new Task482();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task482 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            long K = in.nextLong();
            int[] P = in.nextIntArray(n);
            for (int i = 0; i < n; i++) {
                P[i] -= 1;
            }
            boolean[] mark = new boolean[n];
            int ret = 0;
            for (int i = 0; i < n; i++) {
                if (mark[i]) continue;
                for (int j = i; !mark[j]; j = P[j]) {
                    mark[j] = true;
                    ++ret;
                }
                --ret;
            }
            if (ret <= K && (ret % 2) == (K % 2)) {
                out.println("YES");
            } else {
                out.println("NO");
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

        public int[] nextIntArray(int n) {
            int[] r = new int[n];
            for (int i = 0; i < n; i++) {
                r[i] = nextInt();
            }
            return r;
        }

    }
}

