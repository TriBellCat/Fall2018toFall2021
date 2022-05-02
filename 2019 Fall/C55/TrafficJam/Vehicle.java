public class Vehicle {
	// TODO You'll need to fill in this entire file

	/**
	 * @return the type associated with this particular vehicle
	 */
	
	private VehicleType type; //The vehicle could be an auto, truck, or car
	private Space start; //The starting position of a vehicle
	private int length; //How many spaces the vehicle takes up
	private boolean isVertical; //Checks if the vehicle is vertical
	private int startRow;
	private int startCol;
	
	//Constructor for the Vehicle class
	public Vehicle (VehicleType car, int r, int c, int size, boolean isV) {
		type = car;
		startRow = r;
		startCol = c;
		length = size;
		isVertical = isV;
		start = new Space(r, c);
	}
	
	//Gets the vehicle type
	public VehicleType getVehicleType() {
		// TODO change this implementation so that you return the vehicles
		// actual type, which should be stored in a variable
		// . Right now it only returns the type mycar
		return type;
	}
	
	//Returns true if the vehicle is vertical
	public boolean isVertical () {
		return isVertical;
	}
	
	//Gets the length
	public int getLength() {
		return length;
	}
	
	//Gets the starting position
	public Space getStart () {
		return start;
	}
	
	//Sets the starting row
	public void setStartRow(int newRow) {
		start.setRow(newRow);
	}
	
	//Sets the starting column
	public void setStartCol(int newCol) {
		start.setCol(newCol);
	}
	
	//Updates the vehicle's own start row and column
	public void move (int nSpaces) {
		//If vertical, add in the nSpaces to the row
		//If nSpace were a negative and if i subtract the row or column from it, it's a double negative!
		
		if (this.isVertical()) {
			startRow += nSpaces;
		}
		
		//If horizontal, add in the nSpaces to the column
		else {
			startCol += nSpaces;
		}
	}
	
	//Just returns a new Space with the start and row of 
	//where the vehicle would end up "if it were to move" 
	//Does not update the space too.
	public Space ifIWereToMove (int nSpaces) {
		int tempRow = startRow; //Temporarily stores row
		int tempCol = startCol; //Temporarily stores column
		
		tempRow += (isVertical? nSpaces: 0); //Adds nSpaces to the row if vertical
		tempCol += (isVertical? 0: nSpaces); //Adds nSpaces to the column if horizontal
			
		Space newSpace = new Space(tempRow, tempCol); //sets newSpace with a new row and column
		
		return newSpace; //returns the space
	}
	
	/**
	 * Provides an array of Spaces that indicate where a particular Vehicle
	 * would be located, based on its current starting space
	 * 
	 * @return the array of Spaces occupied by that particular Vehicles
	 */
	public Space[] spacesOccupied() {
		// TODO change this implementation so that you return the correct spaces
		
		Space[] array = new Space[length]; //Initializes an array of Space with length
		int tempRow = startRow; //Stores a temporary row
		int tempCol = startCol; //Stores a temporary column
		
		for (int i = 0; i < length; i++) {
			array[i] = new Space(tempRow, tempCol); //Fills in the row and column into the array
			tempRow += (isVertical? 1: 0); //Changes the row if vertical
			tempCol += (isVertical? 0: 1); //Changes the column if horizontal
		}
		return array; //returns the array
	}

	/**
	 * Calculates an array of the spaces that would be travelled if a vehicle
	 * were to move numSpaces
	 * 
	 * @param numSpaces
	 *            The number of spaces to move (can be negative or positive)
	 * @return The array of Spaces that would need to be checked for Vehicles
	 */
	public Space[] spacesOccupiedOnTrail(int numSpaces) {
		// TODO change this implementation so that you return the correct space
		
		Space[] s = spacesOccupied(); //Initializes a space object to the spacesOccupied function
		Space[] travel = new Space[length + Math.abs(numSpaces)]; //Initializes the array of a space object to be the length plus numSpaces
		int tempRow = startRow; //Stores a temporary row
		int tempCol = startCol; //Stores a temporary column

		if (numSpaces == 0) {
			return s; //If numSpaces is 0, it'll return back the space occupied
		}
		
		if(numSpaces > 0) {
			System.arraycopy(s, 0, travel, 0, length);
			for (int i = length; i < length + Math.abs(numSpaces); i++) {
				tempRow += (isVertical? numSpaces + i: 0); //Adds to tempRow if vertical
				tempCol += (isVertical? 0 : numSpaces + i); //Adds to tempCol if horizontal
				
				travel[i] = new Space(tempRow, tempCol); //Sets the object with a new row and column
				
				tempCol = startCol; //Resets tempCol back
				tempRow = startRow; //Resets tempRow back
			}
			System.arraycopy(s, 0, travel, Math.abs(numSpaces), length);
		}
		
		else {
			System.arraycopy(s, 0, travel, Math.abs(numSpaces), length);
			for (int i = 0; i < Math.abs(numSpaces); i++) {
				tempRow += (isVertical? numSpaces + i: 0); 
				tempCol += (isVertical? 0 : numSpaces + i);
				
				travel[i] = new Space(tempRow, tempCol);
				
				tempCol = startCol;
				tempRow = startRow;
			}
			System.arraycopy(s, 0, travel, Math.abs(numSpaces), length);
		}
		
		return travel;
	}
	
	public static void printSpaces(Space[] arr) {
		for(int i = 0; i < arr.length; i++) {
			System.out.print("r" + arr[i].getRow() + "c" + arr[i].getCol() + "; ");	
		}
		System.out.println();
	}
	
	public static void printSpace(Space s) {
		System.out.println("r" + s.getRow() + "c" + s.getCol() + "; ");
	}
	
	public static void main (String[] args) {
		//this snippet would go inside of a public static void main in Vehicle.java
		//Assume Vehicle constructor is type, startRow, startCol, length, isVertical
		Vehicle someTruck = new Vehicle(VehicleType.TRUCK, 1, 1, 3, true);
		Vehicle someAuto = new Vehicle(VehicleType.AUTO, 2, 2, 2, false);
		System.out.println("This next test is for spacesOccupied: ");
		System.out.println("vert truck at r1c1 should give you r1c1; r2c1; r3c1 as the spaces occupied:does it?");
		printSpaces(someTruck.spacesOccupied());
		System.out.println("horiz auto at r2c2 should give you r2c2; r2c3 as the spaces occupied:does it?");
		printSpaces(someAuto.spacesOccupied());
		System.out.println("if we were to move horiz auto -2 it should give you at least r2c0; r2c1; it may also add r2c2; r2c3 to its answer:does it?");
		printSpaces(someAuto.spacesOccupiedOnTrail(-2));
		//ADD SOME MOVE AND IFIWERETOMOVE TEST CODE BELOW THIS LINE
		System.out.println("vert truck at r1c1 should update to r5c1 and add r6c1; r7c1; if it moves 4 spaces from the right:does it?");
		someTruck.move(4);
		printSpaces(someTruck.spacesOccupied());
		System.out.println("vert truck at r5c1 should show that it gives you r4c1 if it moves 1 space to the left:does it?");
		printSpace(someTruck.ifIWereToMove(-1));
		
		Vehicle testCar = new Vehicle (VehicleType.MYCAR, 1, 0, 2, false);
		
	}
}
