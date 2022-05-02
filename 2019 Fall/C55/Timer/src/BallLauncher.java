import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import javax.swing.*;

import acm.graphics.*;
import acm.program.*;

public class BallLauncher extends GraphicsProgram {
	public static final int SIZE = 25;
	public static final int STORE = 50;
	public static final int MOVE = 2;
	private ArrayList <GOval> balls;
	private Timer time;
	
	public void run() {
		balls = new ArrayList<GOval>();
		time = new Timer (STORE, this);
		time.start();
		addMouseListeners();
	}
	
	public void mousePressed(MouseEvent e) {
		for (GOval check:balls) {
			if (check.getX() < 100) {
				return;
			}
		}
		
		GOval ball = makeBall(SIZE/2, e.getY());
		add(ball);
		balls.add(ball);
	}
	
	public GOval makeBall(double x, double y) {
		GOval temp = new GOval(x-SIZE/2, y-SIZE/2, SIZE, SIZE);
		temp.setColor(Color.RED);
		temp.setFilled(true);
		return temp;
	}
	
	public void actionPerformed(ActionEvent e) {
		  for (GOval temp:balls) {
			  temp.move(MOVE, 0);
		  }
	}

}
