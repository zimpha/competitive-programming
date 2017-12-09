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
        Task488 solver = new Task488();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task488 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int m = in.nextInt();
            boolean[][] g = new boolean[n][];
            for (int i = 0; i < n; i++) {
                g[i] = new boolean[n];
            }
            for (int i = 0; i < m; i++) {
                int a = in.nextInt();
                int b = in.nextInt();
                g[a][b] = g[b][a] = true;
            }
            int ret = 0;
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    if (a == b) continue;
                    ;
                    for (int c = 0; c < n; c++) {
                        if (a == c || b == c) continue;
                        for (int d = 0; d < n; d++) {
                            if (a == d || b == d || c == d) continue;
                            if (g[a][b] && g[b][c] && g[c][d] && g[d][a] && !g[a][c] && !g[b][d]) {
                                ++ret;
                            }
                        }
                    }
                }
            }
            out.println(ret / 8);
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

