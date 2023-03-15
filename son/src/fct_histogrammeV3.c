#include <stdio.h>
#include <stdlib.h>
#include "../include/histogrammeV3.h"



HISTOGRAMME fct_histogramme( double pas, double echant, HISTOGRAMME h ) {


int intervalle = 0 ; // intervalle est l'indice de l'intervalle entre borne_sup = borne_inf+pas et borne_inf
double borne_inf;
double borne_sup;


borne_inf = -1; // initialisée au minimum -1

while (borne_inf < 1 ){
    borne_sup = borne_inf+pas;
            if ( echant < borne_sup && echant >= borne_inf){
                h.tab [intervalle] = h.tab [intervalle]+1;
                //histo = h.tab [intervalle] ;
                intervalle = 0; // on reinitialise l'intervalle a 0 pour le prochain echantillon
                break;
            }
            borne_inf =(double) (borne_inf+pas);
            intervalle++;
}
//printf ("intervalle %d : %lf <= %lf <%lf \n", cp_intervalle, borne_inf, echant, borne_sup);
return h;

}

