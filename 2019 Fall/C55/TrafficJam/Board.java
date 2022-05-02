import java.util.*;

/**
 * This represents the board.  Really what it is going to do is just have a 2d array of the vehicles
 * (which we'll refer to as grid), and it will be in charge of doing the bounds type checking for doing any of the moves.
 * It will also have a method display board which will give back a string representation of the board
 * 
 * @author Osvaldo
 *
 */

public class Board {
	Vehicle[][] grid; //The board
	int numRows; //The number of rows on the board
	int numCols; //The number of columns on the board
	private ArrayList<Vehicle> vList = new ArrayList<Vehicle>(); //2D array list to store vehicles
	
	//TODO Add the other methods that are in the handout, and fill out the rest of this file
	
	/**
	 * Constructor for the board which sets up an empty grid of size rows by columns
	 * Use the first array index as the rows and the second index as the columns
	 * 
	 * @param rows number of rows on the board
	 * @param cols number of columns on the board
	 */
	public Board(int rows, int cols) {
		//TODO finish implementing this constructor
		numRows = rows;
		numCols = cols;
		grid = new Vehicle [rows][cols];
	}
	
	/*Returns the list*/
	public ArrayList<Vehicle> getVehiclesOnBoard() {
		return vList;
	}
	
	/**
	 * @return number of columns the board has
	 */
	public int getNumCols() {
		//TODO change this method, which should return the number of columns the grid has
		return numCols;
	}

	/**
	 * @return number of rows the board has
	 */
	public int getNumRows() {
		//TODO change this method, which should return the number of rows the grid has
		return numRows;
	}
	
	/*Checks if the vehicle is space*/
	public boolean isVehicleOnSpace (Space s) {
		
		if (grid[s.getRow()][s.getCol()] == null) {
			return false; 
		}
		
		return true;
	}
	
	/**
	 * Grabs the vehicle present on a particular space if any is there
	 * If a Vehicle occupies three spaces, the same Vehicle pointer should be returned for all three spaces
	 * 
	 * @param s the desired space where you want to look to see if a vehicle is there
	 * @return a pointer to the Vehicle object present on that space, if no Vehicle is present, null is returned
	 */
	public Vehicle getVehicle(Space s) {
		//TODO change this method
		
		if (s == null) {
			return null;
		}
		
		else {
			return grid[s.getRow()][s.getCol()];
		}
	}

	/**
	 * adds a vehicle to the board. It would be good to do some checks for a legal placement here.
	 * 
	 * @param type type of the vehicle
	 * @param startRow row for location of vehicle's top
	 * @param startCol column for for location of vehicle leftmost space
	 * @param length number of spaces the vehicle occupies on the board
	 * @param vert true if the vehicle should be vertical
	 */
	public void addVehicle(VehicleType type, int startRow, int startCol, int length, boolean vert) {
		//TODO implement this method, which should addAVehicle to the grid
		Vehicle v = new Vehicle (type, startRow, startCol, length, vert); //Creates a new object and then initializes it to be a new Vehicle
		Space[] s = v.spacesOccupied(); //Creates a new storage for space
		
		for (int i = 0; i < s.length; i++) {
			grid[s[i].getRow()][s[i].getCol()] = v;
		}
		
		vList.add(v); //Adds vehicle to the 2d array list
	}

	/**
	 * This method moves the vehicle on a certain row/column a specific number of spaces
	 * 
	 * @param start the starting row/column of the vehicle in question
	 * @param numSpaces the number of spaces to be moved by the vehicle (can be positive or negative)
	 * @return whether or not the move actually happened
	 */
	public boolean moveNumSpaces(Space start, int numSpaces) {
		//TODO change this method to implementing moving a vehicle that is on a certain row/column a certain number of spaces
		Vehicle v = getVehicle(start);
		
		if (v == null) {
			return false;
		}
		
		Space[] s = v.spacesOccupied();
		
		if(canMoveNumSpaces(start, numSpaces)) {
			vList.remove(v);
			for (int i = 0; i < s.length; i++) {
				grid[s[i].getRow()][s[i].getCol()] = null;
			}
			
			start = v.ifIWereToMove(numSpaces);
			
			addVehicle(v.getVehicleType(), start.getRow(), start.getCol(), v.getLength(), v.isVertical());
			return true;
		}
		return false;
	}
	
