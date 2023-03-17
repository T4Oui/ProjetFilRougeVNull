#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "/home/pfr/pfr_code/texte/include/clean.h"
#include "/home/pfr/pfr_code/texte/include/tok.h"
#include "/home/pfr/pfr_code/texte/include/descripteur_Txt.h"
#include "/home/pfr/pfr_code/texte/include/pile_dynamique.h"
#include "/home/pfr/pfr_code/texte/include/indexation_texte.h"
#include "/home/pfr/pfr_code/texte/include/piles2.h"
#include "/home/pfr/pfr_code/texte/include/table_index.h"

#define CHEMIN_FICHIER_STOPWORD "/home/pfr/pfr_code/data/stop_words_french.txt"
#define CHEMIN_STOCKAGE_FICH_IDX "/home/pfr/pfr/texte/fich_textes"
#define CHEMIN_TRAITEMENT_FICH_IDX "/home/pfr/pfr_code/traitement"
#define CHEMIN_LISTE_FICHIER_IDX "/home/pfr/pfr_code/data/listeFichierTxt.txt"
#define CHEMIN_FICHIER_SOURCE "/home/pfr/pfr/texte/fich_textes/%s.xml"
#define CHEMIN_FICHIER_TOK_IDX "/home/pfr/pfr/texte/tok"


void indexation_texte(void){

    char fileName[256]={0};
    char pathFileSRC[256]={0};
    //char cheminListFich[256]={0};
    //char cheminFich[256]={0};
    
    recupListeFichierTxt();

    FILE * listeFichier = fopen(CHEMIN_LISTE_FICHIER_IDX,"r");
    
    if(listeFichier != NULL){
        while(fscanf(listeFichier,"%s",fileName)==1){
            nettoyage(fileName,CHEMIN_STOCKAGE_FICH_IDX ,CHEMIN_TRAITEMENT_FICH_IDX);
            filtrage(fileName,CHEMIN_TRAITEMENT_FICH_IDX);
        }
        redirCleanTok();
    }
    
    DESCRIPT_TXT descript;
    MotTable pMotTable = initM();
    int ident = 1;
    system("echo '' > /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt");
    system("echo '' > /home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt");
    system("echo '' > /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt");
    
    fseek(listeFichier,0,SEEK_SET);

    while(fscanf(listeFichier,"%s",fileName)==1){
        int ret = snprintf(pathFileSRC,sizeof(pathFileSRC),CHEMIN_FICHIER_SOURCE,fileName);
        if(ret<0){
            abort();
        }
        printf("\n%s",fileName);
        descript = crea_descript_txt(fileName,ident,CHEMIN_FICHIER_TOK_IDX);
        concatBaseDescript(descript);
        ajoutListeBaseTxt(pathFileSRC,ident);
        pMotTable = table(pMotTable,ident,fileName);
        ident ++;
    }
    aff(pMotTable);
    fclose(listeFichier);
}

// Créé un fichier avec la liste des textes dans le répertoire et supprime l'extension .xml du nom des fichier
void recupListeFichierTxt()
{
    system("ls /home/pfr/pfr/texte/fich_textes > /home/pfr/pfr_code/data/listeFichierTxt.txt");
    system("sed -i -e 's/.xml//g' /home/pfr/pfr_code/data/listeFichierTxt.txt");
}

//Redirection des fichier Clean et Tok dans le bon répertoire
void redirCleanTok(){
    system("cd /home/pfr/pfr_code/traitement/");
    system("mv /home/pfr/pfr_code/traitement/*.tok /home/pfr/pfr/texte/tok;mv /home/pfr/pfr_code/traitement/*.clean /home/pfr/pfr/texte/clean");
}

//Créer un descripteur texte .xml à partir du nom du fichier, de l'identifiant et du chemin vers le répertoire tok
DESCRIPT_TXT crea_descript_txt(char * fileName,int ident, char * cheminRepertoireTok){

    DESCRIPT_TXT descripteur;

    descripteur = initDescript();
    return descripteur = creerDescript(fileName,ident,cheminRepertoireTok);
}

