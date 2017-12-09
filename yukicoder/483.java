import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Collection;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.Queue;
import java.io.BufferedReader;
import java.util.LinkedList;
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
        Task483 solver = new Task483();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task483 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int m = in.nextInt();
            int n = 10000;
            int[] deg = new int[n];
            ArrayList<Integer>[] graph = new ArrayList[n];
            for (int i = 0; i < n; i++) {
                graph[i] = new ArrayList<>();
            }
            for (int i = 0; i < m; i++) {
                int r0 = in.nextInt() - 1;
                int c0 = in.nextInt() - 1;
                int r1 = in.nextInt() - 1;
                int c1 = in.nextInt() - 1;
                int u = r0 * 100 + c0;
                int v = r1 * 100 + c1;
                graph[u].add(v);
                graph[v].add(u);
                deg[u]++;
                deg[v]++;
            }
            boolean[] mark = new boolean[n];
            Queue<Integer> queue = new LinkedList<>();
            for (int i = 0; i < n; i++) {
                if (deg[i] == 1) {
                    queue.add(i);
                    mark[i] = true;
                }
            }
            while (!queue.isEmpty()) {
                int u = queue.poll();
                for (int v : graph[u]) {
                    if (!mark[v] && --deg[v] == 1) {
                        queue.add(v);
                        mark[v] = true;
                    }
                }
            }
            boolean valid = true;
            for (int i = 0; i < n; i++) {
                if (!mark[i] && deg[i] != 2 && deg[i] != 0) {
                    valid = false;
                }
            }
            if (valid) out.println("YES");
            else out.println("NO");
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

