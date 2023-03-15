#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interface.h"

#define mdp "feur"

// ouvrir fichier image : display <image>
// ouvrir fichier txt : xdg-open <filename>

void affMP()
{
    printf("\n\n\n    ** Menu Principal **\nTaper 1: mode Utilisateur\nTaper 2: mode Administrateur\nTaper 9: quitter\n");
}

void affUtil()
{
    printf("\n  ** Mode Utilisateur **\nQue voulez-vous chercher?\n1: Un texte\n2: Une image\n3: Un son\n0: revenir au menu principal\n9: quitter\n");
}

void affrechText()
{
    printf("\n  ** Recherche Texte **\n1: par mot clef\n2: par ressemblance avec un autre fichier\n0: revenir au menu principal\n");
}

void affrechImag()
{
    printf("\n  ** Recherche Image **\n1: donner les composantes RGB\n2: ressemblance avec une autre image\n0: revenir au menu principal\n");
}

void affrechSon()
{
    printf("\n  ** Recherche Son **\nTaper le chemin du son que vous voulez comparer:\n");
}

void affrechTextMotClef()
{
    printf("\n  ** Recherche Texte par Mot Clef **\nTaper le mot clef:\n");
}

void affrechTextText()
{
    printf("\n  ** Recherche Texte par ressemblance **\nTaper le chemin du texte que vous voulez comprarer (sans le .xml):\n");
}

void affrechImagRGB()
{
    printf("\n  ** Recherche Image par composantes RGB **\n");
}

void affrechImagImag()
{
    printf("\n  ** Recherche Image par ressemblance avec une image **\n1: une image en noir et blanc\n2: une image couleur\n");
}

void affrechImagImagNB()
{
    printf("\n  ** Recherche Image par ressemblance avec une image NetB **\nTaper le chemin de l'image que vous voulez comparer:\n");
}

void affrechImagImagCoul()
{
    printf("\n  ** Recherche Image par ressemblance avec une image Couleur **\nTaper le chemin de l'image que vous voulez comparer:\n");
}