void ajoutListeBaseTxt(char * pathFileSRC, int ident){

    char echoList[256]={0};
    if(ident<10){
        int ret = snprintf(echoList,sizeof(echoList),"echo 0%d %s >> /home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt",ident,pathFileSRC);
        if(ret<0){
            abort();
        }
        else system(echoList);
    }
    else{
        int ret = snprintf(echoList,sizeof(echoList),"echo %d %s >> /home/pfr/pfr/texte/descripteurs_textes/Liste_Base_Texte.txt",ident,pathFileSRC);
        if(ret<0){
            abort();
        }
        else system(echoList);
    }
}

int main(int argc, char * argv[]){
    indexation_texte();
}

void nettoyage(char *fileName, char * pathStockageFich, char * pathTraitement)
{
    //initialisation du chemin du fichier dans le répertoire de travail
    char pathFile[256]={0};
    int ret = snprintf(pathFile, sizeof(pathFile), "%s/%s",pathTraitement, fileName);
    if (ret < 0) {
        abort();
    }

    copieRepTravail(pathStockageFich, fileName, pathFile);
    enleverBalise(pathFile);
    changerMajMin(pathFile);
    supprNPremLig(3,pathFile);
    supprApostrophe(pathFile);
    supprChiffre(pathFile);
    supprPonctu(pathFile);
    supprTiret(pathFile);
    supprXml(pathFile);
}

// copier le fichier .xml du répertoire de stockage vers le répertoire de travail
void copieRepTravail(char * pathStockageFich, char *fileName, char * pathFile){

    char copieRepTravail[256] = {0};
    int ret = snprintf(copieRepTravail, sizeof(copieRepTravail), "cp %s/%s.xml %s.xml",pathStockageFich, fileName, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(copieRepTravail);
    }
}

// enlever les balises dans ls fichier .xml
void enleverBalise(char * pathFile){

    char enleverBalise[256] = {0};
    int ret = snprintf(enleverBalise, sizeof(enleverBalise), "sed -i -e 's/<[^>]*>//g' %s.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(enleverBalise);
    }
}

// Changer les majuscules en minuscules
void changerMajMin(char * pathFile){
    char changeMajMin[256] = {0};
    int ret = snprintf(changeMajMin, sizeof(changeMajMin), "cat %s.xml | tr A-Z a-z > %sV2.xml", pathFile, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(changeMajMin);
    }
}

// Supprimer les n première lignes (car lignes vides)
void supprNPremLig(int n, char * pathFile){
    char supprPremLig[256] = {0};
    int ret = snprintf(supprPremLig, sizeof(supprPremLig), "sed -i '1,%dd' %sV2.xml",n, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprPremLig);
    }
}

// suppression ' et "
void supprApostrophe(char * pathFile){
    char supprApostrophe[256] = {0}; 
    system("chmod +x /home/pfr/pfr_code/texte/src/remove_apostrophe.sh");
    int ret = snprintf(supprApostrophe, sizeof(supprApostrophe), "/home/pfr/pfr_code/texte/src/remove_apostrophe.sh %sV2.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprApostrophe);
    }
}

// Supprimer les chiffres
void supprChiffre(char * pathFile){
    char supprChiffre[256] = {0};
    int ret = snprintf(supprChiffre, sizeof(supprChiffre), "sed -i -e 's/[0-9]//g' %sV2.xml", pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprChiffre);
    }
}

// Remplace de la ponctuation et des symboles (hors -) par des " "
void supprPonctu(char * pathFile){
    char supprPonctu[256] = {0};
    int ret = snprintf(supprPonctu, sizeof(supprPonctu), "sed -i -e 's/[.,;:?!()%%_<>/$€]/ /g' %sV2.xml", pathFile);
    if (ret < 0)
    {
        abort();
    }
    else
        system(supprPonctu);
}

// Suppression des "-" et création du fichier .clean
void supprTiret(char * pathFile){
    char supprTiret[256] = {0};
    int ret = snprintf(supprTiret, sizeof(supprTiret), "sed 's/-/ /g' %sV2.xml > %s.clean", pathFile, pathFile);
    if (ret < 0)
    {
        abort();
    }
    else
        system(supprTiret);
}

// Suppression des fichiers .xml
void supprXml(char * pathFile){
    char supprXmlV2[256] = {0};
    int ret = snprintf(supprXmlV2, sizeof(supprXmlV2), "rm %sV2.xml;rm %s.xml ", pathFile, pathFile);
    if (ret < 0) {
        abort();
    }
    else{ 
        system(supprXmlV2);
    }
}

