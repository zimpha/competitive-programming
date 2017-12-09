import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.List;
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
        Task007 solver = new Task007();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task007 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            boolean[] mark = new boolean[n + 1];
            List<Integer> pl = new ArrayList<>();
            for (int i = 2; i <= n; ++i) {
                if (!mark[i]) {
                    pl.add(i);
                    for (int j = i; j <= n; j += i) {
                        mark[j] = true;
                    }
                }
            }
            mark[0] = mark[1] = true;
            for (int i = 2; i <= n; ++i) {
                mark[i] = false;
                for (int p : pl) {
                    if (p > i) break;
                    if (!mark[i - p]) {
                        mark[i] = true;
                        break;
                    }
                }
            }
            if (mark[n]) out.println("Win");
            else out.println("Lose");
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

