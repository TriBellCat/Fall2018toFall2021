import java.util.*;


public class Level {	
	private Board board;
	private Space winningSpace;
	private int numMoves = 0;
	private ArrayList<Vehicle> vList;
	
	//Gets the number of moves
	public int getNumMoves() {
		return numMoves;
	}
	
	//Increments the number of moves by 1
	public void incrementMoves() {
		numMoves += 1;
	}
	
	public ArrayList<Vehicle> getVehiclesOnBoard() {
		return vList;
	}
	
	//Gets the vehicle from a space
	public Vehicle getVehicle (Space space) {
		return board.getVehicle(space);
	}
	
	//TODO fill out this class with a Level constructor
	//all the other methods necessary and any other instance variables needed
	public Level(int nRows, int nCols) {
		board = new Board(nRows, nCols);
	}
	
	//Sets up the level
	public void setupLevel (int maxRows, int maxCols) {
		winningSpace = new Space(2, 5);
		
		//Adds vehicles based on what the instructions showed
		board.addVehicle(VehicleType.MYCAR, 2, 0, 2, false);
		board.addVehicle(VehicleType.TRUCK, 0, 2, 3, true);
		board.addVehicle(VehicleType.AUTO, 0, 4, 3, true);
		board.addVehicle(VehicleType.AUTO, 0, 5, 3, true);
		board.addVehicle(VehicleType.AUTO, 3, 3, 2, true);
		board.addVehicle(VehicleType.AUTO, 4, 4, 2, false);
		
		vList = board.getVehiclesOnBoard(); //Adds the vehicles to the array list
	}
	
	/**
	 * @return the number of columns on the board
	 */
	public int getColumns() {
		//TODO: have this return the number of columns in the level
		return board.getNumCols();
	}
	
	//Returns the number of rows
	public int getRows() {
		return board.getNumRows();
	}
	
	//Returns the winning space
	public Space getGoalSpace() {
		return winningSpace;
	}
	
	//A boolean function that prints and increments the moves if one of the vehicle moved
	public boolean moveNumSpaces (Space space, int numSpaces) {
		if (board.moveNumSpaces(space, numSpaces)) {
			System.out.println("The vehicle moved!");
			incrementMoves();
			return true;
		}
		System.out.println("The vehicle did not move!");
		return false;
	}
	
	//A boolean function that returns true if the vehicle on space is on the winning space
	public boolean passedLevel() {
		if(board.isVehicleOnSpace(winningSpace)) {
			if(board.getVehicle(winningSpace).getVehicleType() == VehicleType.MYCAR) {
				return true;
			}
		}
		return false;
	}
	//Methods already defined for you
	/**
	 * generates the string representation of the level, including the row and column headers to make it look like
	 * a table
	 * 
	 * @return the string representation
	 */
	public String toString() {
		String result = generateColHeader(getColumns());
		result+=addRowHeader(board.toString());
		return result;
	}
	
	/**
	 * This method will add the row information
	 * needed to the board and is used by the toString method
	 * 
	 * @param origBoard the original board without the header information
	 * @return the board with the header information
	 */
	private String addRowHeader(String origBoard) {
		String result = "";
		String[] elems = origBoard.split("\n");
		for(int i = 0; i < elems.length; i++) {
			result += (char)('A' + i) + "|" + elems[i] + "\n"; 
		}
		return result;
	}
	
	/**
	 * This one is responsible for making the row of column numbers at the top and is used by the toString method
	 * 
	 * @param cols the number of columns in the board
	 * @return if the # of columns is five then it would return "12345\n-----\n"
	 */
	private String generateColHeader(int cols) {
		String result = "  ";
		for(int i = 1; i <= cols; i++) {
			result+=i;
		}
		result+="\n  ";
		for(int i = 0; i < cols; i++) {
			result+="-";
		}
		result+="\n";
		return result;
	}
}
