import java.awt.*;
import java.awt.event.MouseEvent;
import java.util.*;

import acm.program.*;
import acm.graphics.*;

public class GraphicsGame extends GraphicsProgram {
	/**
	 * Here are all of the constants
	 */
	public static final int PROGRAM_WIDTH = 500;
	public static final int PROGRAM_HEIGHT = 500;
	public static final String lABEL_FONT = "Arial-Bold-22";
	public static final String EXIT_SIGN = "EXIT";
	public static final String IMG_FILENAME_PATH = "images/";
	public static final String IMG_EXTENSION = ".png";
	public static final String VERTICAL_IMG_FILENAME = "_vert";

	// TODO declare your instance variables here
	private Level level; //The level that's going to have vehicles in it later
	public static final int NUM_ROWS = 6; //The number of rows 
	public static final int NUM_COLS = 6; //The number of columns
	private ArrayList <Vehicle> vList; //Vehicle array list
	
	private GObject drag; //Object that's going to be dragged later
	private int sX; //start x
	private int sY; //start y
	private int lX; //last x
	private int lY; //last y
	
	public void init() {
		setSize(PROGRAM_WIDTH, PROGRAM_HEIGHT);
	}

	public void run() {
		// TODO write this part, which is like your main function
		level=new Level(NUM_ROWS,NUM_COLS);
		level.setupLevel(NUM_ROWS, NUM_COLS);
		drawLevel();
		addMouseListeners();
	}

	private void drawLevel() {
		// TODO write the code to draw the entire level, which should
		// mostly be calls to some of your helper functions.
		drawGridLines(); 
		drawCars();
		drawWinningTile();
		drawCounter();
	}

	/**
	 * This should draw the label EXIT and add it to the space that represents
	 * the winning tile.
	 */
	private void drawWinningTile() {
		Space winS = level.getGoalSpace();
		System.out.println("The winning space is at r" + winS.getRow() + "c" + winS.getCol());
		int y = winS.getRow();
		int x = winS.getCol();
		
		double winY = spaceHeight() * y + 20;
		double winX = spaceWidth() * x;
		
		System.out.println("The coordinates of the winning space is at x: " + winX + ", y: " + winY);
	
		GLabel winT = new GLabel(EXIT_SIGN, winX, winY);
		winT.setFont(lABEL_FONT);
		winT.setColor(Color.RED);
		add(winT);
	}
	
	/**
	 * draw the lines of the grid. Test this out and make sure you have it
	 * working first. Should draw the number of grids based on the number of
	 * rows and columns in Level
	 */
	private void drawGridLines() {
		System.out.println("The column width is set to: " + spaceWidth());
		System.out.println("The row height is set to: " + spaceHeight());
		
		for(int x = 1; x < level.getColumns(); x++) {
			GLine width = new GLine(x*spaceWidth(), 0, x*spaceWidth(), PROGRAM_HEIGHT);
			add(width);
		}
		
		for(int y = 1; y < level.getRows(); y++) {
			GLine height = new GLine(0, y*spaceHeight(), PROGRAM_WIDTH, y*spaceHeight());
			add(height);
		}
	}
	
	//Draws the counter of the number of moves
	private void drawCounter () {
		GLabel counter = new GLabel("" + level.getNumMoves(), 0, 20);
		counter.setFont("Arial-Bold-25");
		counter.setColor(Color.BLACK);
		add(counter);
	}
	
	/**
	 * Maybe given a list of all the cars, you can go through them and call
	 * drawCar on each?
	 */
	private void drawCars() {
		vList = level.getVehiclesOnBoard();
		for (int x = 0; x < vList.size(); x++) {
			drawCar(vList.get(x));
		}
	}

	/**
	 * Given a vehicle object, which we will call v, use the information from
	 * that vehicle to then create a GImage and add it to the screen. Make sure
	 * to use the constants for the image path ("/images"), the extension ".png"
	 * and the additional suffix to the filename if the object is vertical when
	 * creating your GImage. Also make sure to set the images size according to
	 * the size of your spaces
	 * 
	 * @param v
	 *            the Vehicle object to be drawn
	 */
	private void drawCar(Vehicle v) {
		// TODO implement drawCar
		GImage c; //the car
		
		double x = v.getStart().getCol()*spaceWidth(); //Gets the x
		double y = v.getStart().getRow()*spaceHeight(); //Gets the y
		System.out.println("Drawing vehicle at coordinates: x" + x + "y" + y); //Prints out the coordinates vehicle is on
		
		double w; //weight
		double h; //height
		
		String file = IMG_FILENAME_PATH + v.getVehicleType().toString(); //The image file path
		
		if (v.isVertical()) {
			file += VERTICAL_IMG_FILENAME;
			w = spaceWidth();
			h = spaceHeight() * v.getLength();
		}
		
		else {
			w = spaceWidth() * v.getLength(); 
			h = spaceHeight();
		}
		
		file += IMG_EXTENSION; 
		c = new GImage(file, x, y); //Sets the car with image and coordinates
		c.setSize(w, h); //Also sets the car to the size width by height
		add(c); //Draws the car
	}

