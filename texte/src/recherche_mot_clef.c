#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/home/pfr/pfr_code/texte/include/recherche_mot_clef.h"

void rech_MC(char * mot){
    system("echo >/home/pfr/pfr_code/data/rech_mot_clef.txt");
    char carac[200];
    char chaine[210];
    int nbMot;
    int id_courant;
    int id_fich;
    char chemin[200];
    FILE * table =fopen("/home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt","r"); 
    while(fscanf(table,"%s",carac)){
        if(strcmp(carac,mot)==0){
            fscanf(table,"%d",&nbMot);
            int fich;
            int nb;
            for(int i=0;i<nbMot;i++){
                fscanf(table,"%d",&fich);
                fscanf(table,"%d",&nb);
                snprintf(chaine, 150,"echo '%d %d'>> /home/pfr/pfr_code/data/rech_mot_clef.txt",fich,nb);
                system(chaine);
            }
            snprintf(chaine,270,"sort -k 2 -nr /home/pfr/pfr_code/data/rech_mot_clef.txt > /home/pfr/pfr_code/data/rech_mot_clef_tri.txt");
            system(chaine);
            FILE *rech = fopen("/home/pfr/pfr_code/data/rech_mot_clef_tri.txt","r");
            while (fscanf(rech,"%d",&id_fich)==1){
                fscanf(rech,"%d",&nb);
                FILE *base = fopen("/home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt", "r");
                while (fscanf(base,"%d",&id_courant) == 1){
                    fscanf(base,"%s",chemin);
                    if(id_courant==id_fich){
                        printf("%s %d\n",chemin,nb);
                    }
                }
                fclose(base);
            }
            fclose(rech);
            break;
        }
    }
    fclose(table);
}


void open_fich(){
    int ident;
    int id_courant;
    char chemin[150] ={0};
    char chaine[150] = {0};
    FILE * rech = fopen("/home/pfr/pfr_code/data/rech_mot_clef_tri.txt","r");
    fscanf(rech,"%d",&ident);
    fclose(rech);
    FILE *fich = fopen("/home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt", "r");
    while (fscanf(fich,"%d",&id_courant) == 1){
        fscanf(fich,"%s",chemin);
        if(id_courant==ident){
            snprintf(chaine,220,"xdg-open %s",chemin);
            system(chaine);
            break;
        }
    }
    fclose(fich);
}


int main(int argc,char *argv[]){
    //char chaine[100];
    printf("mot clef %s\n",argv[1]);
    rech_MC(argv[1]);
    //snprintf(chaine,100,"echo '%s' > /home/pfr/pfr_code/texte/src/resultat.txt",argv[1]);
    //system(chaine);
    return 0;
}
