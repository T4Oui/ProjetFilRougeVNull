package vueConsole;

import control.ControlRechercherImage;

public class BoundaryRechercherImage {
	private ControlRechercherImage controlRechercherImage;
	//private int choix1, choix2,couleur=0 ;
	private float pourcentage;
	public BoundaryRechercherImage(ControlRechercherImage controlRechercherImage) {
		// TODO Auto-generated constructor stub
		this.controlRechercherImage=controlRechercherImage;
	}
	
	public void rechercheImage()
	{
		int choix1;
		System.out.println("Entrez le numéro de la recherche que vous souhaitez effectuer :");		
		for(choix1=0;!(choix1==1 || choix1==2);) //pour ne pas utiliser de while
		{
			System.out.println("1. Recherche par nom/chemin");
			System.out.println("2. Recherche par couleur");
			choix1=Clavier.entrerClavierInt();
			if(!(choix1==1 || choix1==2))
			{
				System.out.println("Veuillez entrez 1 ou 2");
			}
		}
		switch(choix1)
		{
			case 1:
				int choix2;
				System.out.println("Entrez le type d'image que vous souhaitez rechercher");
				for(choix2=0;!(choix2==1 || choix2==2);) //pour ne pas utiliser de while
				{
					System.out.println("1. Image NB");
					System.out.println("2. Image Couleur");
					choix2=Clavier.entrerClavierInt();
					if(!(choix2==1 || choix2==2))
					{
						System.out.println("Veuillez entrez 1 ou 2");
					}
				}
				System.out.println("Veuillez entrer le pourcentage de ressemblance minimum que vous désirez");
				for(this.pourcentage=-1;!(this.pourcentage<=100 && this.pourcentage>=0);) //pour ne pas utiliser de while
				{
					this.pourcentage=Clavier.entrerClavierFloat();
					if(!(this.pourcentage<=100 && this.pourcentage>=0))
					{
						System.out.println("Veuillez entrer un pourcentage entre 0 et 100");
					}
				}
				System.out.println("Veuillez entrer le nom ou le chemin du fichier que vous souhaitez rechercher");
				String chemin=Clavier.entrerClavierString();
				switch (choix2)
				{
					case 1 :
						String fichierAOuvrir=controlRechercherImage.rechercheImageNB(pourcentage, chemin);
						System.out.println(fichierAOuvrir);
						break;
					case 2 :
						fichierAOuvrir=controlRechercherImage.rechercheImageCouleur(pourcentage, chemin);
						System.out.println(fichierAOuvrir);
						break;
						
				}
				break;
			case 2 :
				System.out.println("Veuillez choisir une couleur parmi celles ci-dessous :");
				int couleur;
				for(couleur=0;!(couleur==1 || couleur==2 || couleur==3 || couleur==4);) //pour ne pas utiliser de while
				{
					System.out.println("1. Bleu");
					System.out.println("2. Rouge");
					System.out.println("3. Vert");
					System.out.println("4. Violet");
					couleur=Clavier.entrerClavierInt();
					if(!(couleur==1 || couleur==2 || couleur ==3 || couleur ==4 ))
					{
						System.out.println("Veuillez entrez 1, 2, 3, 4");
					}
				}
				String fichierAOuvrir=controlRechercherImage.rechercheParCouleur(couleur);
				System.out.println(fichierAOuvrir);
				break;

				
				

				
		}
		
	}

}
