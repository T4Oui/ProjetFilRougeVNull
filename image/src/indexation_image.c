#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Ouvrir le fichier avec le mode qui le prend en paramètre
FILE* openFile( const char * nomFichier , const char * m ) 
{
  FILE* file = fopen ( nomFichier , m) ; 
  if (file == NULL ) //Vérification si le fichier est bien ouvert ou non
  { 
    printf ( "error opening file ") ; 
  }
  return file ; 
}


// Fonction quantification qui prend en paramètre un tableau {R, V, B} si l'image est en couleur sinon {pixel, 0,0} et renvoie la nouvelle valeur de pixel
int quantification (int tab[] , int b , int n ) 
{ 

  int t[8] ;  
  int nouPix = 0 ; 
  int Nbr = (n *b)-1 ; //le nombre de bits nécessaire
  int i = 0;  //compteur
  while (( i<3) && (Nbr >=0 ))
   { 
    int a = tab[i] ; 
    for (int j = 0 ; j<8 ; j ++) //codage décimal binaire d'un pixel 
    {
       t[j] = a % 2 ;
       a = a / 2;
    } 
    if (n ==2)
    { 
       nouPix = nouPix + (t[7] * pow(2 , Nbr) )+ (t[6] * pow(2 , Nbr-1)) ;
       Nbr = Nbr - 2 ;
    } 
    else if (n ==3)
    { 
      nouPix = nouPix + (t[7] * pow(2 , Nbr) )+ (t[6] * pow(2 , Nbr-1)) + (t[5] * pow(2 , Nbr-2)) ;
      Nbr = Nbr - 3 ;
    } 
    i++ ; 
    }
  return ( nouPix) ; 
} 

//Parcourir le fichier image .txt, appeler la fonction quantification pour chaque pixel et retourne une matrice contenant tous les nouveaux pixels
 int ** pretraitement_image ( const char* fichier , int * ptrNBLIG , int * ptrNBCOL, int * ptrB  , int n)  
{ 
  char chaine[256] = {0} ; 
  int ret = snprintf ( chaine , 256 ,"/home/pfr/pfr/image/fich_images/txt/%s" , fichier ) ;
  if ( ret < 0 )
       abort(); 
    FILE* f = openFile( chaine , "r" ); //ouvrir le fichier avec le mode lire
   
    fscanf(f,"%d" , ptrNBLIG);  // nombre de ligne 
    
    fscanf(f,"%d" , ptrNBCOL ); // nombre de colonne

    fscanf(f,"%d", ptrB);   // nombre de composantes
    int ** APQ = malloc( (*ptrNBLIG)*sizeof(int*) );

    if ( APQ == NULL )
    { 
     printf ("erreur ") ; 
     exit(1); 
    }
    int tab[3];
    if ( (*ptrB) !=3 ) // image N/B
    { 
      for ( int a =0 ; a<*ptrNBLIG ; a++ )
     {  
        APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
        for (int b=0; b< (*ptrNBCOL); b++ ) 
            {  fscanf(f,"%d", &tab[0]); 
              tab[1] = 0 ;
              tab[2] = 0 ;
               APQ[a][b]= quantification ( tab , *ptrB , n) ; // tab = {pixel , 0 ,0}
               }
               } }
    else  // image en couleur 
      { int taille = (*ptrNBLIG) *(*ptrNBCOL) ;
        int rouge[taille] ; 
        int vert [taille] ; 
        int bleu [taille] ; 
        int r =0 ;
        int v =0 ;
        int bl=0 ;
        for ( int i = 0 ;i<3 ;i++)
        {
          for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
          {  
           APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
           for (int b=0; b< (*ptrNBCOL); b++ ) 
           { 
              if (i==0) 
              { 
                  fscanf(f,"%d", &rouge[r]); //tableau qui contient tous les composants rouges
                   r++ ; 
              }
              else if (i==1)
              { 
                  fscanf(f,"%d", &vert[v]); //tableau qui contient tous les composants verts
                   v++ ;
              }
              else 
              { 
                  fscanf(f,"%d", &bleu[bl]); //tableau qui contient tous les composants bleus
                   bl++ ; 
              }
           }
          }
        }
        int t =0 ; 

        for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
            for (int b=0; b< (*ptrNBCOL); b++ ) 
                {
                    tab [0] = rouge[t] ; 
                    tab[1] = vert [t];
                    tab[2] = bleu[t]; 
                    APQ[a][b]= quantification ( tab , *ptrB , n) ; // tab = { composant_rouge, composant_vert, composant_bleu}
                    t++;
                    }
        }
        
        fclose(f) ;
    return ( APQ ) ;  
      }
