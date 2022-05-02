// Phase 3.1: Evaluator for Lexp
//Trinity Caitlin Atayan Belen
//Comp 141: Programming Languages

import java.util.*;
import java.io.*;

public class Scanner {
	public static ArrayList<Token> scanner(String inputLine, String outputFile, BufferedWriter lineWriter) {
		ArrayList<Token> tokens = new ArrayList<Token>(); 
		char[] inputLineChars = inputLine.toCharArray(); 
		int startCharIndex = 0;	
		int endCharIndex = 0; 
		int currentIndex = 0; 
		String tokenString;
		
		while(currentIndex < inputLineChars.length) {
			char startChar = inputLineChars[currentIndex];
			startCharIndex = currentIndex;
			endCharIndex = currentIndex;
			
			if(Character.isLetter(startChar)) { 
				currentIndex++;
				
				while(currentIndex < inputLineChars.length) { 
					if(Character.isLetterOrDigit(inputLineChars[currentIndex])) {
						endCharIndex = currentIndex;
						currentIndex++;
					}
					else {
						break;
					}
				}
				
				tokenString = new String(makeTokenString(inputLineChars, startCharIndex, endCharIndex)); 
				if(isAKeyword(tokenString)) { 
					Token keyWordToken = new Token();
					keyWordToken.setTokenType(TokenType.KEYWORD);
					keyWordToken.setTokenValue(tokenString);
					tokens.add(keyWordToken);
				}
				else { 
					Token identifierToken = new Token();
					identifierToken.setTokenType(TokenType.IDENTIFIER);
					identifierToken.setTokenValue(tokenString);
					tokens.add(identifierToken);
				}
			}
			else if(Character.isDigit(startChar)) {
				currentIndex++;
				
				while(currentIndex < inputLineChars.length) {
					if(Character.isDigit(inputLineChars[currentIndex])) {
						endCharIndex = currentIndex;
						currentIndex++;
					}
					else {
						break;
					}
				}
				
				tokenString = new String(makeTokenString(inputLineChars, startCharIndex, endCharIndex)); 
				Token numberToken = new Token();
				numberToken.setTokenType(TokenType.NUMBER);
				numberToken.setTokenValue(tokenString);
				tokens.add(numberToken);
			}
			else if(startChar == '+' || startChar == '-' || startChar == '*' || startChar == '/' || startChar == '(' || startChar == ')' || startChar == ':' || startChar == ';') { //These characters are stated as punctuation tokens and simply just adds them since all these tokens are only one character
				currentIndex++;
				if(startChar == ':' && inputLineChars[currentIndex] == '=') { 
					endCharIndex = currentIndex;
					currentIndex++;
				}
				tokenString = new String(makeTokenString(inputLineChars, startCharIndex, endCharIndex));
				Token punctuationToken = new Token();
				punctuationToken.setTokenType(TokenType.PUNCTUATION);
				punctuationToken.setTokenValue(tokenString);
				tokens.add(punctuationToken);
			}
			else if (Character.isWhitespace(startChar)) { 
				currentIndex++;
				startCharIndex = currentIndex;
				endCharIndex = currentIndex;
			}
			else { 
				try {
					System.out.println("ERROR: Unrecognized Character \"" + startChar + "\" on Line: " + inputLine +"\nScanner Function has been stopped.\n");
					lineWriter.write("ERROR: Unrecognized Character \"" + startChar + "\" on Line: " + inputLine +"\nScanner Function has been stopped.\n");
				}
				catch(IOException e) {
					e.printStackTrace();
				}

				return null;
			}
		}
		
		return tokens;
	}
	
	private static String makeTokenString(char[] inputLine, int startIndex, int endIndex) {
		return new String(Arrays.copyOfRange(inputLine,  startIndex, endIndex + 1));
	}
	
	public static Boolean isAKeyword(String s) {
		return (s.equals("if") || s.equals("then") || s.equals("else") || s.equals("endif") || s.equals("while") || s.equals("do") || s.equals("endwhile") || s.equals("skip"));
	}
}
