#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../include/recherche_image.h"



int tab_taille_couleur(int config,int noiroublanc)
{   
    int taille=0;
        if ((config==2)&&(noiroublanc==0)) 
        {
            taille=64; // 64 valeurs et l'identificateur stocké ailleurs
        }
        else if ((config==3)&&(noiroublanc==0))
        {

            taille=512; // 128 valeurs et l'identificateur stocké ailleurs
        }
        else if ((config==2)&&(noiroublanc==1))
        {

            taille=4; // 128 valeurs et l'identificateur stocké ailleurs
        }
        else if ((config==3)&&(noiroublanc==1))
        {

            taille=8; // 128 valeurs et l'identificateur stocké ailleurs
        }
        return taille;
}


 int configurationR  (FILE* fichier)
 {
  int carac=0;
  fseek(fichier,35,SEEK_SET); //permet de placer le curseur au niveau du caractère 13 (valeur de quantification) 
  fscanf(fichier,"%d",&carac); // lis le caractère au niveau du curseu
  return carac;
  }

  
float pourcentage(float partie,int total)
{
    return (100*partie/total); //retourne un pourcentage pouvant être flottant
}

 int intersection (int* tab1, int* tab2 ,int taille)
 {
    int val1=0, val2=0 , total=0 ;
    for (int i = 0; i < taille; i++)// on commence à 1 pour ne pas traiter la première case du tableau car elle contient l'identifiant et non pas une valeur de l'histogramme

    {
        val1 = *(tab1+i); //pointeur sur le contenu de l'adresse (on incrémente l'adresse de i pour parcourir toutes les cases du tableau)
        val2 = *(tab2+i);
        if(val1<=val2)
        {
            total=total+val1; //on fait la somme des minimums afin d'obtenir à la fin un total représentant ce qu'il y a en commun entre les deux histogramme
        }
        else //if (val2<val1)
        {
            total=total+val2;
        }
    // si les valeurs sont égales on ajoute la valeur au total
    }
    return total;
 }

 void remplissagestructure (TAB* tableau,int bit_quantification, FILE* base_descripteur_image,int noiroublanc)
 {
    int string=0;
    tableau->nb_valeur=tab_taille_couleur(bit_quantification,noiroublanc);
    fscanf(base_descripteur_image,"%d",&string);
    tableau->identifiant=string; //l'identificateur est stocké dans un champ réservé pour lui dans la structure
    for(int i =0;i<tableau->nb_valeur;i++)
    {
        fscanf(base_descripteur_image,"%d",&string);
        tableau -> T[i] = string; // le tableau contient seulement les valeurs de chaque couleur
       // printf("%d",tableau->T[i]);
        //printf("%d\t",tableau->T[i]);
    } 
    //printf("\n \n");
    //return tableau;
 }

void remplissagetab (TAB* tableau1,int nbdescripteurs,int noiroublanc)

 {
    if(noiroublanc==0)
    {
        FILE* base_descripteur_image = fopen("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt","r");
        FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
        int nb=configurationR(config);

        //TAB* tableau=(TAB*)malloc(sizeof(struct TAB)*nbdescripteurs);
      // printf("\n%d TEST NOMBRE DESCRIPTEUR\n",nbdescripteurs);

        for(int i=0;i<nbdescripteurs;i++)    
        {
            remplissagestructure((tableau1+i),nb,base_descripteur_image,noiroublanc);
                for(int i =0;i<tableau1->nb_valeur;i++)
    {
       // printf("%d\t",tableau1->identifiant);
        //printf("%d\t",tableau->T[i]);
    }
            //printf("%d TEST ULTIME xfyxtf\n",(tableau)->T[i]);

            //tableau=remplissagestructure(tableau,nb,base_descripteur_image,noiroublanc);
        }
          for(int i =0;i<63;i++)
    {
       // printf("%d",tableau->T[i]);
        //printf("%d\t",tableau->T[i]);
    } 
        //printf("%d TEST ULTIME",(tableau)->identifiant);
       // printf("\n");
        fclose(base_descripteur_image);
        fclose(config);
      //  return tableau;
        //free(tableau);

    }
    else
    {
        FILE* base_descripteur_image = fopen("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_noiroublanc.txt","r");
        FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
        int nb=configurationR(config);

       // printf("%d\t%d\n",nb,noiroublanc);
        for(int i=0;i<nbdescripteurs;i++)    
        {

            remplissagestructure((tableau1+i),nb,base_descripteur_image,noiroublanc);
        }
        fclose(base_descripteur_image);
        fclose(config);
        //return tableau;
        //free(tableau);
    }
 }

