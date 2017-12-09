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
        Task498 solver = new Task498();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task498 {
        final static int mod = 1000000000 + 7;

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int Gx = in.nextInt();
            int Gy = in.nextInt();
            int K = in.nextInt();
            int[] x = new int[K];
            int[] y = new int[K];
            int[] n = new int[K];
            int total = 1;
            for (int i = 0; i < K; i++) {
                x[i] = in.nextInt();
                y[i] = in.nextInt();
                n[i] = in.nextInt();
                total *= n[i] + 1;
            }
            long[] fac = new long[100];
            long[] inv = new long[100];
            fac[0] = inv[0] = 1;
            for (int i = 1; i < 100; i++) {
                fac[i] = i * fac[i - 1] % mod;
                inv[i] = MathUtils.pow_mod(fac[i], mod - 2, mod);
            }
            long ret = 0;
            for (int mask = 0; mask < total; ++mask) {
                int[] cnt = new int[K];
                int m = mask;
                int sx = 0;
                int sy = 0;
                for (int i = 0; i < K; i++) {
                    cnt[i] = m % (n[i] + 1);
                    m /= (n[i] + 1);
                    sx += x[i] * cnt[i];
                    sy += y[i] * cnt[i];
                }
                if (sx == Gx && sy == Gy) {
                    int sum = 0;
                    long mul = 1;
                    for (int i = 0; i < K; ++i) {
                        sum += cnt[i];
                        mul = mul * inv[cnt[i]] % mod;
                    }
                    mul = mul * fac[sum] % mod;
                    ret += mul;
                }
            }
            out.println(ret % mod);
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

    static class MathUtils {
        public static long pow_mod(long a, long n, long mod) {
            long result = 1;
            for (; n >= 1; n >>= 1) {
                if (n % 2 == 1) result = result * a % mod;
                a = a * a % mod;
            }
            return result;
        }

    }
}

