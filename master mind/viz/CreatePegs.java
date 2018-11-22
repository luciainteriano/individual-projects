package lab9.viz;

import sedgewick.StdDraw;

import java.awt.Color;

import lab9.GameProperties;
import lab9.Guess;
import lab9.History;
import lab9.providers.ProvidesColor;
import lab9.providers.ProvidesGuess;
import lab9.providers.ReceivesHistory;

public class CreatePegs implements ReceivesHistory {

	public GameProperties gp; 
	public ProvidesColor co;
	public ProvidesGuess codeMaker;
	public ProvidesGuess codeBreaker;
	public double placementY;
	//public History history;

	public CreatePegs(GameProperties gameProperties, ProvidesGuess cb, ProvidesColor pc) {
		this.gp = gameProperties;
		this.codeBreaker = cb;
		this.co = pc;
		this.placementY= .99;
		System.out.println("draw");
		StdDraw.setXscale(0, 1.0);
		StdDraw.setYscale(0, 1.0);

	}

	//	public void drawDots() {
	//
	//	}

	@Override
	public void sendHistory(History history) {
		int size = history.size();
		System.out.println(size);

		Guess mostRecent= history.getHistoryAt(size-1);

		double xSpacing = 1.0/(double)(this.gp.getNumHoles()+1);
		double ySpacing = 1.0/(double)(this.gp.getMaxNumGuesses()+1);

		double placementX = 0.0;
	//	double placementY = .99;

		for (int j=0; j<this.gp.getNumHoles(); j++) {
			StdDraw.setPenColor(co.getColorForPeg(mostRecent.getChoice(j)));
			//StdDraw.setPenColor(co.getColorForPeg(p))
			StdDraw.filledCircle(placementX, placementY, .03);
			placementX = placementX + xSpacing;
		
		}
		placementX=0.0;
		placementY = placementY - ySpacing;
	}

}