void filtrage(char *fileName, char * pathTraitement)
{
    char mot[256] = {0};
    char pathChaine[256] = {0};
    char pathFile[256] = {0};
    int ret;
    int test;

    ret = snprintf(pathFile, sizeof(pathFile), "%s/%s",pathTraitement, fileName);
    if (ret < 0) {
        abort();
    }

    ret = snprintf(pathChaine, sizeof(pathChaine), "%s.clean", pathFile);
    if (ret < 0) {
        abort();
    }

    creerFichTok(pathFile);

    FILE *fichier_clean = fopen(pathChaine, "r");

    if (fichier_clean != NULL)
    {
        while (fscanf(fichier_clean, "%s", mot) == 1)
        {
            enleverStopWord(mot,pathFile);
        }
    }
    fclose(fichier_clean);
}

void enleverStopWord(char * mot, char * pathFile){

    char stopWord[256] = {0};
    char ajoutMotTok[256] = {0};
    FILE *fichierStopWord = fopen(CHEMIN_FICHIER_STOPWORD, "r");
    int is_stopword = 0;

    //lecture du stopword dans le fichier stop_words_french.txt
    while (fscanf(fichierStopWord,"%s", stopWord) == 1)
    {
        if ((strcmp(mot, stopWord) == 0) || (strlen(mot) <=2))
        {
            is_stopword = 1;
            break;
        }
    }

    //ajout du mot dans le .tok si ce n'est pas un stopword
    if (is_stopword == 0)
    {
        int ret = snprintf(ajoutMotTok, sizeof(ajoutMotTok), "echo %s >> %s.tok", mot, pathFile);
        if (ret < 0)
        {
            abort();
        }
        else system(ajoutMotTok);
    }
    fclose(fichierStopWord);    
}

// On vide ou créé le fichier .tok à partir du nom du fichier
void creerFichTok(char * pathFile){

    char creerFichTok[256]={0};
    int ret = snprintf(creerFichTok, sizeof(creerFichTok), "echo '' > %s.tok", pathFile);
    if (ret < 0) {
        abort();
    }
    else system(creerFichTok);
}

/*Pile1*/

Table initT() { return NULL; }

Table addT(Table p, int fich, int nb)
{
    Table paux = (Table)malloc(sizeof(Cel1));
    paux->fich = fich;
    paux->nb = nb;
    paux->suiv = p;
    return paux;
}

void affT(Table p)
{
    char chaine[256] = {0};
    while (p != NULL)
    {
        // printf("    %s %d\n", p->fich,p->nb);
        snprintf(chaine, 256, "echo '%d %d'>> /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt", p->fich, p->nb);
        system(chaine);
        p = p->suiv;
    }
}

/*Pile2*/

MotTable initM() { return NULL; }

MotTable addM(MotTable p, char *mot)
{
    MotTable paux = (MotTable)malloc(sizeof(Cel2));
    snprintf(paux->mot, sizeof(paux->mot), "%s", mot);
    paux->nbMot=0;
    paux->table = NULL;
    paux->motTableSuiv = p;
    return paux;
}

MotTable add(MotTable p, int nb, char *mot, int fich)
{
    int nb_min;
    FILE *config = fopen("/home/pfr/pfr_code/config.txt", "r");
    fscanf(config, "%d", &nb_min);
    fclose(config);

    MotTable paux = p;
    MotTable posC2 = NULL;
    if (nb >= nb_min)
    {
        while (paux != NULL)
        {
            if (strcmp(paux->mot, mot) == 0)
                posC2 = paux;
            paux = paux->motTableSuiv;
        }
        if (posC2 == NULL)
        {
            p = addM(p, mot);
            p->table = addT(p->table, fich, nb);
            p->nbMot++;
        }
        else
        {
            if (posC2->table->fich != fich)
            {
                posC2->table = addT(posC2->table, fich, nb);
                posC2->nbMot++;
            }
        }
    }
    return p;
}

