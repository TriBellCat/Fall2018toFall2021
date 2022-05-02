import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import javax.swing.*;

import acm.graphics.*;
import acm.program.*;
import sun.misc.ObjectInputFilter.Status;

import java.util.HashMap; 
import java.util.Map; 

public class SoundBoard extends GraphicsProgram {
	public static final int WINDOW_WIDTH = 800;
	public static final int WINDOW_HEIGHT = 600;
	public static final int STATUS_LABEL_X = 200;
	public static final int STATUS_LABEL_Y = 550;

	public static final int HORN_LABEL_X = 200;
	public static final int HORN_LABEL_Y = 200;
	public static final int AWW_LABEL_X = 600;
	public static final int AWW_LABEL_Y = HORN_LABEL_Y;
	public static final String FONT_STYLE = "Arial-20-Bold";
	
	private AudioPlayer player;
	private GLabel statusLabel;
	private GLabel hornLabel;
	private GLabel yeahLabel;
	
	private SoundEffect horn;
	private SoundEffect yeah;
	
	private HashMap <GLabel, Playable> map;
	
	public void run() {
		HashMap <GLabel, Playable> map = new HashMap <GLabel, Playable> ();
		
		player = AudioPlayer.getInstance();
		// TODO add more labels
		
		statusLabel = new GLabel("", STATUS_LABEL_X, STATUS_LABEL_Y);
		add(statusLabel);
		
		yeahLabel = new GLabel("Ahh Yeah", AWW_LABEL_X, AWW_LABEL_Y);
		yeahLabel.setFont(FONT_STYLE);
		add(yeahLabel);
		map.put(yeahLabel, new SoundEffect (yeahLabel.getLabel()));
		
		hornLabel = new GLabel("Air Horn", HORN_LABEL_X, HORN_LABEL_Y);
		hornLabel.setFont(FONT_STYLE);
		add(hornLabel);
		map.put(hornLabel, new SoundEffect (hornLabel.getLabel()));
		
		addMouseListeners();
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		GObject elem = getElementAt(e.getX(), e.getY());
		if (elem instanceof GLabel) {
			// TODO play different sounds
			SoundEffect yeah = new SoundEffect ("Ahh Yeah");
			yeah.play(player, statusLabel);
			SoundEffect horn = new SoundEffect("Air Horn");
			horn.play(player, statusLabel);
		}
	}

	public void init() {
		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}
