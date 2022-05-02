import acm.graphics.*;
import acm.program.*;
import acm.util.*;
import java.awt.*;

public class ACMLab extends GraphicsProgram {
	public static final int PROGRAM_HEIGHT = 600;
	public static final int PROGRAM_WIDTH = 800;
	
	public void init() {
		setSize(PROGRAM_WIDTH, PROGRAM_HEIGHT);
		requestFocus();
	}
	
	public void run() {
		GLabel label = new GLabel("My Robot Drawing - Trinity Belen", 050, 050);
		label.setColor(Color.red);
		label.setFont("Arial-Bold-24");
		add(label);
		
		GRect rect = new GRect (300,300,250,200);
		add(rect);
		GOval oval = new GOval (365,345,125,125);
		oval.setColor(Color.green);
		oval.setFilled(true);
		add(oval);
		GLine line = new GLine (150,50,200,150);
		add(line);
		
		GLine a = new GLine (200,150,200,120);
		add(a);
		
		GLine b = new GLine (200,150,150,150);
		add(b);
		
		GImage image = new GImage("robot.png", 315,147);
		add(image);
		
		GRect s1 = new GRect (300,500,100, 50);
		s1.setColor(Color.black);
		s1.setFilled(true);
		add(s1);
		
		GRect s2 = new GRect (450,500,100, 50);
		s2.setColor(Color.black);
		s2.setFilled(true);
		add(s2);
		
		GRect s = new GRect (370,275,120, 25);
		s.setColor(Color.black);
		s.setFilled(true);
		add(s);
	}
	
}
