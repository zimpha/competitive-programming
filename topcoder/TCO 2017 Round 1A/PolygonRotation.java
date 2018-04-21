package main;

public class PolygonRotation {
    int[] X;
    int[] Y;
    int n;
    public double getVolume(int[] x, int[] y) {
        n = x.length;
        X = y;
        Y = x;
        double pi = Math.acos(-1.0);
        double a = X[0];
        double b = X[0];
        for (int i = 0; i < n; i++) {
            b = Math.min(b, X[i]);
        }
        return asr(b, a, 1e-9) * pi;
    }
    int cnt = 0;
    double F(double x) {
        double y = 0;
        for (int i = 1; i < n; ++i) {
            int j = i - 1, k = (i + 1) % n;
            if (X[j] >= x && x >= X[i] && X[i] != X[j]) {
                y = Math.max(y, (x - X[j]) * (Y[i] - Y[j]) / (X[i] - X[j]) + Y[j]);
            }
            if (X[i] <= x && X[k] >= x && X[i] != X[k]) {
                y = Math.max(y, Math.abs((x - X[i]) * (Y[i] - Y[k]) / (X[i] - X[k]) + Y[i]));
            }
        }
        return y * y;
    }
    double simpson(double a, double b) {
        double c = a + (b - a) / 2;
        return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
    }
    double asr(double a, double b, double eps, double A) {
        double c = a + (b - a) / 2;
        double L = simpson(a, c);
        double R = simpson(c, b);
        if (Math.abs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15;
        return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
    }
    double asr(double a, double b, double eps) {
        return asr(a, b, eps, simpson(a, b));
    }
}
