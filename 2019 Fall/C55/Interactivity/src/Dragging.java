import acm.graphics.*;
import acm.program.*;
import acm.util.*;
import java.awt.*;
import java.awt.event.*;

public class Dragging extends GraphicsProgram {
	public static final int WINDOW_WIDTH = 800;
	public static final int WINDOW_HEIGHT = 600;
	public static final int SHAPE_SIZE = 300;
	
	private GObject toDrag;
	private double lastX;
	private double lastY;
	
	public void run() {
		GOval oval = new GOval(100, 100, SHAPE_SIZE, SHAPE_SIZE);
		oval.setColor(Color.blue);
		oval.setFilled(true);
		add(oval);
		
		GRect rect = new GRect(500, 500, SHAPE_SIZE, SHAPE_SIZE);
		rect.setColor(Color.green);
		rect.setFilled(true);
		add(rect);
		
		addMouseListeners();
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		toDrag = getElementAt(e.getX(), e.getY());
		lastX = e.getX();
		lastY = e.getY();
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		if (lastX != e.getX() & lastY != e.getY() && toDrag != null) {
			double distanceX = lastX - e.getX();
			double distanceY = lastY - e.getY();
			toDrag.setLocation(e.getX() - SHAPE_SIZE/2, e.getY() - SHAPE_SIZE/2);
			
			System.out.println("A shape is being dragged from r" + lastX + "c" + lastY + " to r" + e.getX() + "c" + e.getY() + "!");	
			
			if (lastX > e.getX()) {
				System.out.println("The shape moved to the left in " + distanceX + " distance");
			}
			
			else if (lastX < e.getX()) {
				System.out.println("The shape moved to the right in " + distanceX + " distance");
			}
			
			if (lastY < e.getY()) {
				System.out.println("The shape moved down in " + distanceY + " distance");
			}
			
			else if (lastY > e.getY()) {
				System.out.println("The shape moved up in " + distanceY + " distance");
			}
			lastX = e.getX();
			lastY = e.getY();
		}
	}
	
	@Override
	public void mouseReleased(MouseEvent e) {
		System.out.println("The mouse is released!");
	}
	
	public void init() {
		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		requestFocus();
	}
}
