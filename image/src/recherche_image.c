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

            taille=512; // 512 valeurs et l'identificateur stocké ailleurs
        }
        else if ((config==2)&&(noiroublanc==1))
        {

            taille=4; // 4 valeurs et l'identificateur stocké ailleurs
        }
        else if ((config==3)&&(noiroublanc==1))
        {

            taille=8; // 8 valeurs et l'identificateur stocké ailleurs
        }
        return taille;
}


 int configurationR  (FILE* fichier)
 {
  int carac=0;
  fseek(fichier,35,SEEK_SET); //permet de placer le curseur au niveau du caractère 35 (valeur de quantification) 
  fscanf(fichier,"%d",&carac); // lis le caractère au niveau du curseur
  return carac;
  }

  
float pourcentage(float partie,int total)
{
    return (100*partie/total); //retourne un pourcentage pouvant être flottant
}

 int intersection (int* tab1, int* tab2 ,int taille)
 {
    int val1=0, val2=0 , total=0 ;
    for (int i = 0; i < taille; i++)// on parcourt toute les cases du tableau 

    {
        val1 = *(tab1+i); //pointeur sur le contenu de l'adresse (on incrémente l'adresse de i pour parcourir toutes les cases du tableau)
        val2 = *(tab2+i);
        if(val1<=val2)
        {
            total=total+val1; //on fait la somme des minimums afin d'obtenir à la fin un total représentant ce qu'il y a en commun entre les deux histogramme
        }
        else 
        {
            total=total+val2;
        }
    }
    return total;
 }

 void remplissagestructure (TAB* tableau,int bit_quantification, FILE* base_descripteur_image,int noiroublanc)
 {
    int string=0;
    tableau->nb_valeur=tab_taille_couleur(bit_quantification,noiroublanc); // on récupère le nombre de valeurs grâce à tab_taillecouleur
    fscanf(base_descripteur_image,"%d",&string);
    tableau->identifiant=string; //l'identificateur est stocké dans un champ réservé pour lui dans la structure
    for(int i =0;i<tableau->nb_valeur;i++)
    {
        fscanf(base_descripteur_image,"%d",&string);
        tableau -> T[i] = string; // le tableau contient seulement les valeurs de chaque couleur
    } 
 }

void remplissagetab (TAB* tableau1,int nbdescripteurs,int noiroublanc)

 {
    if(noiroublanc==0)
    {
        FILE* base_descripteur_image = fopen("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt","r");
        FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
        int nb=configurationR(config);
        for(int i=0;i<nbdescripteurs;i++)    
        {
            remplissagestructure((tableau1+i),nb,base_descripteur_image,noiroublanc); //pour chaque descripteur on remplit sa structure
        } 
        fclose(base_descripteur_image);
        fclose(config);
    }
    else
    {
        FILE* base_descripteur_image = fopen("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt","r");
        FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
        int nb=configurationR(config);
        for(int i=0;i<nbdescripteurs;i++)    
        {

            remplissagestructure((tableau1+i),nb,base_descripteur_image,noiroublanc);
        }
        fclose(base_descripteur_image);
        fclose(config);
    }
 }

void affichagetab (TAB*tableau, int tailletableau)
{
for(int j=0;j<tailletableau;j++)
{
    for (int i = 0; i < 63; i++)
    {
        printf("%d",(tableau+j)->T[i]); //permet d'afficher toutes les valeurs des nbdescripteurs utile pour le débuggage
    }
    printf("\n\n");
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
                }


            }
        }
    }


}


 void malloc_structure(TAB* tab,int nbdescripteurs)
 {
    for(int i=0;i<nbdescripteurs;i++)
    {
        (tab+i)->T=(int*)malloc(sizeof(int)*(tab->nb_valeur));
        for(int j=0;j<tab->nb_valeur;j++)
        {
               (tab+i)->T[j]=0;          // cela permet d'allouer la mémoir popur le tableau de chaque descripteur
        }
    }
 }
 void free_structure(TAB* tab,int nbdescripteurs)
 {
        for(int j=0;j<nbdescripteurs;j++)
        {
            free(((tab+j)->T)); // permet de free la première case de chaque tableau
        }
}


 void total(TAB* descripteur,int tabtaillemax)
 {
    for(int j=0;j<tabtaillemax;j++)
    {
        int somme=0;
        for (int i = 0; i < (descripteur+j)->nb_valeur; i++)
        {
            somme=somme+((descripteur+j)->T[i]);      // calcul simplement le total
        }
        (descripteur+j)->total=somme;

    }
 }


