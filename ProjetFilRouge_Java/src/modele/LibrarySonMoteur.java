package modele;

import com.sun.jna.Native;
import com.sun.jna.Library;
import com.sun.jna.Structure;

public interface LibrarySonMoteur extends Library{
	LibrarySonMoteur INSTANCE = (LibrarySonMoteur) Native.loadLibrary("/home/pfr/pfr_code/son/src/libSon.so", LibrarySonMoteur.class);
	
	int n = 1024;
    int m = 20;
    int taille = 2;

    public static class HISTOGRAMME extends Structure {
        public int[] tab = new int[m];
        public HISTOGRAMME() {
            super();
        }
    }

    public static class DESCRIPTEUR extends Structure {
        public HISTOGRAMME[] histo = new HISTOGRAMME[2000];
        public DESCRIPTEUR() {
            super();
        }
    }

    HISTOGRAMME fct_histogramme(double pas, double echant, HISTOGRAMME h);

    void indexation_son();
}
