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
        Task489 solver = new Task489();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task489 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int d = in.nextInt();
            int k = in.nextInt();
            int[] x = new int[n];
            for (int i = 0; i < n; i++) {
                x[i] = in.nextInt();
            }
            int[] q = new int[n];
            int h = 0, t = -1;
            int ret = 0, a = 0, b = 0;
            for (int i = 0; i < n; i++) {
                while (h <= t && q[h] < i - d) ++h;
                if (h <= t && x[i] - x[q[h]] > ret) {
                    ret = x[i] - x[q[h]];
                    a = q[h];
                    b = i;
                }
                while (h <= t && x[q[t]] > x[i]) --t;
                q[++t] = i;
            }
            if (ret == 0) out.println(ret);
            else out.printf("%d\n%d %d\n", (long) k * ret, a, b);
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

