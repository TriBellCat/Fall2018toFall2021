import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Timer;

import acm.graphics.GLabel;
import acm.program.GraphicsProgram;

import javax.swing.*;

public class MyFirstTimer extends GraphicsProgram implements ActionListener {
	
	public static final int MAX_STEPS = 20;
	private GLabel myLabel;
	private Timer timeVar;
	private int numTimes = 0;
	
	public void run(){
		myLabel = new GLabel("# of times called?", 0, 100);
		add(myLabel);		
		timeVar = new Timer(1000, this);
		timeVar.start();
	}
	
	public void actionPerformed (ActionEvent e) {
		//TODO add what we want to do every two seconds
		myLabel.setLocation((myLabel.getX()+5),(myLabel.getY()+0));
		myLabel.setLabel("times called? " + numTimes);
		
		if(numTimes == 20) {
			timeVar.stop();
		}
		
		numTimes++;
	}
}



