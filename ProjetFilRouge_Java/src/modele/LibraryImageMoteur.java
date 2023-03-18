package modele;
import com.sun.jna.Native;

import java.util.Arrays;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;
import com.sun.jna.Memory;

public interface LibraryImageMoteur extends Library{
	LibraryImageMoteur INSTANCE = (LibraryImageMoteur) Native.loadLibrary("/home/pfr/pfr_code/image/src/libImage.so", LibraryImageMoteur.class);
	
	
	public static class TAB extends Structure {
        public int identifiant;
        public int nb_valeur;
        public Pointer T;
        public float pourcentage;
        public int total;

        public TAB() {
            super();
        }

        public TAB(Pointer pointer) {
            super(pointer);
        }

        protected List<String> getFieldOrder() {
            return Arrays.asList("identifiant", "nb_valeur", "T", "pourcentage", "total");
        }

        public int[] getT() {
            return T.getIntArray(0, nb_valeur);
        }

        public void setT(int[] T) {
            this.T = new Memory(T.length * Native.getNativeSize(Integer.TYPE));
            this.T.write(0, T, 0, T.length);
            this.nb_valeur = T.length;
        }
    }

    public static class STRUCTPOURC extends Structure {
        public int identifiant;
        public float pourcentage;
        public byte[] fichier = new byte[20];

        public STRUCTPOURC() {
            super();
        }

        public STRUCTPOURC(Pointer pointer) {
            super(pointer);
        }

        protected List<String> getFieldOrder() {
            return Arrays.asList("identifiant", "pourcentage", "fichier");
        }
    }

    int quantification (int[] tab, int b, int n);
    Pointer pretraitement_image(String fichier, int[] ptrNBLIG, int[] ptrNBCOL, int[] ptrB, int n);
    Pointer pretraitement_recherche(String fichier, int[] ptrNBLIG, int[] ptrNBCOL, int[] ptrB, int n);
    int histogramme (Pointer tab, int nbr, int[] ptrNBLIG, int[] ptrNBCOL);
    void mise_a_jour_base_image(Pointer LBI, Pointer BDI, String f, int[] descripteur, int n, int[] d);
    Pointer openFile(String nomFichier, String m);
    Pointer descripteur_image(Pointer tab, int n, int[] ptrNBCOL, int[] ptrNBLIG, int[] d);
    int configuration(Pointer fichier);
    Pointer indexation_recherche(String image);
    void indexation_image();
    float pourcentage(float partie, int total);
    int intersection(int[] tab1, int[] tab2, int taille);
    int configurationR(Pointer fichier);
    int tab_taille_couleur(int config, int noiroublanc);
    void remplissagestructure(TAB couleur, int bit_quantification, Pointer base_descripteur_image, int noiroublanc);
    int compterlignes(Pointer fichier);
    void remplissagetab(TAB tableau1, int nblignes, int noiroublanc);
    void affichagetab(TAB tableau, int tailletableau);
    int couleurougris(TAB descripteur);
    int fichier_a_traiter(TAB descripteur, int nblignes);
    void comparaison_couleur(TAB descripteur, int identifiant, int nblignes);
    void comparaison_noirblanc(Pointer fichier);
    void malloc_structure(TAB tab, int nblignes);
    void total(TAB descripteur, int tabtaillemax);
    void free_structure(TAB tab, int nblignes);
    void afficher_resultat_noiroublanc(STRUCTPOURC tableau2, int nblignes);
    void afficher_resultat_couleur(STRUCTPOURC tableau2, int nblignes);
    void afficher_pourcentage(STRUCTPOURC tableau2, int nblignes, float pourcentagemini);
    void tri(STRUCTPOURC tableau2, int nblignes);
    void remplissagetabpourcent(STRUCTPOURC tableau2, TAB tableau1, int nblignes);
    int nbdedescripteurs(int noiroublanc);
    void recherchenoiretblanc(int fichierrecherche, float pourcentagemini, String fichier);
    void recherchecouleur(int fichierrecherche, float pourcentagemini, String fichier);
    TAB init_tableau(TAB tableau1, int nbdescripteurs);
    void recupfichier_couleur(STRUCTPOURC tab, int nbdescripteurs);
    void recupfichier_noiroublanc(STRUCTPOURC tab, int nbdescripteurs);
    void open_image_coul(String fichier);
    void open_image_nb(String fichier);
    int comptageNbLigne(String pathFile);
}


