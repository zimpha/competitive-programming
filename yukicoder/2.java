import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.HashMap;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.Map;
import java.io.BufferedReader;
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
        Task002 solver = new Task002();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task002 {
        Map<Integer, Boolean> cache;
        ArrayList<Integer> p;

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            cache = new HashMap<>();
            p = new ArrayList<>();
            int m = n;
            for (int i = 2; i * i <= m; ++i) {
                if (m % i == 0) {
                    p.add(i);
                    while (m % i == 0) m /= i;
                }
            }
            if (m > 1) {
                p.add(m);
            }
            if (calc(n)) out.println("Alice");
            else out.println("Bob");
        }

        boolean calc(int n) {
            if (n == 1) {
                return false;
            }
            if (cache.containsKey(n)) {
                return cache.get(n);
            }
            boolean ret = false;
            for (int v : p) {
                if (n % v != 0) continue;
                int m = n;
                while (m % v == 0) {
                    m /= v;
                    if (!calc(m)) {
                        ret = true;
                    }
                }
            }
            cache.put(n, ret);
            return cache.get(n);
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

