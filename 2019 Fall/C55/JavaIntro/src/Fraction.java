
public class Fraction {
	private int numerator;
	private int denominator;
	
	public Fraction(int num, int den) {
		numerator = num;
		denominator = den;
	}

	public int getNumerator() {
		return numerator;
	}

	public int getDenominator() {
		return denominator;
	}

	public void setNumerator(int numerator) {
		this.numerator = numerator;
	}

	public void setDenominator(int denominator) {
		//Only let numbers that are not 0 to be set as the denominator
		if (denominator != 0) { 
			this.denominator = denominator;
		}
	}

	@Override
	public String toString() {
		return numerator + "/" + denominator;
	}

}
