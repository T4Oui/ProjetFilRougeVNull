package modele;
import com.sun.jna.Native;


import com.sun.jna.Library;
import com.sun.jna.Pointer;
import com.sun.jna.PointerType;
import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public interface LibraryTexteMoteur extends Library{
	LibraryTexteMoteur INSTANCE = (LibraryTexteMoteur) Native.loadLibrary("/home/pfr/pfr_code/texte/src/libTexte.so", LibraryTexteMoteur.class);

	public void indexation_texte();
	
	public void recupListeFichierTxt();
	public void redirCleanTok();
	public DESCRIPT_TXT crea_descript_txt(String fileName,int ident, String cheminRepertoireTok);
	public void ajoutListeBaseTxt(String pathFileSRC, int ident);
	public void nettoyage(String fileName, String pathStockageFich, String pathTraitement);
	public void copieRepTravail(String pathStockageFich, String fileName, String pathFile);
	public void enleverBalise(String pathFile);
	public void changerMajMin(String pathFile);
	public void supprNPremLig(int n, String pathFile);
	public void supprApostrophe(String pathFile);
	public void supprChiffre(String pathFile);
	public void supprPonctu(String pathFile);
	public void supprTiret(String pathFile);
	public void supprXml(String pathFile);
	public void filtrage(String fileName, String pathTraitement);
	public void enleverStopWord(String mot, String pathFile);
	public void creerFichTok(String pathFile);
	
	public PILE init_PILE();
	public void affiche_PILE(PILE p);
    public int PILE_estVide(PILE p);
    public PILE emPILE(PILE p, MOT mot);
    public PILE dePILE(PILE p, MOT.ByReference mot);
    
    public MOT initMot();
    public MOT addMot(String motTxt, int ident, String fileName);
    public int chercheNbOccur(String mot, String fileName);
    public void creerPileMot(MOT.ByReference pileMot, String fileName, IntByReference nbMotDiff, int ident, String cheminRepertoireTok);
    public DESCRIPT_TXT initDescript();
    public DESCRIPT_TXT creerDescript(String fileName, int ident, String cheminRepertoireTok);
    public void concatBaseDescript(DESCRIPT_TXT descript);
    public int comptageNbMot(String fileName);
    
    public Table initT();
    public Table addT(Table p, int fich, int nb);
    public void affT(Table p);
    public MotTable initM();
    public MotTable addM(MotTable p, String motTable);
    public MotTable add(MotTable p, int nb, String motTable, int fich);
    public void aff(MotTable p);
    public MotTable table(MotTable p, int ident, String fichier);
    
    public void recherche_comparaison_texte(String pathFileRecherchee, int nbFichierTxt);
    public void nbOccurCommun(int[] tabOccurCommun, DESCRIPT_TXT descriptMotRech, int nbFichierTxt);
    public int compareNbOccurComm(int[] tabOccurCommun, int nbFichierTxt);
    
    public void rech_MC(String mot);
    public void open_fich();
    
    public class MOT extends Structure {
        public int ident;
        public byte[] mot = new byte[50];
        public int nb_occur;
        public Pointer mot_suiv;

        public MOT() {
            super();
        }

        public MOT(Pointer p) {
            super(p);
        }

        public static class ByReference extends MOT implements Structure.ByReference {
            public ByReference() {
                super();
            }

            public ByReference(Pointer p) {
                super(p);
            }
        }
    }

    public class PILE extends Structure {
        public Pointer ptrMot;
        public Pointer pNext;

        public PILE() {
            super();
        }

        public PILE(Pointer p) {
            super(p);
        }

        public static class ByReference extends PILE implements Structure.ByReference {
            public ByReference() {
                super();
            }

            public ByReference(Pointer p) {
                super(p);
            }
        }
    }

    public class DESCRIPT_TXT extends Structure {
        public int ident;
        public PILE pile_mot;
        public int nb_mot_diff;
        public int taille_txt;

        public DESCRIPT_TXT() {
            super();
        }

        public DESCRIPT_TXT(Pointer p) {
            super(p);
        }

        public static class ByReference extends DESCRIPT_TXT implements Structure.ByReference {
            public ByReference() {
                super();
            }

            public ByReference(Pointer p) {
                super(p);
            }
        }
    }
    
    public static class Cel1 extends Structure {
        public int fich;
        public int nb;
        public Pointer suiv;
        
        public Cel1(Pointer p) {
            super(p);
        }
    }
    
    public static class Table extends PointerType {
        public Table(Pointer address) {
            super(address);
        }
        
        public Table() {
            super();
        }
    }
    
    public static class Cel2 extends Structure {
        public byte[] mot = new byte[50];
        public int nbMot;
        public Table table;
        public Pointer motTableSuiv;
        
        public Cel2(Pointer p) {
            super(p);
        }
    }
    
    public static class MotTable extends PointerType {
        public MotTable(Pointer address) {
            super(address);
        }
        
        public MotTable() {
            super();
        }
    }
}


