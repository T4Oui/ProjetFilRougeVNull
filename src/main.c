#include <stdio.h> 
#include <stdlib.h>
#include "/home/pfr/pfr_code/texte/include/indexation_texte.h"
#include "/home/pfr/pfr_code/texte/include/recherche_texte.h"
#include "/home/pfr/pfr_code/include/interface.h"

void main(void){
    int choix;
    printf("Voulez-vous créer l'environnement de travail?\n - A ne faire qu'une fois au début -\n Taper 1 si oui sinon 2\n");
    scanf("%d",&choix);
    if(choix==1){
        crea_dossiers();
    }
    interface();
}
