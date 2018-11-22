package lab9;

import lab9.providers.ReceivesHistory;
import sedgewick.StdDraw;

public class GetsHistory1 implements ReceivesHistory {

	@Override
	public void sendHistory(History history) {
		Guess g = history.getHistoryAt(0);
		System.out.println("GetsHistory 1 remember first move? " + g);
		// TODO Auto-generated method stub
		System.out.println("GetHistory1 has received new history");
		int size = history.size();
		Guess recentGuess = history.getHistoryAt(size-1);
		System.out.println(" and your most recent move is "+ recentGuess);
		
		
	}

}
