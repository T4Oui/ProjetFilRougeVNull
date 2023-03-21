package testconsole;

import control.ControlRechercherImage;
import vueConsole.BoundaryRechercherImage;

public class TestAffichage {



		public static void main(String[] args) {
			// Initialisation controleur du cas
			ControlRechercherImage controlRechercheImage = new ControlRechercherImage();
			// Initialisation vue du cas
			BoundaryRechercherImage boundaryRechercheImage =
					new BoundaryRechercherImage(controlRechercheImage);

			// Lancement du cas
			boundaryRechercheImage.rechercheImage();

			// Verification de la bonne realisation du cas
			System.out.println("VERIFICATION");			
			// Resultat du test
			// Veuillez entrer votre nom
			// Victor
			// Veuillez entrer votre prenom
			// Martin
			// Veuillez entrer votre mot de passe
			// gmv
			// VERIFICATION
			// BDPersonnel [listePersonnel={0=Personnel [gerant=true, nom=Victor,prenom=Martin, login=Martin.Victor, mdp=gmv, connecte=false]}]
			// BDClient [listeClient={}]
		}
}
