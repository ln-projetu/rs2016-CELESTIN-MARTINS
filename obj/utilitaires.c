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

char rwx[3][2]={{'-','r'},{'-','w'},{'-','x'}};

int* convert_oct_to_bin(char *octalChar){
	int nbBin[3];
	int nbOctal = atoi(octalChar);
	int pow8=1;
	int i;
	int pow2=4;
	for (i=0;i<3;i++){
		if(nbOctal/pow2 != 0){
			nbBin[i]=1;
		}
		nbOctal/=2;
		pow2*=2;
	}
	return nbBin;
}


/*char* convert_permission(char *permission_oct){
	int i,j;
	int nbBin[3];
	char permission_let[9];
	char temp[1];
	for (i=3;i<6;i++){
		temp[0]=permission_oct[i];
		for (j=0;j<3;j++){
			permission_let[j+(3*i-9)]=rwx[j][convert_oct_to_bin(temp[0])[j]];
		}
	}
	return permission_let;
}*/

void date(char *octalTime )
{
	long decTime= long_convert_oct_to_dec(octalTime);
    time_t     now;
    struct tm  ts;
    char       buf[80];
    // Get current time
    now= (time_t)decTime;
    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    printf("%s", buf);
}

char* convert_permission(char *permission){
	int i;
	char *result=NULL;
	result=calloc(9,sizeof(char));
	
	for(i=strlen(permission)-1;i>strlen(permission)-4;i--)
		{
		if(permission[i]=='0')
		{
		strcat(result,"---");
		}
		else if(permission[i]=='1')
		{
		strcat(result,"--x");
		}
		else if(permission[i]=='2')
		{
		strcat(result,"-w-");
		}
		else if(permission[i]=='3')
		{
		strcat(result,"-wx");
		}
		else if(permission[i]=='4')
		{
		strcat(result,"r--");
		}
		else if(permission[i]=='5')
		{
		strcat(result,"r-x");
		}
		else if(permission[i]=='6')
		{
		strcat(result,"rw-");
		}
		else if(permission[i]=='7')
		{
		strcat(result,"rwx");
		}
	}
	return result;
}