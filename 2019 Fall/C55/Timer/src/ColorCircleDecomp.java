import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Timer;

import acm.graphics.*;
import acm.program.*;

public class ColorCircleDecomp extends GraphicsProgram implements ActionListener {
	public static final int PROGRAM_WIDTH = 800;
	public static final int PROGRAM_HEIGHT = 600;
	public static final int BALL_SIZE = 50;
	public static final int DELAY_MS = 25;
	
	//TODO create a private GOval here
	private GOval ball;
	private Color color;
	private int angle = 0;
	private int colorS = 0;
	public void run() {
		//TODO add your ball here
		
		ball = new GOval(770, 750, BALL_SIZE, BALL_SIZE);
		add(ball);
		Timer t = new Timer(DELAY_MS, this);
		t.start();
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		Color color = new Color (45,0, 0);
		ball.movePolar(10,angle);
		//ball.setColor(color);
		
		
		System.out.println(Math.abs(3- colorS % 6) % 6);
		ball.setFilled(true);
		colorS = (colorS + 1) % 511;
		angle = (angle + 2) % 360;
	}

	public void init() {
		setSize(PROGRAM_WIDTH, PROGRAM_HEIGHT);
	}
	
}
