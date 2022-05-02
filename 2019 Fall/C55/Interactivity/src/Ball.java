import acm.graphics.*;
import acm.program.*;
import acm.util.*;
import java.awt.*;
import java.awt.event.*;

public class Ball extends GraphicsProgram {
	public static final int WINDOW_WIDTH = 800;
	public static final int WINDOW_HEIGHT = 600;
	public static final int BALL_SIZE = 100;
	public static final int BREAK_MS = 30;
	public static final int INIT_X_VELOCITY = 5;
	
	private GOval ball;
	private int xVelocity;
	private RandomGenerator rgen;
	
	public void run() {
		rgen = RandomGenerator.getInstance();
		xVelocity = INIT_X_VELOCITY;
		
		ball = new GOval(WINDOW_HEIGHT/2-BALL_SIZE/2, WINDOW_WIDTH/2-BALL_SIZE/2, BALL_SIZE, BALL_SIZE);
		ball.setColor(Color.RED);
		ball.setFilled(true);
		add(ball);
		
		addMouseListeners();
		animateBall();
	}
	
	private void animateBall() {
		while(true) {
			ball.move(xVelocity, 0);
			if(outOfBounds()) {
				xVelocity *= -1;
			}
			pause(BREAK_MS);
		}
	}
	
	private boolean outOfBounds() {
		double x = ball.getX();
		return (x < 0 && xVelocity < 0 || x > WINDOW_WIDTH && xVelocity > 0);
	}

	public void init() {
		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		requestFocus();
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		//code to tell the computer what to do when the mouse is pressed
		
		System.out.println("Mouse is being pressed!");
		//Changes the ball color if it's clicked on
		if(getElementAt(e.getX(), e.getY()) == ball) {
			ball.setColor(rgen.nextColor());
			System.out.println("Ball changed colors! Color: " + ball.getColor());
		}
		
		//Otherwise, changes the ball location if it'ss clicked somewhere else
		else {
			ball.setLocation(ball.getX(), e.getY());
			System.out.println("Ball changed location! x: " + e.getX() + ", y: " +e.getY());
		}		
	}
	
	public void mouseReleased(MouseEvent e) {
		System.out.println("The mouse is not being pressed!");
	}
	
	public void mousedClicked(MouseEvent e) {
		System.out.println("The mouse is clicked!");
	}
	
	public void mouseEntered(MouseEvent e) {
		System.out.println("The mouse entered the window!");
	}
	
	public void mouseExited(MouseEvent e) {
		System.out.println("The mouse left the window!");
	}
	
	public void mouseMoved(MouseEvent e) {
		System.out.println("The mouse moved on the screen; no bottons are pressed!");
	}
	
	public void mouseDragged(MouseEvent e) {
		System.out.println("The mouse moved on the screen; bottons are pressed!");
	}
}