	/**
	 * This method just checks to see if the vehicle on a certain row/column can move a specific number of spaces, though
	 * it will not move the vehicle.  You should use this when you wish to move or want to see if you can
	 * move a vehicle numSpaces without going out of bounds or hitting another vehicle
	 * 
	 * @param start the starting row/column of the vehicle in question
	 * @param numSpaces number of spaces to be moved by the vehicle (positive or negative)
	 * @return whether or not the move is possible
	 */
	public boolean canMoveNumSpaces(Space start, int numSpaces) {
		Vehicle v = getVehicle(start);

		if (v == null) {
			return false; //If no vehicle at space, it returns false
		}
		
		Space[] s = v.spacesOccupiedOnTrail(numSpaces);
		
		for (int i = 0; i < s.length; i++) {
			if (s[i].getRow() < 0||s[i].getCol() < 0||s[i].getRow() >= getNumRows()||s[i].getCol() >= getNumRows()) {
				return false; //returns false if any of the spaces are outside the grid
			}
			
			if (grid[s[i].getRow()][s[i].getCol()] != null && grid[s[i].getRow()][s[i].getCol()] != v) {
				return false; //returns false if trail contains other vehicles
			}
		}
		return true;
	}
	
	// This method helps create a string version of the board
	// You do not need to call this at all, just let it be
	public String toString() {
		return BoardConverter.createString(this);
	}
	
	/* Testing methods down here for testing the board 
	 * make sure you run the board and it works before you write the rest of the program! */
	
	public static void main(String[] args) {
		Board b = new Board(5, 5);
		b.addVehicle(VehicleType.MYCAR, 1, 0, 2, false);
		b.addVehicle(VehicleType.TRUCK, 0, 2, 3, true);
		b.addVehicle(VehicleType.AUTO, 3, 3, 2, true);
		b.addVehicle(VehicleType.AUTO, 0, 3, 2, true);
		System.out.println(b);
		testCanMove(b);
		testMoving(b);
		System.out.println(b);
	}
	
	public static void testMoving(Board b) {
		System.out.println("just moving some stuff around");
		b.moveNumSpaces(new Space(1, 2), 1);
		b.moveNumSpaces(new Space(1, 2), 1);
		b.moveNumSpaces(new Space(1, 1), 1);
	}
	
	public static void testCanMove(Board b) {
		System.out.println("Ok, now testing some moves...");
		System.out.println("These should all be true");
		System.out.println("Moving truck down " + b.canMoveNumSpaces(new Space(0, 2), 2));
		System.out.println("Moving truck down " + b.canMoveNumSpaces(new Space(1, 2), 2));
		System.out.println("Moving truck down " + b.canMoveNumSpaces(new Space(2, 2), 2));
		System.out.println("Moving lower auto up " + b.canMoveNumSpaces(new Space(3, 3), -1));
		System.out.println("Moving lower auto up " + b.canMoveNumSpaces(new Space(4, 3), -1));
		
		System.out.println("And these should all be false");
		System.out.println("Moving truck down " + b.canMoveNumSpaces(new Space(3, 2), 2));
		System.out.println("Moving the car into truck" + b.canMoveNumSpaces(new Space(1, 0), 1));
		System.out.println("Moving the car into truck" + b.canMoveNumSpaces(new Space(1, 0), 2));
		System.out.println("Moving nothing at all" + b.canMoveNumSpaces(new Space(4, 4), -1));
		System.out.println("Moving lower auto up " + b.canMoveNumSpaces(new Space(3, 3), -2));
		System.out.println("Moving lower auto up " + b.canMoveNumSpaces(new Space(4, 3), -2));
		System.out.println("Moving upper auto up " + b.canMoveNumSpaces(new Space(0, 3), -1));
		System.out.println("Moving upper auto up " + b.canMoveNumSpaces(new Space(1, 3), -1));
	}
}