void affichagetab (TAB*tableau, int tailletableau)
{
   // printf("\n");
for(int j=0;j<tailletableau;j++)
{
    for (int i = 0; i < 63; i++)
    {
        //printf("%d",(tableau+j)->T[i]); //permet d'afficher toutes les valeurs des nbdescripteurs utile pour
    }
     //printf("\n\n");
}   
}
int compterlignes(FILE* fichier)
{
int c=0;;
int nblig = 1; //initialisation à 1 car il n'y a pas d'\n avant la première ligne mais on la compte quand même
while((c=fgetc(fichier)) != EOF) // on étudie tous les caractères du fichier
{
	if(c=='\n') // si c'est un caractere de fin de ligne on compte une ligne 
    {
        nblig++;
    }
}
return nblig;
}

//30000 couleur 4000 couleur;
int couleurougris(TAB* descripteur)
{
    /*if((descripteur->identifiant>=3000)&&descripteur->identifiant<4000)
        //comparaison_couleur();
    //else
        //comparaison_couleur();
    return 1;
    */
   return 1;
}


void comparaison_couleur(TAB* descripteur, int identifiant, int nbdescripteurs)
{
    int somme=0;
    float tab[nbdescripteurs];
    for(int i=0;i<nbdescripteurs;i++)
    {
        if(((descripteur+i)->identifiant)==identifiant)
        {
            for(int j=0;j<nbdescripteurs;j++)
            {
                if (j==i)
                {

                }

                else
                {
                    somme=intersection((descripteur+i)->T,(descripteur+j)->T,((descripteur+j)->nb_valeur));
                    (descripteur+j)->pourcentage=pourcentage(somme,((descripteur)+i)->total);
                   // printf("%f\n",(descripteur+j)->pourcentage);

                }


            }
        }
    }
    //return tab;


}

 void comparaison_noirblanc(FILE* fichier)
 {

 }

 void malloc_structure(TAB* tab,int nbdescripteurs)
 {
    for(int i=0;i<nbdescripteurs;i++)
    {
//         int taille = tab_taille_couleur(2,0);
        (tab+i)->T=(int*)malloc(sizeof(int)*(tab->nb_valeur));
        for(int j=0;j<tab->nb_valeur;j++)
        {
               (tab+i)->T[j]=0;
              // printf("%d",(tab+i)->T[j]);
        }
       // printf("\n");
        
        //TAB* tableau1=(TAB*)malloc(sizeof(struct TAB)*(nbdescripteurs)); //crée un tableau de la taille nombre de descripteur


    }
    //TAB* tableau1=(TAB*)malloc(sizeof(struct TAB)*(nbdescripteurs)); //crée un tableau de la taille nombre de descripteur
 }
 void free_structure(TAB* tab,int nbdescripteurs)
 {
        for(int j=0;j<nbdescripteurs;j++)
        {
            free(((tab+j)->T));
        }
                

}


 void total(TAB* descripteur,int tabtaillemax)
 {
    for(int j=0;j<tabtaillemax;j++)
    {
        int somme=0;
        for (int i = 0; i < (descripteur+j)->nb_valeur; i++)
        {
            somme=somme+((descripteur+j)->T[i]);
        }
        (descripteur+j)->total=somme;

    }
 }


void afficher_pourcentage(STRUCTPOURC* tableau2, int nbdescripteurs, float pourcentagemini)
    {
        for(int t=nbdescripteurs-1;t>=1;t--)
        {
            if(tableau2[t].pourcentage>pourcentagemini)
            {
                printf("%d\t%s\t%f\n",tableau2[t].identifiant,tableau2[t].fichier,(tableau2[t]).pourcentage);
            }
        
        }
    }
