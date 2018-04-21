package main;

import javax.swing.*;
import java.util.LinkedList;
import java.util.Queue;

public class PingPongQueue {
    public int[] whoPlaysNext(int[] skills, int N, int K) {
        Queue<Integer> q = new LinkedList<>();
        for (int s: skills) {
            q.add(s);
        }
        int a = -1, b = -1;
        int[] cnt = new int[100];
        int L = 0, R = 0;
        for (int i = 0; i < K; ++i) {
            if (a == -1) a = q.poll();
            if (b == -1) b = q.poll();
            if (a > b) {
                int t = a;
                a = b;
                b = t;
            }
            L = a;
            R = b;
            cnt[b]++;
            cnt[a] = 0;
            q.add(a);
            a = -1;
            if (cnt[b] == N) {
                q.add(b);
                cnt[b] = 0;
                b = -1;
            }
        }
        return new int[]{L, R};
    }
}
