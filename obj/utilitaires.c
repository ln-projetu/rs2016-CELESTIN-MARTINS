#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "extracteur.h"
#include <time.h>

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

long long_convert_oct_to_dec(char *octalChar){
	long nbDec=0;
	long nbOctal = (long) atoll(octalChar);
	long pow8 = 1;
	while((nbOctal)!=0){
 		nbDec=nbDec+pow8*(nbOctal%10);
 		nbOctal/=10;
 		pow8*=8;
 	}
	return nbDec;
}

void date(char *octalTime )
{
	long decTime= long_convert_oct_to_dec(octalTime);
    time_t     epoch;
    struct tm  ts;
    char       buf[80];
    epoch= (time_t)decTime;
    ts = *localtime(&epoch);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("%s", buf);
}

void convert_permission(char *permission){
	int i;
	char result[10]={'-','-','-','-','-','-','-','-','-'};
	int permission_int=atoi(permission);
	int powp=100;
	int current;
	for (i=0;i<3;i++){
		current=(permission_int-(permission_int/(powp*10)*powp*10))/powp;
		if (current%2!=0){
			result[2+i*3]='x';
		}
		if (current>3){
			result[0+i*3]='r';
		}
		if (current%4==2 || current%4==3){
			result[1+i*3]='w';
		}
		powp/=10;
	}
	printf("%s ", result);
}