void afficher_pourcentage(STRUCTPOURC* tableau2, int nbdescripteurs, float pourcentagemini)
    {
        for(int t=nbdescripteurs-1;t>=1;t--) 
        {            if(tableau2[t].pourcentage>=pourcentagemini)
            {
                printf("%s\t%f\n",tableau2[t].fichier,(tableau2[t]).pourcentage);
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

    
        if ( tableau2[i].pourcentage > tableau2[j].pourcentage )  // tri structures en fonction de la valeur de leur pourcentage
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

int comptageNbLigne(char * pathFile){

    int ctpMot=0;
    char comptageMot[256]={0};
    //comptage du nombre de mot du fichier passer en paramètre
    snprintf(comptageMot,sizeof(comptageMot),"wc -l %s > /home/pfr/pfr_code/data/comptage.txt",pathFile);
    system(comptageMot);
    
    //récupération du nombre de mot dans le fichier comptage.txt
    FILE * comptage = fopen("/home/pfr/pfr_code/data/comptage.txt","r");
    fscanf(comptage,"%d",&ctpMot);
    fclose(comptage);
    return ctpMot;
}

 int nbdenbdescripteurs(int noiroublanc)
 {
    int nbdescripteurs=0;
        if(noiroublanc==0)
    {
        nbdescripteurs = comptageNbLigne("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt");
    }
    else
    {
        nbdescripteurs = comptageNbLigne("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt");
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
            if(id_courant==tableau2[nbdescripteurs-1].identifiant)//nbdescripteurs-1 car la structure du fichier recherché est toujours dans le tableau et on ne  veut pas afficher le pourcentage de ressemblance d'un fichier avec lui-même
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
            if(id_courant==tableau2[nbdescripteurs-1].identifiant)//nbdescripteurs-1 car la structure du fichier recherché est toujours dans le tableau et on ne  veut pas afficher le pourcentage de ressemblance d'un fichier avec lui-même
            {
                printf("%s\n",chemin);
            }
        }
    fclose(fich);
    }

void recherchenoiretblanc(int fichierrecherche, float pourcentagemini,char* fichier)
{
    FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
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
    for(int i=0;i<nbdescripteurs;i++)
    {
        if(tableau2[i].identifiant==fichierrecherche)
        {
            tableau2[i].pourcentage=0;
        }
    }
    tri(tableau2,nbdescripteurs);
    recupfichier_noiroublanc(tableau2,nbdescripteurs);
    afficher_pourcentage(tableau2,nbdescripteurs,pourcentagemini);
    fclose(config);
    strcpy(fichier,tableau2[nbdescripteurs-1].fichier);
    free_structure(tableau1,nbdescripteurs);
    free(tableau1);//désallouement de l'espace mémoire
}
void recherchecouleur(int fichierrecherche, float pourcentagemini, char* fichier)
{
    FILE* config = fopen("/home/pfr/pfr_code/config.txt","r");
    int noiroublanc=0;
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
    for(int i=0;i<nbdescripteurs;i++)
    {
        if(tableau2[i].identifiant==fichierrecherche)
        {
            tableau2[i].pourcentage=0;
        }
    }
    tri(tableau2,nbdescripteurs);
    recupfichier_couleur(tableau2, nbdescripteurs);
    afficher_pourcentage(tableau2,nbdescripteurs,pourcentagemini);
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
    FILE *fich = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_NB.txt", "r");
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
    char chaine[256] = {0};
    char nomfich[150];
    char changerNom[256]={0};
    int ret = snprintf(changerNom,sizeof(changerNom),"echo '%s' > /home/pfr/pfr_code/data/nfich_rech.txt ",fichier);
    if(ret<0){
        abort();
    } else system(changerNom);
    system("sed -i -e 's/txt/jpg/g' /home/pfr/pfr_code/data/nfich_rech.txt");
    FILE * fich =fopen("/home/pfr/pfr_code/data/nfich_rech.txt","r");
    fscanf(fich,"%s",nomfich);
    ret = snprintf(chaine,sizeof(chaine),"display /home/pfr/pfr/image/fich_images/%s",nomfich);
    if(ret<0){
        abort();
    } else system(chaine);
    fclose(fich);
}

void open_image_nb(char * fichier){
    char chaine[256] = {0};
    char nomfich[150];
    char changerNom[256]={0};
    int ret = snprintf(changerNom,sizeof(changerNom),"echo '%s' > /home/pfr/pfr_code/data/nfich_rech.txt ; sed -i -e 's/txt/bmp/g' /home/pfr/pfr_code/data/nfich_rech.txt",fichier);
    if(ret<0){
        abort();
    } else system(changerNom);
    FILE * fich =fopen("/home/pfr/pfr_code/data/nfich_rech.txt","r");
    fscanf(fich,"%s",nomfich);
    ret = snprintf(chaine,sizeof(chaine),"viewnior /home/pfr/pfr/image/fich_images/%s",nomfich);
    if(ret<0){
        abort();
    } else system(chaine);
    fclose(fich);
}