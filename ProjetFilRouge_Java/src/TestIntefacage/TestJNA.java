package TestIntefacage;

import modele.LibraryImageMoteur;
import modele.LibrarySonMoteur;
import modele.LibraryTexteMoteur;
import com.sun.jna.Pointer;

public class TestJNA {
	
	public static void main(String[] args) {
		LibraryTexteMoteur libraryTexteMoteur = LibraryTexteMoteur.INSTANCE;
		//libraryTexteMoteur.indexation_texte();
		//libraryTexteMoteur.rech_MC("musique");
		libraryTexteMoteur.recherche_comparaison_texte("/home/pfr/DATA_PFR/08-Carlos_do_Carmo____Le_utf8", 35);
		
		//LibraryImageMoteur libraryImageMoteur = LibraryImageMoteur.INSTANCE;
		//libraryImageMoteur.indexation_image();
		//Pointer fich = null;
		//libraryImageMoteur.recherchenoiretblanc(4002, 50, fich);
		//System.out.println(fich);
		//LibrarySonMoteur librarySonMoteur = LibrarySonMoteur.INSTANCE;
		//librarySonMoteur.indexation_son();
	}
}