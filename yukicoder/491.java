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
        Task491 solver = new Task491();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task491 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            long n = in.nextLong();
            n = n / 1000000001;
            if (n == 0) {
                out.println(0);
            } else {
                int ret = 0;
                char[] s = new Long(n).toString().toCharArray();
                int[] pw = new int[10];
                pw[0] = 1;
                for (int i = 1; i < 10; i++) {
                    pw[i] = pw[i - 1] * 10;
                }
                for (int i = 1; i < s.length; ++i) {
                    ret += 9 * pw[(i + 1) / 2 - 1];
                }
                int now = 0;
                for (int i = 0; i < (s.length + 1) / 2; i++) {
                    now = now * 10 + s[i] - '0';
                    int coef = s[i] - '0';
                    int rest = (s.length + 1) / 2 - (i + 1);
                    if (i == 0) --coef;
                    ret += coef * pw[rest];
                }
                now *= pw[s.length - (s.length + 1) / 2];
                for (int i = 0; i < s.length - (s.length + 1) / 2; ++i) {
                    now += pw[i] * (s[i] - '0');
                }
                if (now <= n) ++ret;
                out.println(ret);
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

        public long nextLong() {
            return Long.parseLong(next());
        }

    }
}

