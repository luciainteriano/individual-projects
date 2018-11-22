
import com.sun.glass.events.KeyEvent;

import jssc.*;

public class SerialComm {

	SerialPort port;

	private boolean debug;  // Indicator of "debugging mode"

	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}	


	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);		
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
				SerialPort.DATABITS_8,
				SerialPort.STOPBITS_1,
				SerialPort.PARITY_NONE);

		debug = false; // Default is to NOT be in debug mode
	}

	// TODO: Add writeByte() method from Studio 5
	void writeByte(byte b) throws SerialPortException {
		port.writeByte(b);
		if (debug == true) {
			String s = String.format("%02x", b);
			System.out.println("[0x" + s + "]");
		}
	}


	// TODO: Add available() method
	boolean available() throws SerialPortException {
		if (port.getInputBufferBytesCount() > 0) {
			return true;
		} else {
			return false;
		}
	}
	// TODO: Add readByte() method	
	byte readByte() throws SerialPortException {
		byte[] bytes = port.readBytes(1);
		return bytes[0];
	}

	// TODO: Add a main() method

	public static void main(String[] args) throws SerialPortException {

		try {
			SerialComm sc = new SerialComm("/dev/cu.usbserial-DN03FH0B");
			while(true) {
				if (sc.available() == true) {
					byte b = sc.readByte();
					//System.out.println((int) b);
					sc.writeByte(b);
				}
			}
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}