void affresultMotClef(char *mot)
{
    printf("\n  ** Resultats trouvés pour la recherche '%s' **\n", mot);
    rech_MC(mot);
    //printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affresultTexte(char *chemin)
{
    int nbLig;
    printf("\n  ** Resultats trouvés pour la comparaison avec un fichier **\n");
    nbLig = comptageNbLigne("/home/pfr/pfr_code/data/listeFichierTxt.txt");
    recherche_comparaison_texte(chemin, nbLig);
    
}

void affresultRGB(int R, int G, int B)
{
    printf("\n  ** Resultats trouvés pour la recherche grâce aux composantes R:'%d', G:'%d', B:'%d' **", R, G, B);
   
}

void affresultImageNB(char *fichier_retour, int image, float pourcentage)
{
    printf("\n  ** Resultats trouvés pour la comparaison avec une image NetB **\n");
    recherchenoiretblanc(image, pourcentage, fichier_retour);
    //interface();
    //printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affresultImageCoul(char *fichier_retour, int image, float pourcentage)
{
    printf("\n  ** Resultats trouvés pour la comparaison avec une image Couleur **\n");
    recherchecouleur(image, pourcentage, fichier_retour);
    //interface();
    //printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affresultSon()
{
    printf("\n  ** Resultats trouvés pour la comparaison avec un fichier **\n");
    // recherche son
    printf("\n Taper 1 pour ouvrir le premier fichier\n");
}

void affAdm()
{
    printf("\n  ** Mode Administrateur **\n       Mot de passe?\n");
}

void affmdp()
{
    printf("\n  ** Mode Administrateur **\nMot de passe erroné    Mot de passe?\n");
}

void affmodeAdm()
{
    printf("\n  ** Mode Administrateur **\n1: modifier les configurations\n2: visualiser le contenu des descripteurs\n3: effectuer une recherche\n4: faire l'indexation\n0: revenir au menu principal\n9: quitter\n");
}

void affconfig()
{
    int nb_lig;
    int nb_modif;
    printf("\n  ** Modifier les configurations **\n\n");
    system("cat /home/pfr/pfr_code/config.txt");
    printf("\n\n Que voulez vous modifier ?\nrentrer le numéro de ligne (début à 0) puis la valeur à mettre à la place\n");
    scanf("%d", &nb_lig);
    scanf("%d", &nb_modif);
    char carac[50];
    int nb;
    char chaine[200];
    int i=0;
    FILE * config = fopen("/home/pfr/pfr_code/config.txt","r+");
    system("echo '' > /home/pfr/pfr_code/data/modif_config.txt");
    while(fscanf(config,"%d",&nb)==1){
        fscanf(config,"%s",carac);
        if(i==nb_lig){
            nb=nb_modif;
        }
        snprintf(chaine,200,"echo '%d %s' >> /home/pfr/pfr_code/data/modif_config.txt",nb,carac);
        system(chaine);
        i++;
    }
    system("echo '' > /home/pfr/pfr_code/config.txt");
    system("cat /home/pfr/pfr_code/data/modif_config.txt > /home/pfr/pfr_code/config.txt");
    system("sed -i '1d' /home/pfr/pfr_code/config.txt");
    fclose(config);

    printf("\n  ** fichier mofifié **\n");
    system("cat /home/pfr/pfr_code/config.txt ");
}

void affvisudescripteurs()
{
    printf("\n  ** Visualiser le contenu des descripteurs **\n1: texte\n2: image\n3: son\n0: revenir au mode administrateur\n");
}

void affvisudescText()
{
    /* printf("\n  ** Descripteurs texte **\n");
    printf("\n**** Descripteurs utiles pour la comparaison ****\n");
    system("cat /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt");
    printf("\n**** Descripteurs utiles pour la recherche mot clef ****\n");
    system("cat /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt");
    printf("\n**** Identificateur des fichiers ****\n");
    system("cat /home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt"); */
    system("gedit /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt &");
    system("gedit /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt &");
    system("gedit /home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt &");
}

void affvisudescImag()
{
    /* printf("\n  ** Descripteurs image **\n");
    printf("\n**** Descripteurs pour les fichiers Noir et Blanc ****\n");
    system("cat /home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt");
    printf("\n**** Identificateur des fichiers Noir et Blanc ****\n");
    system("cat /home/pfr/pfr/image/descripteurs_images/bas_image_NB.txt");
    printf("\n**** Descripteurs pour les fichiers Couleur ****\n");
    system("cat /home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt");
    printf("\n**** Identificateur des fichiers Couleur****\n");
    system("cat /home/pfr/pfr/image/descripteurs_images/bas_image_couleur.txt"); */
    system("gedit /home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt &");
    system("gedit /home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt &");
    system("gedit /home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt &");
    system("gedit /home/pfr/pfr/image/descripteurs_images/base_image_NB.txt &");
}

void affvisudescSon()
{
    printf("\n  ** Descripteurs son **\n");
    // afficher descripteurs
    //system("gedit /home/pfr/pfr/son/descripteurs_sons/basetxt &");
    system("gedit /home/pfr/pfr/son/descripteurs_sons/liste.txt &");
    system("gedit /home/pfr/pfr/son/descripteurs_sons/descripteur_corpus_fi.bin.txt &");
}

void indexation()
{
    char chemin[250];
    char verifChaine[256];
    // supprimer les fichiers avant de faire l'indexation //A FAIRE
    do
    {
        printf("\n  ** Indexation **\n Saisir le chemin des fichiers que vous voulez indexer:\n");
        scanf("%s", chemin);
        int ret = snprintf(verifChaine,sizeof(verifChaine),"find %s > /home/pfr/pfr_code/data/erreur.txt 2>&1",chemin);
        if(ret<0){
            abort();
        }
    }while(system(verifChaine) !=0);
    system("rm /home/pfr/pfr/texte/fich_textes/*.xml > /home/pfr/pfr_code/data/testFind.txt 2>&1");
    tri_fich(chemin);
    // indexation texte
    printf("\n***** indexation texte *****\n");
    indexation_texte(); 
    // indexation image
    printf("\n***** indexation image *****\n");
    indexation_image();
    // indexation son
    printf("\n***** indexation son *****\n");
    indexation_son();
}

void modeUtil()
{
    int choix;
    affUtil(); // menu utilisateur
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        affrechText(); // menu recherche texte
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            char mot[256];
            affrechTextMotClef(); // menu recherche texte - mot clef
            scanf("%s", mot);
            affresultMotClef(mot);
            open_fich();
            printf("\n Taper sur une touche pour retourner au menu principal\n");
            scanf("%d", &choix);
            interface();
            break;
        case 2:
            char chemin[150];
            char chaine[256];
            do{
                affrechTextText(); // menu recherche texte - texte
                scanf("%s", chemin);
                snprintf(chaine, 256, "cp %s.xml /home/pfr/pfr/texte/recherche_texte > /home/pfr/pfr_code/data/erreur.txt 2>&1 ", chemin);
            }while(system(chaine)!= 0);
            affresultTexte(chemin);
            printf("\n Taper sur un chiffre pour retourner au menu principal\n");
            scanf("%d", &choix);
            interface();
            // open fichier
            break;
        case 0:
            interface();
            break;
        default:
            affUtil();
            break;
        }
        break;
    case 2:
        affrechImag();
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            int R, G, B;
            affrechImagRGB(); // menu recherche image - RGB
            printf("Composante R?   ");
            scanf("%d", &R);
            printf("Composante G?   ");
            scanf("%d", &G);
            printf("Composante B?   ");
            scanf("%d", &B);
            affresultRGB(R, G, B);
            scanf("%d", &choix);
            // open fichier
            break;
        case 2:
            char chemin[150];
            char chaine[256];
            int *descripteur;
            float pourcentage;
            FILE *base;
            int id;
            char nom[150];
            char fich[256]={0};
            affrechImagImag(); // menu recherche image - image
            scanf("%d", &choix);
            switch (choix)
            {
            case 1:
                affrechImagImagNB(); // menu recherche image - image - NB
                scanf("%s", chemin);
                snprintf(chaine, 256, "cp %s /home/pfr/pfr/image/recherche_image", chemin);
                system(chaine);                                              // chemin + nom_fichier
                printf("\nQuel est le nom du fichier (sans le chemin) ?\n"); // nom_fichier
                scanf("%s", chemin);
                descripteur = indexation_recherche(chemin);
                // demander pourcentage
                printf("\nPourcentage minimum de ressemblance ? (entre 0 et 100)\n");
                scanf("%f", &pourcentage);

                base = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_NB.txt", "r");
                while (fscanf(base, "%d", &id) == 1)
                {
                    fscanf(base, "%s", nom);
                    if (strcmp(nom, chemin) == 0)
                    {
                        printf("%d", id);
                        break;
                    }
                }
                fclose(base);
                affresultImageNB(fich, id, pourcentage);
                open_image_nb(fich);
                printf("\n Taper sur une touche pour retourner au menu principal\n");
                scanf("%d", &choix);
                interface();
                break;

            case 2:
                affrechImagImagCoul(); // menu recherche image - image - couleur
                scanf("%s", chemin);
                snprintf(chaine, 256, "cp %s /home/pfr/pfr/image/recherche_image", chemin);
                system(chaine); // chemin + nom_fichier

                printf("\nQuel est le nom du fichier (sans le chemin) ?\n"); // nom_fichier
                scanf("%s", chemin);
                descripteur = indexation_recherche(chemin);

                // demander pourcentage
                printf("\nPourcentage minimum de ressemblance ? (entre 0 et 100)\n");
                scanf("%f", &pourcentage);

                base = fopen("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt", "r");
                while (fscanf(base, "%d", &id) == 1)
                {
                    fscanf(base, "%s", nom);
                    if (strcmp(nom, chemin) == 0)
                    {
                        break;
                    }
                }
                fclose(base);

                affresultImageCoul(fich, id, pourcentage);
                open_image_coul(fich);
                printf("\n Taper sur une touche pour retourner au menu principal\n");
                scanf("%d", &choix);
                interface();
                break;
            default:
                affUtil();
                break;
            }
            break;
        case 0:
            interface();
            break;
        default:
        affUtil();
            break;
        }
        break;
    case 3:
        char chemin[150];
        char chaine[256];
        affrechSon();
        scanf("%s", chemin);
        snprintf(chaine, 256, "cp %s /home/pfr/pfr/son/recherche_son", chemin);
        system(chaine);
        affresultSon();
        scanf("%d", &choix);
        // open fichier
        break;
    case 0:
        interface();
        break;
    case 9:
        break;
    default:
        affUtil();
        break;
    }
}

