import java.util.*;

public class TestFraction {

	public static void main(String[] args) {
		
		System.out.println("Student - Trinity Caitlin Atayan Belen");
		System.out.println("Testing my Fraction class...");
		System.out.println("Currently: ");
		
		//I want to be able to create a 3/4 fraction...like this
		Fraction f = new Fraction(3, 4);
		
		System.out.println("3/4 should appear below.");
		System.out.println(f);
		
		System.out.println("Now, I want to change the f to be 1/2 instead.");
		//I want to be able to set the numerator, like so
		f.setNumerator(1);
		//setDenominator should work the same
		f.setDenominator(2);
		//TODO: change the denominator to 1
		
		//I should be able to change the numerator
		System.out.println("This numerator should be 1 now, right? " + f.getNumerator());
		//Same with Denominator
		System.out.println("This denominator should be 2 now, right? " + f.getDenominator());
		//More advanced
		System.out.println("I will try to set the denominator to zero, which the program should ignore.");
		f.setDenominator(0);
		//At this point the fraction should print out "1/2"
		System.out.println("Right now, the fraction should print out 1/2 here.  " + f);
	}

}