// Fonction à utiliser dans la fonction indexation_recherche qui effectue le même traitement que la fonction pretraitement_image mais avec un autre chemin de fichier
int ** pretraitement_recherche ( const char* fichier , int * ptrNBLIG , int * ptrNBCOL, int * ptrB  , int n) 
{ 
  char chaine[256] = {0} ; 
  int ret = snprintf ( chaine , 256 ,"/home/pfr/pfr/image/recherche_image/%s" , fichier ) ;
  if ( ret < 0 )
       abort(); 
    FILE* f = openFile( chaine , "r" );  
   
    fscanf(f,"%d" , ptrNBLIG);
    
    fscanf(f,"%d" , ptrNBCOL );

    fscanf(f,"%d", ptrB);  
    int ** APQ = malloc( (*ptrNBLIG)*sizeof(int*) );

    if ( APQ == NULL )
    { 
      printf ("erreur ") ; 
     exit(1); }

    int tab[3];
    if ( (*ptrB) !=3 )
    { 
      for ( int a =0 ; a<*ptrNBLIG ; a++ )
     {  
        APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
        for (int b=0; b< (*ptrNBCOL); b++ ) 
            {  fscanf(f,"%d", &tab[0]); 
              tab[1] = 0 ;
              tab[2] = 0 ;
               APQ[a][b]= quantification ( tab , *ptrB , n) ;
               }
               } }
    else 
      {  int taille = (*ptrNBLIG) *(*ptrNBCOL) ;
         int rouge[taille] ;
        int vert [taille] ; 
        int bleu [taille] ; 
        int r =0 ;
        int v =0 ;
        int bl=0 ;
        for ( int i = 0 ;i<3 ;i++)
          {
            for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
         {  
           APQ[a] = malloc( (*ptrNBCOL)*sizeof(int) );
           for (int b=0; b< (*ptrNBCOL); b++ ) 
           { 
              if (i==0){ 
                  fscanf(f,"%d", &rouge[r]); 
                   r++ ; }
              else if (i==1){ 
                  fscanf(f,"%d", &vert[v]); 
                   v++ ; }
              else { 
                  fscanf(f,"%d", &bleu[bl]); 
                   bl++ ; }
           }
         }
        }
        int t =0 ; 
        for ( int a =0 ; a<(*ptrNBLIG) ; a++ )
            for (int b=0; b< (*ptrNBCOL); b++ ) 
                {
                    tab [0] = rouge[t] ; 
                    tab[1] = vert [t];
                    tab[2] = bleu[t]; 
                    APQ[a][b]= quantification ( tab , *ptrB , n) ;
                    t++;
                    }
        }
        
        fclose(f) ;
    return ( APQ ) ;  
      }


// Calculer nombre d'occurrence d'un pixel dans la matrice
int histogramme ( int ** matrice , int pixel , int * ptrNBLIG , int * ptrNBCOL)  
{
     
 int acc = 0  ;
 for (int i = 0 ;i < *ptrNBLIG ; i++ )
       for ( int j =0 ; j < *ptrNBCOL ; j++)
            if (matrice[i][j] ==  pixel)
                 acc++ ;

 return acc ; 
}

//Le mise à jour des fichiers base_descripteur_image.txt et base_image.txt pour chaque nouveau descripteur
void mise_a_jour_base_image (  FILE* LBI , FILE* BDI, const char* f ,int*  descripteur , int n , int* d ) 
         {  int c = pow ( 2 , ((*d)*n) ) + 1 ; 
             fprintf (LBI, "%d  %s \n" , descripteur[0] ,f) ;  
             for  ( int i=0  ; i < c ; i++ )
                fprintf ( BDI , "%d  " , descripteur[i]) ;
             fprintf(BDI , "\n") ; 
         }