void modeAdm()
{
    int choix;
    affmodeAdm();
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        affconfig();
        printf("\n Taper sur une touche pour retourner au menu principal\n");
        scanf("%d", &choix);
        modeAdm();
        break;
    case 2:
        affvisudescripteurs();
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            affvisudescText();
            printf("\n Taper sur une touche pour retourner au menu principal\n");
            scanf("%d", &choix);
            modeAdm();
            break;
        case 2:
            affvisudescImag();
            printf("\n Taper sur une touche pour retourner au menu principal\n");
            scanf("%d", &choix);
            modeAdm();
            break;
        case 3:
            affvisudescSon();
            printf("\n Taper sur une touche pour retourner au menu principal\n");
            scanf("%d", &choix);
            modeAdm();
            break;
        case 0:
            modeAdm();
            break;
        default:
            modeAdm();
            break;
        }
        break;
    case 3:
        modeUtil();
        break;
    case 4:
        indexation();
        modeAdm();
        break;
    case 0:
        interface();
        break;
    case 9:
        break;
    default:
        modeAdm();
        break;
    }
}

void interface()
{
    int choix ;
    affMP(); // menu principal
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        modeUtil();
        break;
    case 2:
        char m[256];
        affAdm(); // gestion du mot de passe
        scanf("%s", m);
        if (m == 0)
        {
            interface();
        }
        while (strcmp(m, mdp) != 0)
        {
            affmdp();
            scanf("%s", m);
        }
        modeAdm();
        break;
    case 9:
        break;
    default:
        interface();
        break;
    }
}