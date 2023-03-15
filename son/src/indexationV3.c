#include <stdio.h>
#include <stdlib.h>
#include "../include/histogrammeV3.h"
#include "../include/descripteurV3.h"
//#include "../include/fct_histogrammeV3.h"


void indexation_son(void){

    char nom_fic [100] = "corpus_fi.bin";

//strngs pour accéder aux fichiers ---------------------------------------------
    char chemin_desc [256] ="/home/pfr/pfr/son/descripteurs_sons/";
    char chemin_fich_sons[256] = "/home/pfr/pfr/son/fich_sons/";
    //char chaine2 [256] = "base/";
    char chaine3 [256] = "descripteur_";

    char descripteur[1000];
    char liste[1000];
    char bin [1000];
    char base [1000];
    
    sprintf(descripteur,"%s%s%s.txt",chemin_desc,chaine3,nom_fic);
    //printf("%s\n",descripteur);

    sprintf(liste,"%sliste.txt",chemin_desc);
    //printf("%s\n",liste);

    sprintf(base,"%sbase.txt", chemin_desc);

    sprintf(bin,"%s%s",chemin_fich_sons,nom_fic);
    printf("%s\n",bin);
//-------------------------------------------------------------------------------

    double echantillon;

    //distance entre deux points d'un intervalle
    double pas = (double)taille/m;

    //nombre de fenetres
    int k = 0;

    //indice de l'echantillon dans la fenetre de n echantillons
    int i_echant = 0;


    HISTOGRAMME h = {0};
    //initialisation du tableau de l'histogramme à 0
    for (int i_echant = 0; i_echant<m; i_echant++){
    //printf ("%d\n",h.tab[i_echant]);
    }

    DESCRIPTEUR d;
    //initialisation descripteur avec des histogrammes vides
    for (int i = 0;  i<1100; i++){
        d.histo[i]=h;
    }




    FILE* fichier = fopen(bin, "rb");
    if (fichier != NULL){

        int cpt; //============
        while( fread(&echantillon,sizeof(double),1, fichier ) == 1 ){

            //if ( feof(fichier) ) break;

            h = fct_histogramme( pas, echantillon, h );

            if (i_echant == n) {

                FILE* fic_descr = fopen("/home/pfr/pfr/son/descripteurs_sons/descripteur_corpus_fi.bin.txt","a");
                            
                    if (fic_descr == NULL) { 
                        //printf("Erreur ! Le fichier descripteur n'a pas pu être ouvert\n"); 
                        exit(0); 
                    } 

                    else{
                        for (int i = 0; i < m; i++) { 
                            fprintf(fic_descr,"%d \t",h.tab[i] ); 
                        } 
                        fprintf(fic_descr,"\n"); //retour à la ligne après la l'ecriture
                    
                    }
                fclose(fic_descr);

                //remplissage du descripteur
                d.histo[k] = h;


                    //-------------------------------------- affichage sur le terminal -----------------------------------------------------------------
                        //printf ("__________________________________fenetre %d___________________________________________________ \n",k);
                        for (int i = 0;  i<m; i++){
                            //printf("intervalle %d : %d \n",i,d.histo[k].tab[i]);
                        }
                    //------------------------------------------------------------------------------------------------------------------------------------
                i_echant = 0;
                k = k+1;
                   

                for (int i_echant = 0; i_echant<n; i_echant++){
                        h.tab[i_echant] = 0;
                }
            }
                cpt++;
                i_echant++;  
        }

        //printf ("\n*********************** i_echant = %d **************************************\n", i_echant );
        //printf("\n************************ k = %d ********************************************\n",k);

        /*
        Dans le cas ou le nombre de valeurs du fichier n'est pas multiple de n, on verifie si l'indice du dernier echantillon lu est compris entre 0 et n.
        Si c'est le cas, cela signifie qu'un histogrammme contenant "i_echant-1" echantillon a ete realise. On ajoute donc ce dernier au descrypteur.
        */
        if (i_echant > 0 && i_echant <= n){
            
            FILE* fic_descr = fopen("/home/pfr/pfr/son/descripteurs_sons/descripteur_corpus_fi.bin.txt","a");
                
                if (fic_descr == NULL) { 
                    //printf("Erreur ! Le fichier descripteur n'a pas pu être ouvert\n"); 
                    exit(0); 
                } 

                else{
                    for (int i = 0; i < m; i++) { 
                        fprintf(fic_descr,"%d \t",h.tab[i] ); 
                    } 
                    fprintf(fic_descr,"\n"); //retour à la ligne après la l'ecriture
                
                }
            fclose(fic_descr);

        }

        FILE* fic_liste = fopen(liste,"a");
                    
                    if (fic_liste == NULL) { 
                        //printf("Erreur ! La liste n'a pas pu être ouvert\n"); 
                        exit(0); 
                    } 

                    else{
                    
                        fprintf(fic_liste,"%s\n", nom_fic); //retour à la ligne après la l'ecriture
                    }
                    fclose(fic_liste);




                
        FILE* fic_base = fopen(base,"a");
            
            if (fic_liste == NULL) { 
                //printf("Erreur ! La liste n'a pas pu être ouvert\n"); 
                exit(0); 
            } 

            else{
            
                fprintf(fic_base,"descripteur_%s\n", nom_fic); //retour à la ligne après la l'ecriture
            }
            fclose(fic_base);

    }
    
    

    else{

    //printf ("Erreur ! Le fichier n'a pas pu être ouvert\n");
    exit(0);

    }

    fclose(fichier);

}