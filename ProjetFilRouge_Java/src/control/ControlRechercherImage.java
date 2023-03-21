package control;

public class ControlRechercherImage {
	String nom="test";
	public ControlRechercherImage() {
		// TODO Auto-generated constructor stub
	}
	
	public String rechercheImageNB(float pourcentageMini, String nom)
	{
		//nom=rechercheImageNB(pourcentage,nom) du C
		this.nom="NB"+String.valueOf(pourcentageMini)+nom;
		return this.nom;
	}
	
	public String rechercheImageCouleur(float pourcentageMini, String nom)
	{
		//nom=rechercheImageCouleur(pourcentage,nom) du C
		this.nom="Couleur"+String.valueOf(pourcentageMini)+nom;

		return this.nom;
	}
	
	public String rechercheParCouleur(int couleur)
	{
		nom=couleur+"TEST COULEUR";
		
		return this.nom;
	}

}
