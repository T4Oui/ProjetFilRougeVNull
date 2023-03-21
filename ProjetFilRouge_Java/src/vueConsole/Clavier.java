package vueConsole;

import java.util.Scanner;

public class Clavier {
    private static Scanner scanner = new Scanner(System.in);

    public static int entrerClavierInt() {
        return scanner.nextInt();
    }

    public static String entrerClavierString() {
        return scanner.next();
    }
    
    public static float entrerClavierFloat()
    {
    	return scanner.nextFloat();
    }

}
