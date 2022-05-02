// Phase 3.1: Evaluator for Lexp
//Trinity Caitlin Atayan Belen
//Comp 141: Programming Languages

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Evaluator {
	private static int result = 0;
	private static PTNode originalParseTree;
	private static ArrayList<Token> stack = new ArrayList<Token>();
	private static Token stackFirst;
	private static Token stackSecond;
	private static Token stackThird;
	private static boolean ranIntoError = false;
	public static int evaluator(PTNode pTree, BufferedWriter lineWriter) {
		originalParseTree = pTree;
		result = evaluateExpression(originalParseTree, lineWriter);
		if(ranIntoError) {
			return -1;
		}
		System.out.println("Stack: ");
		for(int i = stack.size() - 1; i >= 0; i--) {
			System.out.println(stack.get(i).getTokenValue());
		}
		return result;
	}
	
	public static int evaluateExpression(PTNode pTree, BufferedWriter lineWriter) {
		int subResult = 0;
		if(pTree != null) {
			stack.add(pTree.getData());
			while(shouldDoMath()) {
				int evaluatedResult = calculate(lineWriter);
				if(ranIntoError) {
					break;
				}
				Token resultToken = new Token();
				resultToken.setTokenType(TokenType.NUMBER);
				resultToken.setTokenValue(String.valueOf(evaluatedResult));
				stack.remove(stackFirst);
				stack.remove(stackSecond);
				stack.remove(stackThird);
				stack.add(resultToken);
			}
			evaluateExpression(pTree.getLeftSubTree(), lineWriter);
			evaluateExpression(pTree.getRightSubTree(), lineWriter);
			if(stack.size() == 1) {
				subResult = Integer.parseInt(stack.get(0).getTokenValue());
			}
		}
		return subResult;
	}
	
	private static int calculate(BufferedWriter lineWriter) {
		int firstNum = Integer.parseInt(stackFirst.getTokenValue());
		int secondNum = Integer.parseInt(stackSecond.getTokenValue());
		int result = -1;
		switch(stackThird.getTokenValue()) {
		case "+":
			result = secondNum + firstNum;
			break;
		case "-":
			result = secondNum - firstNum;
			if(result < 0) {
				result = 0;
			}
			break;
		case "/":
			if(firstNum == 0) {
				System.out.println("ERROR: Cannot divide by zero.");
				try {
					lineWriter.write("\nEVALUATOR ERROR: trying to do " + secondNum + " / " + firstNum + "\n");
					lineWriter.write("Cannot divide by zero!\n");
				} catch(IOException e) {
					e.printStackTrace();
				}
				
				ranIntoError = true;
				break;
			}
			result = secondNum / firstNum;
			break;
		case "*":
			result = secondNum * firstNum;
			break;
		default:
		}
		System.out.println("Result of calculation: " + result);
		return result;
	}
	
	private static boolean shouldDoMath() {
		if(stack.size() >= 3) {
			stackFirst = stack.get(stack.size() - 1);
			stackSecond = stack.get(stack.size() - 2);
			stackThird = stack.get(stack.size() - 3);
			if(stackFirst.getTokenType() == TokenType.NUMBER && stackSecond.getTokenType() == TokenType.NUMBER && stackThird.getTokenType() == TokenType.PUNCTUATION) {
				return true;
			}
		}
		return false;
	}
}
