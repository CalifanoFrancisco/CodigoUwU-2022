package TP;

import java.io.*;
import java.net.*;
import java.time.LocalTime;

public class ServidorMultiClientes {
    
    public static void   print            (String x   ){    System.out.print(x);                                    }
    public static void   println          (String x   ){    System.out.println(x);                                  }
    public static String localtimeToString(LocalTime i){    return i.getHour()+":"+i.getMinute()+":"+i.getSecond(); }

    private static final int PORT = 4040;
    private static LocalTime time;

    public static void main(String[] args) throws IOException {

        ServerSocket socketServidor = new ServerSocket(PORT);

        time = LocalTime.now();

        println("Servidor iniciado :D");

        while (true) {

            Socket socketCliente = socketServidor.accept();

            Thread thread = new Thread() {
                public void run() {
                    try (
                        PrintWriter escritor = new PrintWriter(socketCliente.getOutputStream(),true);
                    ) {        
                            while(true){
                                if(LocalTime.now().getSecond() != time.getSecond()){
                                    escritor.println(localtimeToString(LocalTime.now()));
                                    time = LocalTime.now();
                                }
                            }
                        
                    } catch (IOException e) { 
                        println("Error: " + e.getMessage());
                    }
                }
            };

            thread.start();
        }
    }
}