void aff(MotTable p)
{
    char chaine[256] = {0};
    while (p != NULL)
    {
        // printf("%s\n",p->mot);
        snprintf(chaine, 256, "echo '%s' >> /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt", p->mot);
        system(chaine);
        snprintf(chaine, 256, "echo '%d' >> /home/pfr/pfr/texte/descripteurs_textes/Table_Index_Texte.txt", p->nbMot);
        system(chaine);
        if (p->table != NULL)
        {
            affT(p->table);
        }
        p = p->motTableSuiv;
    }
}

//initialise un mot
MOT initMot(){
    MOT mot;
    mot.ident = 0;
    mot.nb_occur = 0;
    mot.mot_suiv = NULL;
    return mot;
}

//ajoute les caractéristique d'un mot d'un fichier.tok
MOT addMot(char * motTxt, int ident,char * fileName){
    MOT mot;
    mot.ident = ident;
    snprintf(mot.mot,sizeof(mot.mot),"%s",motTxt);
    mot.nb_occur = chercheNbOccur(motTxt,fileName);
    mot.mot_suiv = NULL;
    return mot;
}

//Créé une pile de mot relatif à un fichier et met à jour le paramètre nbMotDiff du fichier.tok
void creerPileMot(PILE * pileMot , char * fileName, int * nbMotDiff, int ident, char * cheminRepertoireTok){
    char recupTokUniq[256]={0};   
    char motRecup[256]={0};
    char pathFile[256]={0};
    *pileMot = init_PILE();
    MOT mot = initMot();
    *nbMotDiff = 0;
    int nb_occ_min = 0;

    //Création  du fichier CloneTok avec une seule occurence pas mot du fichier .tok
    snprintf(recupTokUniq,sizeof(recupTokUniq),"sort %s/%s.tok | uniq > /home/pfr/pfr_code/traitement/CloneTok/%sClone.tok",cheminRepertoireTok,fileName,fileName);
    system(recupTokUniq);

    //ouverture du fichier Clone.tok
    snprintf(pathFile,sizeof(pathFile),"/home/pfr/pfr_code/traitement/CloneTok/%sClone.tok",fileName);
    FILE * fichier_CloneTok = fopen(pathFile,"r");

    //récupération du nombre d'occurrence minimum pour qu'un mot soit ajouter au descripteur
    FILE * fichier_config = fopen("/home/pfr/pfr_code/config.txt","r");
    fscanf(fichier_config,"%d",&nb_occ_min);
    fclose(fichier_config);
    
    //ajout des mots au descripteur (création de la pile de mot) 
    while(fscanf(fichier_CloneTok,"%s",motRecup)==1){
        mot = addMot(motRecup,ident,fileName);
        if((mot.nb_occur >= nb_occ_min)&&(strlen(mot.mot)>2)){
            *pileMot = emPILE(*pileMot,mot);
        }
    }
    //comptage du nombre de mot unique
    *nbMotDiff = comptageNbMot(pathFile);

    fclose(fichier_CloneTok);
}

//initialise le descripteur avec des valeurs par défaut
DESCRIPT_TXT initDescript(){
    DESCRIPT_TXT descript;
    descript.ident = 0;
    descript.pile_mot = init_PILE();
    descript.nb_mot_diff = 0;
    descript.taille_txt = 0;
    return descript;
}

//créé le descripteur d'un fichier.tok à partir du chemin du fichier source .xml (identifiant) et du fichier tok accessible dans l'arborescence de répertoires
DESCRIPT_TXT creerDescript(char * fileName, int ident,char * cheminRepertoireTok){

    DESCRIPT_TXT descript = initDescript();
    char pathFile[256]={0};
    //char motRecup[256]={0};

    descript.ident = ident;
    creerPileMot(&descript.pile_mot,fileName,&(descript.nb_mot_diff),ident,cheminRepertoireTok);
    snprintf(pathFile,sizeof(pathFile),"%s/%s.tok",cheminRepertoireTok,fileName);
    //Détermination de la taille du texte en nombre de mot
    descript.taille_txt= comptageNbMot(pathFile);
    return descript;
}

