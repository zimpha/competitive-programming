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
        Task493 solver = new Task493();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task493 {
        long[] sum;
        long[] prod;
        long[] len;
        String[] digits;
        static final int mod = 1000000000 + 7;

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int K = in.nextInt();
            long L = in.nextLong();
            long R = in.nextLong();

            sum = new long[100];
            prod = new long[100];
            len = new long[100];
            digits = new String[100];

            sum[0] = 0;
            prod[0] = 1;
            len[0] = 0;
            int m = 0;
            for (int i = 1; i <= K && i < 100; ++i) {
                digits[i] = new Integer(i * i).toString();
                len[i] = len[i - 1] * 2 + digits[i].length();
                sum[i] = sum[i - 1] * 2;
                prod[i] = prod[i - 1] * prod[i - 1] % mod;
                for (char c : digits[i].toCharArray()) {
                    int d = c - '0';
                    if (d == 0) d = 10;
                    sum[i] = sum[i] + d;
                    prod[i] = prod[i] * d % mod;
                }
                m = i;
                if (len[i] >= R) break;
            }
            if (len[m] < R) {
                out.println(-1);
                return;
            }
            long[] A = calc(R, m);
            long[] B = calc(L - 1, m);
            long x = A[0] - B[0];
            long y = A[1] * MathUtils.pow_mod(B[1], mod - 2, mod) % mod;
            out.printf("%d %d\n", x, y);
        }

        long[] calc(long n, int m) {
            if (n <= 0) {
                return new long[]{0, 1};
            }
            if (len[m - 1] >= n) {
                return calc(n, m - 1);
            }
            long x = sum[m - 1];
            long y = prod[m - 1];
            for (int i = 0; i < digits[m].length() && i + 1 + len[m - 1] <= n; ++i) {
                int d = digits[m].charAt(i) - '0';
                if (d == 0) d = 10;
                x = x + d;
                y = y * d % mod;
            }
            long[] t = calc(n - len[m - 1] - digits[m].length(), m - 1);
            return new long[]{x + t[0], y * t[1] % mod};
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

        public long nextLong() {
            return Long.parseLong(next());
        }

    }
}

