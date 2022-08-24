package TP;

import java.net.*;
import java.io.*;
import java.util.Scanner;

public class ClienteUltimo {

    public static void println   (String x){ System.out.println(x);  }
    public static void print     (String x){ System.out.print(x);    }
    public static final int PORT = 4040;

    public static void main(String[] args) throws IOException {

        println("Cliente iniciado.");
        
        try (
            Socket   socket = new Socket("localhost", PORT);
            Scanner  lector = new Scanner(socket.getInputStream());
        ) {
            while (true) {
                println("<Server> " + lector.nextLine());
            }
        }
    }
 
}
