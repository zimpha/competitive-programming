import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.math.BigInteger;
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
        Task492 solver = new Task492();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task492 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            long n = in.nextLong();
            out.println(solve(n - 1, BigInteger.valueOf(1000000007)));
            out.println(solve(n - 1, new BigInteger("101010101010101010101")));
        }

        BigInteger solve(long n, BigInteger mod) {
            BigInteger[] ret = new BigInteger[]{BigInteger.ONE, BigInteger.ONE};
            BigInteger[][] A = new BigInteger[2][];
            A[0] = new BigInteger[]{BigInteger.valueOf(100), BigInteger.ONE};
            A[1] = new BigInteger[]{BigInteger.ZERO, BigInteger.ONE};
            for (; n > 0; n >>= 1) {
                if (n % 2 == 1) {
                    BigInteger t0 = A[0][0].multiply(ret[0]).add(A[0][1].multiply(ret[1])).mod(mod);
                    BigInteger t1 = A[1][0].multiply(ret[0]).add(A[1][1].multiply(ret[1])).mod(mod);
                    ret[0] = t0;
                    ret[1] = t1;
                }
                A = mul(A, A, mod);
            }
            return ret[0];
        }

        private BigInteger[][] mul(BigInteger[][] a, BigInteger[][] b, BigInteger mod) {
            BigInteger[][] c = new BigInteger[2][];
            for (int i = 0; i < 2; i++) {
                c[i] = new BigInteger[2];
            }
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    c[i][j] = BigInteger.ZERO;
                    for (int k = 0; k < 2; k++) {
                        c[i][j] = c[i][j].add(a[i][k].multiply(b[k][j]));
                    }
                    c[i][j] = c[i][j].mod(mod);
                }
            }
            return c;
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

