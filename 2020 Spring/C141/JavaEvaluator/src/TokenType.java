// Phase 3.1: Evaluator for Lexp
//Trinity Caitlin Atayan Belen
//Comp 141: Programming Languages

public enum TokenType {
	IDENTIFIER, NUMBER, PUNCTUATION, KEYWORD;
	
	public String toString() {
		switch(this) {
		case IDENTIFIER: return "IDENTIFIER";
		case NUMBER: return "NUMBER";
		case PUNCTUATION: return "PUNCTUATION";
		case KEYWORD: return "KEYWORD";
		}
		return "N/A";
	}
}
