
double myPow(double x, int n) {
    if (n == 0 || x == 1) {
        return 1;
    } else if (x == 0) {
        return 0;
    } else if (n < 0) {
        if (n == INT_MIN) {
            return 1 / (myPow(x, -(n + 1)) * x);
        } else {
            return 1 / myPow(x, -n);
        }
    } else {
        if (n == 1) {
            return x;
        } else if (n % 2 == 0) {
            double result = myPow(x, n >> 1);
            return result * result;
        } else {
            double result = myPow(x, n >> 1);
            return result * result * x;
        }
    }
}