void tri (STRUCTPOURC* tableau2, int nbdescripteurs)
{
int i=0, j=0, d=0;
float c=0;
for(i=0;i<nbdescripteurs-1;i++)
{


    for(j=i+1;j<nbdescripteurs;j++)
    {

    
        if ( tableau2[i].pourcentage > tableau2[j].pourcentage ) 
        {
            c = tableau2[i].pourcentage;
            d=tableau2[i].identifiant;
            tableau2[i].pourcentage = tableau2[j].pourcentage;
            tableau2[i].identifiant = tableau2[j].identifiant;
            tableau2[j].pourcentage = c;
            tableau2[j].identifiant=d;
        }
    }

}
}
void remplissagetabpourcent(STRUCTPOURC* tableau2, TAB* tableau1, int nbdescripteurs)
{
    for(int z=0;z<nbdescripteurs;z++)
    {
        (tableau2[z]).pourcentage=(tableau1[z]).pourcentage;
        (tableau2[z]).identifiant=(tableau1[z]).identifiant;

    }
}
 int nbdenbdescripteurs(int noiroublanc)
 {
    int nbdescripteurs=0;
        if(noiroublanc==0)
    {
        FILE* base_descripteur_image=fopen("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt","r");
        nbdescripteurs=compterlignes(base_descripteur_image);//récupère le nb de lignes cad le nb de descripteur
       // printf("%d",nbdescripteurs);
       // printf("Hello world\n\n\n");

        //printf("%d\n\n\n",nbdescripteurs);
        fclose(base_descripteur_image);
    }
    else
    {
        FILE* base_descripteur_noiroublanc=fopen("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_noiroublanc.txt","r");
        nbdescripteurs=compterlignes(base_descripteur_noiroublanc);
        //printf("%d\n\n\n",nbdescripteurs);
        fclose(base_descripteur_noiroublanc);

    }
    return nbdescripteurs;

 }

 void afficher_resultat_couleur(STRUCTPOURC* tableau2, int nbdescripteurs)
    {
    int id_courant=0;
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt", "r");
    char chemin[256] ={0};
    char chaine[256] ={0};
    while (fscanf(fich,"%d",&id_courant) == 1)
        {
            fscanf(fich,"%s",chemin);
            if(id_courant==tableau2[nbdescripteurs-1].identifiant)//tailletab-1 car la structure du fichier recherché est toujours dans le tableau et on ne  veut pas afficher le pourcentage de ressemblance d'un fichier avec lui-même
            {
                printf("%s\n",chemin);
            }
        }
    fclose(fich);
    }

 void afficher_resultat_noiroublanc(STRUCTPOURC* tableau2, int nbdescripteurs)
    {
    int id_courant=0;
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_noirblanc.txt", "r");
    char chemin[256] ={0};
    char chaine[256] ={0};
    while (fscanf(fich,"%d",&id_courant) == 1)
        {
            fscanf(fich,"%s",chemin);
            if(id_courant==tableau2[nbdescripteurs-1].identifiant)//tailletab-1 car la structure du fichier recherché est toujours dans le tableau et on ne  veut pas afficher le pourcentage de ressemblance d'un fichier avec lui-même
            {
                printf("%s\n",chemin);
            }
        }
    fclose(fich);
    }

