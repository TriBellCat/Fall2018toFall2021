// Phase 3.1: Evaluator for Lexp
//Trinity Caitlin Atayan Belen
//Comp 141: Programming Languages

import java.io.BufferedWriter;
import java.util.*;
import java.io.*;

public class Parser {
	private static Token next_token;
	private static int nextTokenIndex = 0;
	private static ArrayList<Token> tokenList = new ArrayList<Token>();
	private static PTNode parseTree;
	
	
	public static PTNode parser(ArrayList<Token> tokens, BufferedWriter lineWriter) {
		tokenList = tokens;
		next_token = tokenList.get(nextTokenIndex);
		parseTree = parseExpression(lineWriter);
		nextTokenIndex = 0;
		return parseTree;
	}
	
	private static PTNode parseStatement(BufferedWriter lineWriter)
	{
			PTNode tree = parseBase(lineWriter);
			while(next_token.getTokenValue().contains(";")) {
				Token operatorToken = next_token;
				consume_token();
				tree = new PTInteriorNode(operatorToken, tree, parseBase(lineWriter));
			}
			return tree;
	}
		

	private static PTNode parseAssign(BufferedWriter lineWriter) {
		PTNode tree = parseExpression(lineWriter);
		if(next_token.getTokenValue().contains(":=")) {	
			Token n = next_token;
			consume_token();
			tree = new PTInteriorNode(n, tree, parseExpression(lineWriter));
		}
		return tree;
	}

