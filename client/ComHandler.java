package eyal.remote;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class ComHandler {

	private Socket s = null;
	private PrintWriter out = null;
	public boolean isConnected = false;
	
	public boolean connect(String ip){
		byte addr[] = new byte[4];
		getAddress(ip, addr);
		try {
			//s = new Socket(InetAddress.getByAddress(addr), 5555);
			s = new Socket(InetAddress.getByAddress(addr), 6000);
		} catch (UnknownHostException e) {
			System.out.println("UnknownHostException.");
			return false;
		} catch (IOException e) {
			System.out.println("Socket IOException.");
			return false;
		}
		
		try {
			out = new PrintWriter(s.getOutputStream(), true);
		} catch (IOException e) {
			System.out.println("PrintWriter IOException.");
			return false;
		}
		this.isConnected = true;
		return true;
	}
	
	public void send(String str){
		synchronized (this) {
			out.println(str);
		}
	}
	
	private void getAddress(String str, byte arr[]){
		int j = 0;
		int i = 0;
		int len = str.length();
		String temp = "";
		while (j < len){
			if (str.charAt(j) != '.')
				temp += str.charAt(j);
			if (str.charAt(j) == '.' || j == len-1){
				arr[i] = Byte.parseByte(temp);
				i++;
				temp = "";
			}
			j++;
		}
	}
	
}