void recherchenoiretblanc(int fichierrecherche, float pourcentagemini,char* fichier)
{
    FILE* config = fopen("./.config","r");
    int noiroublanc=1;
    int nbdescripteurs=0;
    int bit_config=0;
    nbdescripteurs=nbdenbdescripteurs(noiroublanc);
    TAB* tableau1=(TAB*)malloc(sizeof(struct TAB)*(nbdescripteurs)); //crée un tableau de la taille nombre de 
    bit_config=configurationR(config);
    tableau1->nb_valeur=tab_taille_couleur(bit_config,noiroublanc);
    malloc_structure(tableau1,nbdescripteurs);
    remplissagetab(tableau1,nbdescripteurs, noiroublanc);
    total(tableau1,nbdescripteurs);
    comparaison_couleur( tableau1,fichierrecherche,nbdescripteurs);
    STRUCTPOURC tableau2[nbdescripteurs]; //crée un tableau de la taille nombre de descripteur
    remplissagetabpourcent(tableau2,tableau1,nbdescripteurs);
    tri(tableau2,nbdescripteurs);
    //printf("test tri\n");
    //afficher_pourcentage(tableau2,nbdescripteurs,pourcentagemini);
    //afficher_resultat_noiroublanc(tableau2,nbdescripteurs);
    recupfichier_noiroublanc(tableau2,nbdescripteurs);
    afficher_pourcentage(tableau2,nbdescripteurs,pourcentagemini);
    fclose(config);
    strcpy(fichier,tableau2[nbdescripteurs-1].fichier);
    free_structure(tableau1,nbdescripteurs);
    free(tableau1);//désallouement de l'espace mémoire
}
void recherchecouleur(int fichierrecherche, float pourcentagemini, char* fichier)
{
    FILE* config = fopen("./.config","r");
    int noiroublanc=0;
    int nbdescripteurs=0;
    int bit_config=0;
    nbdescripteurs=nbdenbdescripteurs(noiroublanc);
    TAB* tableau1=(TAB*)malloc(sizeof(struct TAB)*(nbdescripteurs)); //crée un tableau de la taille nombre de 
    bit_config=configurationR(config);
    tableau1->nb_valeur=tab_taille_couleur(bit_config,noiroublanc);
    //printf("%d",bit_config);
    malloc_structure(tableau1,nbdescripteurs);
    remplissagetab(tableau1,nbdescripteurs, noiroublanc);
    total(tableau1,nbdescripteurs);
    comparaison_couleur( tableau1,fichierrecherche,nbdescripteurs);
    STRUCTPOURC tableau2[nbdescripteurs]; //crée un tableau de la taille nombre de descripteur
    remplissagetabpourcent(tableau2,tableau1,nbdescripteurs);
    tri(tableau2,nbdescripteurs);
    //afficher_pourcentage(tableau2,nbdescripteurs,pourcentagemini);
    //afficher_resultat_couleur(tableau2,nbdescripteurs);
    recupfichier_couleur(tableau2, nbdescripteurs);
    // for(int i=0;i<nbdescripteurs;i++)
    // {
    //     printf("%s",tableau2[i].fichier);
    // }
    afficher_pourcentage(tableau2,nbdescripteurs,pourcentagemini);
    //afficher_resultat_couleur(tableau2,nbdescripteurs);
    fclose(config);
    strcpy(fichier,tableau2[nbdescripteurs-1].fichier);
    free_structure(tableau1,nbdescripteurs);
    free(tableau1);//désallouement de l'espace mémoire
}
void recupfichier_couleur (STRUCTPOURC* tab,int nbdescripteurs)
{
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt", "r");
    int id_courant=0;
            for(int i=0;i<nbdescripteurs;i++)
            {
                fscanf(fich,"%d",&id_courant);
                for (int j = 0; j < nbdescripteurs; j++)
                {
                    if(id_courant==(tab+j)->identifiant)
                    {
                        fscanf(fich,"%s",((tab+j)->fichier));
                    }
                }
            }

          
        
    fclose(fich);

}

void recupfichier_noiroublanc (STRUCTPOURC* tab,int nbdescripteurs)
{
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_noirblanc.txt", "r");
    int id_courant=0;
            for(int i=0;i<nbdescripteurs;i++)
            {
                fscanf(fich,"%d",&id_courant);
                for (int j = 0; j < nbdescripteurs; j++)
                {
                    if(id_courant==(tab+j)->identifiant)
                    {
                        fscanf(fich,"%s",((tab+j)->fichier));

                    }
                }
            }

          
        
    fclose(fich);

}


void open_image_coul(char * fichier){
    char chaine[150] = {0};
    char nomfich[150];
    FILE * file=fopen("/home/pfr/pfr_code_ambre/data/nfich_rech","a");
    fprintf(file,"%s",fichier);
    system("sed -e 's/.txt// /home/pfr/pfr_code_ambre/data/nfich_rech");
    FILE * fich =fopen("/home/pfr/pfr_code_ambre/data/nfich_rech","r");
    fscanf(fich,"%s",nomfich);
    snprintf(chaine,250,"display /home/pfr/pfr/image/fich_images/%s.jpg",nomfich);
    system(chaine);
    fclose(file);
}

void open_image_nb(char * fichier){
    char chaine[150] = {0};
    char nomfich[150];
    FILE * file=fopen("/home/pfr/pfr_code_ambre/data/nfich_rech","a");
    fprintf(file,"%s",fichier);
    system("sed -e 's/.txt// /home/pfr/pfr_code_ambre/data/nfich_rech");
    FILE * fich =fopen("/home/pfr/pfr_code_ambre/data/nfich_rech","r");
    fscanf(fich,"%s",nomfich);
    snprintf(chaine,250,"xdg-open /home/pfr/pfr/image/fich_images/%s.txt",nomfich);
    system(chaine);
    fclose(file);
}