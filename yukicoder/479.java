import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
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
        Task479 solver = new Task479();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task479 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int m = in.nextInt();
            int[] a = new int[m];
            int[] b = new int[m];
            boolean[] mark = new boolean[m];
            ArrayList<Integer>[] edges = new ArrayList[n];
            for (int i = 0; i < n; i++) {
                edges[i] = new ArrayList<>();
            }
            for (int i = 0; i < m; i++) {
                a[i] = in.nextInt();
                b[i] = in.nextInt();
                edges[a[i]].add(i);
                edges[b[i]].add(i);
            }
            boolean first = false;
            for (int i = n - 1; i >= 0; --i) {
                boolean buy = false;
                for (int e : edges[i]) {
                    if (mark[e]) continue;
                    if (a[e] + b[e] - i > i) buy = true;
                }
                if (buy) {
                    first = true;
                    for (int e : edges[i]) {
                        mark[e] = true;
                    }
                }
                if (first) {
                    if (buy) out.printf("1");
                    else out.printf("0");
                }
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

