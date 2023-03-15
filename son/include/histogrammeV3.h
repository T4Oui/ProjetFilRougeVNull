#ifndef histogramme_H_INCLUS
#define histogramme_H_INCLUS


#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------
// nombre d'echantillons
#define n 1024

// nombre d'intervalles
#define m 20
//------------------------------------------------------------------------------



// taille de l'intervalle des valeurs du signal (entre -1 et 1 donc taille = 2)
#define taille 2


typedef struct et_histo{
int tab [m];
} HISTOGRAMME;


HISTOGRAMME fct_histogramme( double pas, double echant, HISTOGRAMME h );

#endif