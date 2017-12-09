import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
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
        Task001 solver = new Task001();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task001 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int N = in.nextInt();
            int C = in.nextInt();
            int[][] dist = new int[N][];
            ArrayList<Integer>[] graph = new ArrayList[N];
            for (int i = 0; i < N; i++) {
                graph[i] = new ArrayList<>();
                dist[i] = new int[C + 1];
                Arrays.fill(dist[i], 1000000);
            }
            int V = in.nextInt();
            int[] S = in.nextIntArray(V);
            int[] T = in.nextIntArray(V);
            int[] Y = in.nextIntArray(V);
            int[] M = in.nextIntArray(V);
            for (int i = 0; i < V; i++) {
                graph[S[i] - 1].add(i);
            }
            dist[0][0] = 0;
            for (int i = 0; i < N - 1; i++) {
                for (int j = 0; j < C; j++) {
                    if (dist[i][j] == 1000000) continue;
                    ;
                    for (int k : graph[i]) {
                        if (j + Y[k] <= C) {
                            dist[T[k] - 1][j + Y[k]] = Math.min(dist[T[k] - 1][j + Y[k]], dist[i][j] + M[k]);
                        }
                    }
                }
            }
            int ret = -1;
            for (int i = 0; i <= C; i++) {
                if (ret == -1 || dist[N - 1][i] < ret) {
                    ret = dist[N - 1][i];
                }
            }
            if (ret == 1000000) ret = -1;
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

        public int[] nextIntArray(int n) {
            int[] r = new int[n];
            for (int i = 0; i < n; i++) {
                r[i] = nextInt();
            }
            return r;
        }

    }
}