int chercheNbOccur(char * mot, char * fileName){

    char cptnbMot[256]={0};
    int nb_occurrence = 0;

    //comptage du nombre d'occurrence d'un mot dans le fichier passé en paramètre
    snprintf(cptnbMot, sizeof(cptnbMot), "grep -ow '%s' /home/pfr/pfr/texte/tok/%s.tok | wc -l > /home/pfr/pfr_code/data/nbOccur.txt",mot,fileName);
    system(cptnbMot);

    //récupération du nombre d'occurrence du mot dans le fichier nbOccur.txt
    FILE * nbOccur = fopen("/home/pfr/pfr_code/data/nbOccur.txt","r");
    fscanf(nbOccur,"%d",&nb_occurrence);
    fclose(nbOccur);
    return nb_occurrence;
}

//ajout du descripteur au fichier bas descripteur texte
void concatBaseDescript(DESCRIPT_TXT descript){

    //ajout de l'identifiant
    char ajoutIdentDescript[256]={0};
    snprintf(ajoutIdentDescript,sizeof(ajoutIdentDescript),"echo %d >> /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.ident);
    system(ajoutIdentDescript);

    //ajout des mots
    char ajoutMotDescript[256]={0};
    MOT mot = initMot();
    while(!PILE_estVide(descript.pile_mot)){
        descript.pile_mot=dePILE(descript.pile_mot, &mot);
        snprintf(ajoutMotDescript,sizeof(ajoutMotDescript),"echo %d %s %d >> /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",mot.ident,mot.mot,mot.nb_occur);
        system(ajoutMotDescript);
    }
    //ajout du nombre de mot différents
    char ajoutNbMotDiffDescript[256]={0};
    snprintf(ajoutNbMotDiffDescript,sizeof(ajoutNbMotDiffDescript),"echo %d >> /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.nb_mot_diff);
    system(ajoutNbMotDiffDescript);

    //ajout de la taille du texte en nombre de mot
    char ajoutNbMotDescript[256]={0};
    snprintf(ajoutNbMotDescript,sizeof(ajoutNbMotDescript),"echo %d >> /home/pfr/pfr/texte/descripteurs_textes/Base_Descripteur_Texte.txt",descript.taille_txt);
    system(ajoutNbMotDescript);
} 

int comptageNbMot(char * pathFile){

    int ctpMot=0;
    char comptageMot[256]={0};
    //comptage du nombre de mot du fichier passer en paramètre
    snprintf(comptageMot,sizeof(comptageMot),"wc -w %s > /home/pfr/pfr_code/data/comptage.txt",pathFile);
    system(comptageMot);
    
    //récupération du nombre de mot dans le fichier comptage.txt
    FILE * comptage = fopen("/home/pfr/pfr_code/data/comptage.txt","r");
    fscanf(comptage,"%d",&ctpMot);
    fclose(comptage);
    return ctpMot;
}

PILE init_PILE(){
	PILE p = NULL;
	return p;
}

void affiche_PILE(PILE p){
	
	while(p != NULL){
		printf("\n ident = %d,",p->ident);
    	printf("mot = %s,",p->mot);
		printf(" nb_occur = %d",p->nb_occur);
		p=p->mot_suiv;
	}
}

int PILE_estVide(PILE p){

	return (p == NULL);
}
//Empile un mot dans la pile de mot
PILE emPILE(PILE p, MOT mot){
	
	PILE paux =(PILE)malloc(sizeof(struct MOT));
	if(!PILE_estVide(paux)){
		paux->ident = mot.ident;
		snprintf(paux->mot,sizeof(paux->mot),"%s",mot.mot);
		paux->nb_occur = mot.nb_occur;
		paux->mot_suiv = p;
	}
	return paux;
}

PILE dePILE(PILE p, MOT * mot){

	PILE paux=p;
	if(!PILE_estVide(p)) {
		mot->ident = paux->ident;
		snprintf(mot->mot,sizeof(mot->mot),"%s",paux->mot);
		mot->nb_occur = paux->nb_occur;
		p = p->mot_suiv;
		free(paux);
	}
	return p;
}

MotTable table(MotTable p, int ident, char *fichier)
{
    char chaine1[256] = {0};
    char mot[256];
    int ret = snprintf(chaine1, 256, "/home/pfr/pfr/texte/tok/%s.tok", fichier);
    if (ret < 0)
    {
        abort();
    }
    FILE *fich = fopen(chaine1, "r");
    while (fscanf(fich, "%s", mot) == 1)
    {
        p = add(p, chercheNbOccur(mot, fichier), mot, ident);
    }
    fclose(fich);
    return p;
}