package modele;

import java.io.BufferedReader;

import java.io.IOException;
import java.io.InputStreamReader;

public class TestExec {

    public static void main(String[] args) throws IOException {
        // Créer la commande pour exécuter l'exécutable C avec les arguments d'entrée
        //String[] cmd = {"/home/pfr/eclipse-workspace/ProjetFilRouge/exec/indexation_texte.out"};
    	//String[] cmd = {"/home/pfr/eclipse-workspace/ProjetFilRouge/exec/recherche_mot_clef.out","musique"};
    	//String[] cmd = {"/home/pfr/eclipse-workspace/ProjetFilRouge/exec/recherche_texte.o"};
    	
        // Exécuter la commande
        Process process = Runtime.getRuntime().exec(cmd);
        // Lire la sortie standard de l'exécutable
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        // Attendre que l'exécution de l'exécutable soit terminée
        try {
            int exitCode = process.waitFor();
            System.out.println("Exit code: " + exitCode);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

