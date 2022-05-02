// Phase 3.1: Evaluator for Lexp
//Trinity Caitlin Atayan Belen
//Comp 141: Programming Languages

import java.io.*;
import java.util.*;
public class testDriver {
	public static void main(String[] args) {
		String userHomeDir = System.getProperty("user.home");
		String inputFile = userHomeDir + "\\downloads\\Valuator\\" + args[0];
		String outputFile = userHomeDir + "\\downloads\\Valuator\\" + args[1];
		
		ArrayList<Token> tokens = new ArrayList<Token>(); 
		ArrayList<Token> foundTokens = new ArrayList<Token>();
		try {
			BufferedReader lineReader = new BufferedReader(new FileReader(inputFile)); 
			BufferedWriter lineWriter = new BufferedWriter(new FileWriter(outputFile));
			
			String inputLine = lineReader.readLine();
			while(inputLine != null) {
				foundTokens = Scanner.scanner(inputLine, outputFile, lineWriter);
				tokens.addAll(foundTokens);
				inputLine = lineReader.readLine();				
			}
			
			System.out.println("Tokens:\n");
			lineWriter.write("Tokens: \n");
			for(Token token: tokens) {
				System.out.println(token.getTokenValue() + "    : " + token.getTokenType() + "\n");
				lineWriter.write(token.getTokenValue() + "    : " + token.getTokenType() + "\n");
			}

			System.out.println("\nAST:\n");
			lineWriter.write("\nAST:\n");
			PTNode parseTree = Parser.parser(tokens, lineWriter);
			String parseResult = Parser.traverseParseTree(parseTree, "", 0);
			System.out.println(parseResult);
			lineWriter.write(parseResult);
		
			int result = Evaluator.evaluator(parseTree, lineWriter);
			if(result >= 0) {
				lineWriter.write("\nResult: " + result + "\n");
			}
			
			lineReader.close(); 
			lineWriter.close();
		}
		catch(IOException e) {
			System.out.println("Error: No file located");
			e.printStackTrace();
		}
	}
}
