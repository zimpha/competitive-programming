import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.util.Comparator;
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
        Task497 solver = new Task497();
        solver.solve(1, in, out);
        out.close();
    }

    static class Task497 {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int[][] box = new int[n][];
            for (int i = 0; i < n; i++) {
                box[i] = new int[3];
                for (int j = 0; j < 3; ++j) {
                    box[i][j] = in.nextInt();
                }
                Arrays.sort(box[i]);
            }
            Arrays.sort(box, new Comparator<int[]>() {

                public int compare(int[] o1, int[] o2) {
                    if (o1[0] != o2[0]) return o1[0] - o2[0];
                    if (o1[1] != o2[1]) return o1[1] - o2[1];
                    return o1[2] - o2[2];
                }
            });
            int[] dp = new int[n];
            int ret = 0;
            for (int i = 0; i < n; i++) {
                dp[i] = 1;
                for (int j = 0; j < i; j++) {
                    if (box[j][0] < box[i][0] && box[j][1] < box[i][1] && box[j][2] < box[i][2]) {
                        dp[i] = Math.max(dp[i], dp[j] + 1);
                    }
                }
                ret = Math.max(ret, dp[i]);
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

