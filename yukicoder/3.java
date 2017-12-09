import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Collection;
import java.io.IOException;
import java.io.InputStreamReader;
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
        Task003 solver = new Task003();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task003 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int[] dis = new int[n + 1];
            Arrays.fill(dis, -1);
            Queue<Integer> queue = new LinkedList<>();
            dis[1] = 1;
            queue.add(1);
            while (!queue.isEmpty()) {
                int u = queue.poll();
                int v = popcount(u);
                if (u - v > 0 && dis[u - v] == -1) {
                    dis[u - v] = dis[u] + 1;
                    queue.add(u - v);
                }
                if (u + v <= n && dis[u + v] == -1) {
                    dis[u + v] = dis[u] + 1;
                    queue.add(u + v);
                }
            }
            out.println(dis[n]);
        }

        private int popcount(int n) {
            int r = 0;
            while (n > 0) {
                r += n % 2;
                n >>= 1;
            }
            return r;
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

