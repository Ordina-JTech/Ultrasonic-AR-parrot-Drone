package ordina;

import java.io.*;
import java.net.*;

public class App 
{
    public static void main( String[] args ) {
        try {
            DatagramSocket serverSocket = new DatagramSocket(33333);

            byte[] receiveData = new byte[1024];
            String command = "AT*CONFIG=1,\"general:navdata_demo\",\"FALSE\"\r";
            String command2 = "somebytes";
            byte[] sendData = command.getBytes();
            byte[] sendData2 = command2.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("192.168.1.1"), 5556);
            DatagramPacket sendPacket2 = new DatagramPacket(sendData2, sendData2.length, InetAddress.getByName("192.168.1.1"), 5554);
            serverSocket.send(sendPacket);
            serverSocket.send(sendPacket2);

            while (true) {
                    DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                    serverSocket.receive(receivePacket);
                    String sentence = new String(receivePacket.getData());
                    System.out.println("RECEIVED: " + sentence);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}

