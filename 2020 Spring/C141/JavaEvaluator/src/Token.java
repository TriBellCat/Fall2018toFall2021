// Phase 3.1: Evaluator for Lexp
//Trinity Caitlin Atayan Belen
//Comp 141: Programming Languages

public class Token {
	private TokenType tokenType = null;
	private String tokenValue = "";
	

	public void setTokenType(TokenType type) {
		tokenType = type;
	}
	
	public void setTokenValue(String value) {
		if(value.equals("")) {
			System.out.println("ERROR: Token is not valid.");
			return;
		}
		tokenValue = value;
	}
	
	public TokenType getTokenType() {
		return tokenType;
	}
	
	public String getTokenValue() {
		return tokenValue;
	}
}
