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
        Task501 solver = new Task501();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task501 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int d = in.nextInt();
            if (n * 2 == d) {
                for (int i = 0; i < n; i++) {
                    out.printf("B");
                }
            } else if (d <= n) {
                for (int i = 0; i < d; i++) {
                    out.printf("A");
                }
                for (int i = d; i < n; i++) {
                    out.printf("C");
                }
            } else {
                int y = d - n;
                int x = n - y;
                for (int i = 0; i < x; i++) {
                    out.printf("A");
                }
                for (int i = 0; i < y; i++) {
                    out.printf("B");
                }
            }
            out.println();
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