	// TODO implement the mouse listeners here
	@Override
	public void mousePressed(MouseEvent e) {
		drag = getElementAt(e.getX(), e.getY());
		
		convertXYToSpace(e.getX(), e.getY());
		
		sX = e.getX();
		sY = e.getY();
		lX = e.getX();
		lY = e.getY();
		
		if (drag!=null) {
			System.out.println("Vehicle is clicked on!");
		}
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		
		if (drag != null) {
			drag.move(e.getX() - lX, e.getY() - lY);
		}
		
		lX = e.getX();
		lY = e.getY();
	}
	
	@Override
	public void mouseReleased(MouseEvent e) {
		System.out.println("start: x" + sX + "y" + sY); //Prints the start coordinates
		System.out.println("last: x" + lX + "y" + lY); //Prints the last coordinates
		Space s = convertXYToSpace(sX, sY); //Space converts the start coordinates
		
		System.out.println("r"+s.getRow()+"c"+s.getCol()); //Prints the row and column
		
		//Screen if the vehicle isn't at winning space
		if (getVehicleFromXY(sX, sY) !=null) {
			level.moveNumSpaces(s, calculateSpacesMoved()); 
			removeAll(); 
			drawLevel();
		}
		
		//Winning Screen
		if (level.passedLevel()) {
			removeAll();//Removes everything to make way of the winning screen
			GLabel winner = new GLabel("You completed the level!", 220, 250);
			winner.setFont("Arial-Bold-50");
			winner.setColor(Color.BLACK);
			add(winner);
		}	
	}
	
	/**
	 * Given a xy coordinates, return the Vehicle that is currently at those x
	 * and y coordinates, returning null if no Vehicle currently sits at those
	 * coordinates.
	 * 
	 * @param x
	 *            the x coordinate in pixels
	 * @param y
	 *            the y coordinate in pixels
	 * @return the Vehicle object that currently sits at that xy location
	 */
	private Vehicle getVehicleFromXY(double x, double y) {
		// TODO fix this implementation
		Space s = convertXYToSpace(x, y); //Converts x and y to column and row
		return level.getVehicle(s); //Then returns the vehicle at that location
	}

	/**
	 * This is a useful helper function to help you calculate the number of
	 * spaces that a vehicle moved while dragging so that you can then send that
	 * information over as numSpacesMoved to that particular Vehicle object.
	 * 
	 * @return the number of spaces that were moved
	 */
	private int calculateSpacesMoved() {
		Space s = convertXYToSpace(sX, sY); //The start space
		Space l = convertXYToSpace (lX, lY); //The last space
		Vehicle v = getVehicleFromXY(sX, sY); //The vehicle at the start coordinates
		
		if (v != null) {
			if (v.isVertical()) {
				return l.getRow() - s.getRow(); 
			}
			else {
				return l.getCol() - s.getCol();
			}
		}
		
		else {
			return 0;
		}
	}

	/**
	 * Another helper function/method meant to return the space given an x and y
	 * coordinate system. Use this to help you write getVehicleFromXY
	 * 
	 * @param x
	 *            x-coordinate (in pixels)
	 * @param y
	 *            y-coordinate (in pixels)
	 * @return the Space associated with that x and y
	 */
	private Space convertXYToSpace(double x, double y) {
		// TODO write this implementation hint (use helper methods below)
		int conRow = (int)(y/spaceHeight()); //Converts the y coordinate to the row
		int conCol = (int)(x/spaceWidth()); //Converts the x coordinate to the column
		
		System.out.println("The XY(" + x + "," + y + ") coordinates respectively converts to r" + conRow + "c" + conCol);
		
		Space con = new Space(conRow,conCol); //The new Space with the conversion
		return con; //returns the conversion
	}

	/**
	 * 
	 * @return the width (in pixels) of a single space in the grid
	 */
	private double spaceWidth() {
		// TODO fix this method
		return (PROGRAM_WIDTH/level.getColumns());
	}

	/**
	 * 
	 * @return the height in pixels of a single space in the grid
	 */
	private double spaceHeight() {
		// TODO fix this method
		return (PROGRAM_HEIGHT/level.getRows());
	}
}
