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
        Task452 solver = new Task452();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task452 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int m = in.nextInt();
            int[][] line = new int[n * m * 2 + 2 * m][];
            int sz = 0;
            int ret = n * 2;
            for (int it = 0; it < m; it++) {
                int[][] card = new int[n][];
                int new_sz = sz;
                for (int j = 0; j < n; j++) {
                    card[j] = in.nextIntArray(n);
                }
                for (int i = 0; i < n; i++) {
                    int[] a = new int[n];
                    for (int j = 0; j < n; j++) {
                        a[j] = card[i][j];
                    }
                    Arrays.sort(a);
                    for (int k = 0; k < sz; k++) {
                        ret = Math.min(ret, intersect(a, line[k]));
                    }
                    line[new_sz++] = a;
                }
                for (int j = 0; j < n; j++) {
                    int[] a = new int[n];
                    for (int i = 0; i < n; i++) {
                        a[i] = card[i][j];
                    }
                    Arrays.sort(a);
                    for (int k = 0; k < sz; k++) {
                        ret = Math.min(ret, intersect(a, line[k]));
                    }
                    line[new_sz++] = a;
                }
                int[] a = new int[n];
                for (int i = 0; i < n; i++) {
                    a[i] = card[i][i];
                }
                Arrays.sort(a);
                for (int k = 0; k < sz; k++) {
                    ret = Math.min(ret, intersect(a, line[k]));
                }
                line[new_sz++] = a;
                a = new int[n];
                for (int i = 0; i < n; i++) {
                    a[i] = card[i][n - 1 - i];
                }
                Arrays.sort(a);
                for (int k = 0; k < sz; k++) {
                    ret = Math.min(ret, intersect(a, line[k]));
                }
                line[new_sz++] = a;
                sz = new_sz;
            }
            out.println(ret - 1);
        }

        private int intersect(int[] a, int[] b) {
            int cnt = a.length + b.length;
            for (int i = 0, j = 0; i < a.length && j < b.length; ) {
                if (a[i] == b[j]) {
                    --cnt;
                    ++i;
                    ++j;
                } else if (a[i] < b[j]) {
                    ++i;
                } else {
                    ++j;
                }
            }
            return cnt;
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

        public int[] nextIntArray(int n) {
            int[] r = new int[n];
            for (int i = 0; i < n; i++) {
                r[i] = nextInt();
            }
            return r;
        }

    }
}

