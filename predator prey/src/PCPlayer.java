
import com.sun.glass.events.KeyEvent;

import jssc.*;

public class PCPlayer {
	
	public static void main(String[] args) throws SerialPortException {
		SerialComm sc = new SerialComm("/dev/cu.usbserial-DN03FRQG");
		while(true) {
			byte bt = 0;
			if (StdDraw.isKeyPressed(KeyEvent.VK_LEFT)) {
				bt = 3;
				System.out.println("left");
			}
			if (StdDraw.isKeyPressed(KeyEvent.VK_RIGHT)) {
				bt = 2;
				System.out.println("right");
			}
			if (StdDraw.isKeyPressed(KeyEvent.VK_UP)) {
				bt = 1;
				System.out.println("up");
			}
			if (StdDraw.isKeyPressed(KeyEvent.VK_DOWN)) {
				bt = 4;
				System.out.println("down");
			}
			if (bt != 0) {
				System.out.println(bt);
				sc.writeByte(bt);
				try {
					Thread.sleep(500); // stops reading buttons 
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
}