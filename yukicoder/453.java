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
        Task453 solver = new Task453();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task453 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            // 3/4 * x + 2/7 * y <= C
            // 1/4 * x + 5/7 * y <= D
            // max z = 1000 * x + 2000 * y
            double C = in.nextDouble();
            double D = in.nextDouble();
            double x = (C * 5 / 7 - D * 2 / 7) / (0.75 * 5 / 7 - 0.25 * 2 / 7);
            double y = (C - x * 0.75) / (2.0 / 7);
            double ret = 0;
            if (x > 0 && y > 0) {
                ret = calc(x, y);
            }
            ret = Math.max(ret, calc(Math.min(4 * C / 3, 4 * D), 0));
            ret = Math.max(ret, calc(0, Math.min(7 * C / 2, 7 * D / 5)));
            out.println(ret);
        }

        private double calc(double x, double y) {
            return x * 1000 + y * 2000;
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

        public double nextDouble() {
            return Double.parseDouble(next());
        }

    }
}

