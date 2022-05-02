/**
 * Simple class that represents a row and a column, with simple getters and setters for both
 * @author Osvaldo
 */

public class Space {
	//TODO Put your instance variables here
	private int mainRow;
	private int mainCol;
	
	/**
	 * The constructor that will set up the object to store a row and column
	 * 
	 * @param row
	 * @param col
	 */
	
	public Space(int row, int col) {
		//TODO: this is the constructor, you'll need to fill this in
		mainRow = row;
		mainCol = col;
	}
	
	public int getRow() {
		//TODO fill in this getter
		return mainRow;
	}
	
	public void setRow(int mainRow) {
		this.mainRow = mainRow;
	}
	
	public int getCol() {
		//TODO fill this in
		return mainCol;
	}

	public void setCol(int mainCol) {
		this.mainCol = mainCol;
	}
	
	@Override
	public String toString() {
		return "R" + mainRow + ", C" + mainCol;
	}

	//Sample code to tests if my space class works.
	public static void main(String[] args) {
		Space one = new Space(3, 4);
		Space two = new Space(1, 6);
		two.setRow(two.getRow()+1);
		two.setCol(two.getCol()-1);
		System.out.println("one r: " + one.getRow() + ", c: " + one.getCol());
		System.out.println("two r: " + two.getRow() + ", c: " + two.getCol());
	}


}
