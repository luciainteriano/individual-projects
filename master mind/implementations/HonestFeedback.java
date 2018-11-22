package lab9.implementations;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import lab9.Guess;
import lab9.providers.ProvidesFeedback;

/**
 * Correctly responds to a given Guess
 * 
 * @author roncytron
 *
 */
public class HonestFeedback implements ProvidesFeedback {

	private final Guess code;

	/** 
	 * Capture the code that will be compared with Guesses
	 * @param code
	 */
	public HonestFeedback(Guess code) {
		this.code = code;
	}

	/**
	 * For the supplied Guess, how many peg ids occur in the correct position
	 *   with respect to the desired goal?
	 * For example, if the goal is 0 2 3 1
	 *            and the guess is 0 1 3 4
	 * then the result is 2, because the pegs with ids 0 and 3 are in exactly the
	 * right position.
	 * @param guess the Guess to be judged with respect to the goal
	 * @return the number of peg ids in the correct position
	 */

	@Override
	public int numSamePosition(Guess other) {
		//this.g & this.other are the arrays
		int c = 0;
		for (int i= 0; i<this.code.size(); i++) {
			if(this.code.g[i] == other.g[i]) {
				c= c+1;
			}
		}
		return c;
	}

	/**
	 * Given the supplied Guess, how many peg ids are in common with the desired
	 *    goal and the guess?
	 *    
	 * For example, if the goal is 0 2 3 1
	 *            and the guess is 0 1 3 4
	 * then the result is 3 because peg ids 0, 1, and 3 occur in both the goal and
	 * the guess.
	 * @param guess the Guess to be judged with respect to the goal
	 * @return the number of peg ids in common with the goal and the guess
	 */

	@Override
	public int numIntersection(Guess other) {
		Set<Integer> cSet = new HashSet<Integer>();
		Set<Integer> gSet = new HashSet<Integer>();
		
		for (int j= 0; j<code.size(); j++) {
			cSet.add(code.getChoice(j));
		}
		for (int k = 0; k<code.size(); k++) {
			gSet.add(other.getChoice(k));
		}
		
		Set<Integer> whereIntersect = new HashSet<Integer>(cSet);
		whereIntersect.retainAll(gSet);
		return whereIntersect.size();
	}

	/**
	 * Is the solution correct?   This can be reduced from numSamePosition(guess)
	 *   returning an answer showing all pegs of the Guess are in the correct
	 *   position.
	 * @param guess the supplied Guess to be judged
	 * @return true iff the guess is completely correct
	 */

	public boolean isSolution(Guess other) {
		int c = 0;
		for (int i= 0; i<this.code.size(); i++) {
			if(this.code.g[i] == other.g[i]) {
				c= c+1;
			}
		}
		if (c==this.code.size()) {
			return true;
		}
		return false;
	}
//	int[] array = {20,22,23,24,25,26,27,28,30,31};
//	int[] nums = new int[5];
//	for (int i = 0; i < 31; i++) {
//		
	}