//Fonction pour recupere le nombre de bits utilisés pour la quantification
int configuration (FILE* fichier) 
{
  int carac=0;
  fseek(fichier,35,SEEK_SET); //permet de placer le curseur au niveau du caractère 35 (valeur de quantification) 
  fscanf(fichier,"%d",&carac); // lis le caractère au niveau du curseu
  return carac;
}

//Crée un descripteur image .txt a partire d'une matrice 
int* descripteur_image ( int ** matrice , int n , int * ptrNBCOL , int * ptrNBLIG , int * b) 
{
 int c = pow ( 2 , ((*b)*n) )  ; //  c+1 : taille d'un descripteur 
 int* D =  (int*) malloc ((c+1) *sizeof( int));  
 D[0]=0 ;  //Initialiser l'identifiant avec 0
 for (int i = 0 ; i < c ; i++ ){ 
    D[i+1] = histogramme( matrice , i  , ptrNBLIG , ptrNBCOL) ; 
    }
  return D ;

} 



void indexation_image () { 
 int id =0 ; 
 char nomFichier[200] ;
 system("ls /home/pfr/pfr/image/fich_images/txt > /home/pfr/pfr_code/data/listeFichierImage.txt " );  //Créé un fichier avec la liste des textes dans le répertoire 
 FILE * listeFichier = openFile("/home/pfr/pfr_code/data/listeFichierImage.txt","r") ; 
 system("rm /home/pfr/pfr/image/descripteurs_images/*.txt");

 while ( fscanf ( listeFichier ,"%s",nomFichier )==1) // Faire l'indexation de tous les fichiers
 { 

 printf ( "/home/pfr/pfr/image/fich_images/txt/%s\n",nomFichier);
 id++ ;
 FILE* config = openFile("/home/pfr/pfr_code/config.txt" , "r" ); 
 int n = configuration(config); 
 fclose(config);
 int NBLIG ; //nombre des lignes
 int NBCOL ; //nombre des colonnes
 int d ;  //nombre des composantes
 int ** matrice = pretraitement_image( nomFichier , &NBLIG ,&NBCOL , &d , n ) ; 
 int * Descripteur = descripteur_image ( matrice , n , &NBCOL, &NBLIG , &d ) ; 
 FILE* BDI = NULL ;
 FILE * LBI = NULL ;
 if (d==3){ //image en couleur 
 Descripteur[0]= 3000 + id;
 //Ouvrir les fichiers en mode écrire 
 BDI = openFile("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_couleur.txt" ,"a" ) ; 
 LBI = openFile("/home/pfr/pfr/image/descripteurs_images/base_image_couleur.txt","a" ) ;
 }
 
 else {  //image en N/B
 Descripteur[0]= 4000 +id; 
 BDI = openFile("/home/pfr/pfr/image/descripteurs_images/base_descripteur_image_NB.txt" ,"a" ) ;
 LBI = openFile("/home/pfr/pfr/image/descripteurs_images/base_image_NB.txt","a" ) ;
 }
 mise_a_jour_base_image ( LBI , BDI, nomFichier, Descripteur , n , &d) ;
 for (int i = 0 ; i< NBLIG ;i++ )
    free (matrice[i]) ; 
 free(matrice) ; 
 free (Descripteur ) ; 
 
 fclose( BDI );
 fclose( LBI ) ; 
 }
 fclose(listeFichier) ; 
}


//Fonction à utiliser dans la fonction recherche_image qui effectue le même traitement que la fonction indexation_image 
//mais avec un seul fichier, sans faire le mise à jour des fichiers base_descripteur_image.txt et base_image.txt et retourne un descripteur 
int* indexation_recherche (const char * image )  
{      FILE* config = openFile("/home/pfr/pfr_code/config.txt" , "r" ); 
         int  n = configuration(config); 
         int NBLIG ;
         int NBCOL ;
         int id =  100 ; 
         int d ; 
         int ** matrice = pretraitement_recherche(image , &NBLIG ,&NBCOL , &d  , n ) ; 
         int * Descripteur = descripteur_image  ( matrice , n , &NBCOL, &NBLIG , &d  ) ; 
         if (d==3){ 
         Descripteur[0]= 3000 + id;
          }
         else { 
          Descripteur[0]= 4000 +id; 
          }
         for (int i = 0 ; i< NBLIG ;i++ )
               free (matrice[i]) ; 
         free(matrice) ;  
         return (Descripteur) ;
}



