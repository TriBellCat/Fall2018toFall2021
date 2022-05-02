
public class SimplifiedFraction {
	private int numerator;
	private int denominator;

	public SimplifiedFraction(int n, int d) {
		numerator = n;
		denominator = d;
		simplify(numerator, denominator);
	}

	public void setNumerator(int n) {
		simplify(n, denominator);
	}

	public void setDenominator(int d) {
		simplify(numerator, d);
	}

	public double toDecimal() {
		return numerator / denominator;
	}

	private void simplify(int numerator, int denominator) {
		int gcd = gcd(numerator, denominator);
		numerator = numerator / gcd;
		denominator = denominator / gcd;
	}

	private int gcd(int n1, int n2) {
		int upperlimit = Math.min(n1, n2);
		int gcd = 1;
		for (int divisor = 2; divisor <= upperlimit; divisor++) {
			if (n1 % divisor == 0 && n2 % divisor == 0) {
				gcd = divisor;
			}
		}
		return gcd;
	}

	public String toString() {
		return numerator + "/" + denominator;
	}

	public static void main(String[] args) {
		SimplifiedFraction f = new SimplifiedFraction(10, 12);
		System.out.println(f);
	}
}