	private static PTNode parseIf(BufferedWriter lineWriter) {
		PTNode tree1 = parseExpression(lineWriter);
		Token i = next_token;
		consume_token();
		
		if(next_token.getTokenValue().contains ("then")) {
			i = next_token;
			consume_token();
			PTNode tree2 = parseStatement(lineWriter);
			if(next_token.getTokenValue().contains ("else")) {
				i = next_token;
				consume_token();
				PTNode tree3 = parseStatement(lineWriter);
				if(next_token.getTokenValue().contains ("endif")) {
					//(Token operator, PTNode left, PTNode middle, PTNode right)
					PTNode tree = new PTInteriorNode(i,tree1,tree2,tree3);
					return tree;
				}
				
				else {
					try { 
						lineWriter.write("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
						System.out.println("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
					}
					catch(IOException e) {
						e.printStackTrace();
					}
					return null;

				}
			}
			
			else {
				try { 
					lineWriter.write("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
					System.out.println("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
				}
				catch(IOException e) {
					e.printStackTrace();
				}
				return null;

			}
		}
		
		else {
			try { 
				lineWriter.write("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
				System.out.println("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
			}
			catch(IOException e) {
				e.printStackTrace();
			}
			return null;

		}	
}


	private static PTNode parseWhile(BufferedWriter lineWriter) {
		Token i = next_token;
		consume_token();
		PTNode tree1 = parseExpression(lineWriter);
		
		if (next_token.getTokenValue().contains("do")) {
			i = next_token;
			consume_token();
			PTNode tree2 = parseStatement(lineWriter);
			if (next_token.getTokenValue().contains("endwhile")) {
				i = next_token;
				consume_token();
				PTNode tree = new PTInteriorNode(i, tree1, tree2);
				return tree;
			}
			else {
				try { 
					lineWriter.write("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
					System.out.println("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
				}
				catch(IOException e) {
					e.printStackTrace();
				}
				return null;

			}
		}
		
		else {
			try { 
				lineWriter.write("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
				System.out.println("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
			}
			catch(IOException e) {
				e.printStackTrace();
			}
			return null;

		}
	}

	private static PTNode parseBase(BufferedWriter lineWriter)
	{
		PTNode tree;
		
		if (next_token.getTokenType().equals(TokenType.IDENTIFIER)) {
			return parseAssign(lineWriter);
		}
		
		else if(next_token.getTokenType().equals(TokenType.KEYWORD)) {
			Token i;
			if (next_token.getTokenValue().contains("if")) 
			{
					return parseIf(lineWriter);
			}
					
			else if (next_token.getTokenValue().contains("while")) {
				return parseWhile(lineWriter);
			}
			else if (next_token.getTokenValue().contains("skip")) {
				i = next_token;
				consume_token();
				return new PTLeafNode(i);
			}
		}
		
		return null;
	}
	
	private static PTNode parseExpression(BufferedWriter lineWriter) {
		PTNode tree = parseTerm(lineWriter);
		while(next_token.getTokenValue().contains("+")) {
			Token operatorToken = next_token;
			consume_token();
			tree = new PTInteriorNode(operatorToken, tree, parseTerm(lineWriter));
		}
		return tree;
	}
	
	
	private static PTNode parseTerm(BufferedWriter lineWriter) {
		PTNode tree = parseFactor(lineWriter);
		while(next_token.getTokenValue().contains("-")) {
			Token operatorToken = next_token;
			consume_token();
			tree = new PTInteriorNode(operatorToken, tree, parseFactor(lineWriter));
		}
		return tree;
	}
	
	
	private static PTNode parseFactor(BufferedWriter lineWriter) {
		PTNode tree = parsePiece(lineWriter);
		while(next_token.getTokenValue().contains("/")) {
			Token operatorToken = next_token;
			consume_token();
			tree = new PTInteriorNode(operatorToken, tree, parsePiece(lineWriter));
		}
		return tree;
	}
	
	
	private static PTNode parsePiece(BufferedWriter lineWriter) {
		PTNode tree = parseElement(lineWriter);
		while(next_token.getTokenValue().contains("*")) {
			Token operatorToken = next_token;
			consume_token();
			tree = new PTInteriorNode(operatorToken, tree, parseElement(lineWriter));
		}
		return tree;
	}
	
	
	private static PTNode parseElement(BufferedWriter lineWriter) {
		PTNode tree;
		if(next_token.getTokenValue().contains("(")) {
			consume_token();
			tree = parseExpression(lineWriter);
			if(next_token.getTokenValue().contains(")")) {
				consume_token();
				return tree;
			}
			else { 
				try {
					lineWriter.write("PARSER ERROR: Expected Right Parenthesis \")\" to close block, but token " + next_token.getTokenValue() + " was encountered instead.\nParser Function has been stopped.\n\n");
					System.out.println("PARSER ERROR: Expected Right Parenthesis \")\" to close block, but token " + next_token.getTokenValue() + " was encountered instead.\nParser Function has been stopped.\n\n");
				}
				catch(IOException e) {
					e.printStackTrace();
				}
				return null;
			}
		}
		else if(next_token.getTokenType().equals(TokenType.NUMBER)) {
			Token n = next_token;
			consume_token();
			return new PTLeafNode(n);
		}
		else if(next_token.getTokenType().equals(TokenType.IDENTIFIER)) {
			Token i = next_token;
			consume_token();
			return new PTLeafNode(i);
		}
		
		/*else if(next_token.getTokenType().equals(TokenType.KEYWORD)) {
			Token j = next_token;
			consume_token();
			return new PTLeafNode(j);
		}*/
		
		else {
			try { 
				lineWriter.write("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
				System.out.println("PARSER ERROR: Invalid token: " + next_token.getTokenValue() + "\nParser Function has been stopped.\n\n");
			}
			catch(IOException e) {
				e.printStackTrace();
			}
			return null;
		}
	}
	
	
	private static void consume_token() {
		nextTokenIndex++;
		if(nextTokenIndex < tokenList.size()) {
			next_token = tokenList.get(nextTokenIndex);
		}
	}
	
	
	public static String traverseParseTree(PTNode tree, String parseString, int level) {
		String exampleString = parseString;
		String tabs = "";
		if(tree != null) {
			for(int i = 0; i < level; i++) {
				tabs += "\t";
			}
			exampleString += tabs + tree.getData().getTokenValue() + " : " + tree.getData().getTokenType().toString() + "\n";
			exampleString += traverseParseTree(tree.getLeftSubTree(), parseString, level + 1);
			exampleString += traverseParseTree(tree.getRightSubTree(), parseString, level + 1);
			return exampleString;
		}
		else {
			return exampleString;
		}
	}
	
	
	public static int size(PTNode tree) {
		int size = 0;
		if(tree != null) {
			return size(tree.getLeftSubTree()) + size(tree.getRightSubTree()) + 1;
		}
		return size;
	}
}
