#ifndef RECHERCHE_IMAGE_H
#define RECHERCHE_IMAGE_H

typedef struct TAB{
    int identifiant;
    int nb_valeur;
    int* T;
    float pourcentage;
    int total;

}TAB;

typedef struct STRUCTPOURC{
    int identifiant;
    float pourcentage;
    char fichier[20];

}STRUCTPOURC;



float pourcentage(float partie,int total);
int intersection (int* tab1, int* tab2 ,int taille);
int configurationR ( FILE* fichier);
int tab_taille_couleur(int config, int noiroublanc);
void remplissagestructure (TAB* couleur, int bit_quantification,FILE* base_descripteur_image, int noiroublanc);
int compterlignes(FILE* fichier);
void remplissagetab (TAB* tableau1,int nblignes, int noiroublanc);
void affichagetab (TAB*tableau, int tailletableau);
int couleurougris(TAB* descripteur);
int fichier_a_traiter(TAB* descripteur,int nblignes);
void comparaison_couleur(TAB* descripteur, int identifiant, int nblignes);
void comparaison_noirblanc(FILE* fichier);
void malloc_structure(TAB* tab,int nblignes);
void total(TAB* descripteur,int tabtaillemax);
void free_structure(TAB* tab,int nblignes);
void afficher_resultat_noiroublanc(STRUCTPOURC* tableau2, int nblignes);
void afficher_resultat_couleur(STRUCTPOURC* tableau2, int nblignes);
void afficher_pourcentage(STRUCTPOURC* tableau2, int nblignes, float pourcentagemini);
void tri (STRUCTPOURC* tableau2, int nblignes);
void remplissagetabpourcent(STRUCTPOURC* tableau2, TAB* tableau1, int nblignes);
int nbdedescripteurs(int noiroublanc);
void recherchenoiretblanc(int fichierrecherche, float pourcentagemini, char* fichier);
void recherchecouleur(int fichierrecherche,float pourcentagemini,char* fichier);
TAB* init_tableau(TAB* tableau1,int nbdescripteurs);
void free_structure(TAB* tab,int nbdescripteurs);
void recupfichier_couleur (STRUCTPOURC* tab, int nbdescripteurs);
void recupfichier_noiroublanc (STRUCTPOURC* tab,int nbdescripteurs);
void open_image_coul(char * fichier);
void open_image_nb(char * fichier);
int comptageNbLigne(char * pathFile);



//void tri (int tabtaillemax,STRUCTPOURC* tabpourcent);










#endif