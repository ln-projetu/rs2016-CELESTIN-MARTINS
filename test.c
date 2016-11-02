#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* permutation(char* Mot, int position1, int position2){
	char lettre;
	lettre=Mot[position1];
	Mot[position1]=Mot[position2];
	Mot[position2]=lettre;
	return Mot;
}

int anagramme(char* Mot, int Pos, int taille){
	int i;

	if (Pos==taille-1){
		return(0);
	}
	else {
		for (i=Pos;i<taille;i++){
			if (i!=Pos || ( (Pos==0) && (i==0) ) ){
				Mot=permutation(Mot,Pos,i);
				printf("%s\n",Mot );
			}
			anagramme(Mot,Pos+1,taille);
			Mot=permutation(Mot,Pos,i);
		}
		return(0);
	}
}

int combi(){
	for 
}

int main(int argc, char* argv[]){
	char mot[]="abcd";
	anagramme(mot,0,4);
	return(0);
}