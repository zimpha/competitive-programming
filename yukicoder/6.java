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
        Task006 solver = new Task006();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task006 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int k = in.nextInt();
            int n = in.nextInt();
            boolean[] mark = new boolean[n + 1];
            List<Integer> pl = new ArrayList<>();
            for (int i = 2; i <= n; ++i) {
                if (mark[i]) continue;
                if (i >= k) {
                    pl.add(i);
                }
                for (int j = i + i; j <= n; j += i) {
                    mark[j] = true;
                }
            }
            int cnt = 0;
            int ret = -1;
            for (int i = 0, j; i < pl.size(); ++i) {
                mark = new boolean[9];
                for (j = i; j < pl.size(); ++j) {
                    if (mark[pl.get(j) % 9]) {
                        break;
                    }
                    mark[pl.get(j) % 9] = true;
                }
                if (j - i >= cnt) {
                    cnt = j - i;
                    ret = pl.get(i);
                }
            }
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

    }
}

