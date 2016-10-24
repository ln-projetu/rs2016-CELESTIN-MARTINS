#include <string.h>
#include <stdio.h>
#include <stdib.h>
#include "utilitaires.h"
#include "extracteur.h"

int convert_oct_to_dec(char *octalChar){
	int nbDec=0;
	int nbOctal = atoi(octalChar);
	int pow8 = 1;
	while((nbOctal)!=0){
 		nbDec=nbDec+pow8*(nbOctal%10);
 		nbOctal/=10;
 		pow8*=8;
 	}

	return nbDec;
}
