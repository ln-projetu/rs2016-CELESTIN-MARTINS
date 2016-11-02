#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"
#include "correcteur_orthographique.h"


int isCorrect(char *word, char *Dictionnaire){	
	FILE *Dico=malloc(sizeof(FILE));
	Dico=fopen(Dictionnaire, "r");
	char lettreActu;
	char *motDico=calloc(50 , sizeof(char));
	int nb=0;
	lettreActu=fgetc(Dico);
	while ((strcmp(word,motDico)) && (lettreActu != EOF)){
		while (lettreActu != '\n'){
			motDico[nb]=lettreActu;
			nb++ ;
			lettreActu=fgetc(Dico);
		}
		motDico[nb]='\0';
		lettreActu=fgetc(Dico);
		nb=0;
	}
	fclose (Dico);
	if (!strcmp(word,motDico)){
		free(motDico);
		return 1;
	}
	else {
		free(motDico);
		return 0;
	}
}



char** suggest(char *wrongWord, char *Dictionnaire){
	//printf("dans suggest\n");
	FILE *Dico=calloc(1,sizeof(FILE));
	Dico=fopen(Dictionnaire, "r"); 
	int continuer=0;
	char lettreActu;
	//printf("%c",lettreActu);
	char *motDico=calloc(50,sizeof(char));
	int nb=0;	
	int diff;
	diff=0;
	int taille=0;
	int accent;
	int accentIni;
	char testi;
	testi=wrongWord[taille];
	int nbSpeIni=0;
	int *placeSpeIni=calloc(50,sizeof(int));
	int *placeSpe=calloc(50,sizeof(int));
	int diffTaille;
	int *diffTab=calloc(50,sizeof(int));
	while(testi!='\0'){
		accentIni=testi;
		if (accentIni==-61){
			nbSpeIni++;
		}
		placeSpeIni[taille]=nbSpeIni;
		taille++;
		testi=wrongWord[taille];
	}
	int nbSpe=0;
	int boucle;
	char *reponse=calloc(10,sizeof(char));
	char **listeReponse=calloc(100,sizeof(char*));
	int ouri;
	for (ouri=0;ouri<100;ouri++){
		*(listeReponse+ouri*sizeof(char))=calloc(50,sizeof(char));
	}
	int tailleListeReponse;
	tailleListeReponse=0;
	lettreActu=fgetc(Dico);
	while ((continuer==0) && (lettreActu != EOF)){
		while ((lettreActu != '\n')){
			motDico[nb]=lettreActu;
			accent=lettreActu;
			if ( accent==-61 ){
				nbSpe++;
			}
			placeSpe[nb]=nbSpe;
			lettreActu=fgetc(Dico);
			nb++ ;
			
		}
		motDico[nb]='\0';
		diffTaille=nb-taille;
		boucle=0;
		if (diffTaille==-1){
			while ((boucle<taille) && (diff<2)){
				if (motDico[boucle-diff]!=wrongWord[boucle] ){
					diff++;
					if ((placeSpeIni[boucle]-placeSpeIni[boucle-1])==1){
						diff--;
					}
				}
				boucle ++;
			}
		}
		if (diffTaille==1){
			while( (boucle<nb) && (diff<2) ){
				if (motDico[boucle]!=wrongWord[boucle-diff]) {
					diff++;
					if ((placeSpe[boucle]-placeSpe[boucle-1])==1){
						diff--;
					}
				}
				boucle++;
			}
		}
		if (diffTaille==0){
			while ( ( (boucle<taille-placeSpe[boucle]) || (boucle<taille-placeSpeIni[boucle]) ) && (diff<2)){
				if (motDico[boucle+placeSpe[boucle]]!=wrongWord[boucle+placeSpeIni[boucle]]){
					diffTab[diff]=boucle+placeSpe[boucle];
					diff++;
					if ((diff==2) &&
						(motDico[diffTab[0]]==wrongWord[diffTab[1]+placeSpeIni[diffTab[1]]-placeSpe[diffTab[1]]]) &&
						(motDico[diffTab[1]]==wrongWord[diffTab[0]+placeSpeIni[diffTab[0]-1]-placeSpe[diffTab[0]]]) ){
						diff--;
					}
				}
				boucle++;
			}
		}
		lettreActu=fgetc(Dico);
		if (diff==1){
			tailleListeReponse++;
			copie_mot(listeReponse[tailleListeReponse],motDico);
		}
		nbSpe=0;
		nb=0;
		diff=0;
	}
	fclose(Dico);
	free (diffTab);
	free(placeSpeIni);
	free (placeSpe);
	free (reponse);
	listeReponse[0][0]=tailleListeReponse;
	if (tailleListeReponse==0){
		int azez;
		for (azez=0;azez<100;azez++){
			free(listeReponse[azez]);
		}
		free(listeReponse);
		return NULL;
	}
	else{
		return (listeReponse);
	}
}


void checkFile(char *filename, char *Dictionnaire){	
	FILE *fichier=malloc(sizeof(FILE));
	FILE *copie=NULL;
	fichier=fopen(filename, "r"); 
	copie=fopen("copie_corrigee.txt","w");
	char lettreActu=NULL;
	char *motFichier=calloc(50,sizeof(char));
	char *motCopie=calloc(50,sizeof(char));
	int nb=0;	
	int correct;
	int debutDePhrase=1;
	int debutDeMot=1;
	int ascii;
	char majuscule='&';
	int nomPropre=0;
	char *reponse=calloc(10,sizeof(char));
	reponse[0]=' ';
	int verification=1;
	char temp;
	char** listeSuggestion=calloc(100,sizeof(*listeSuggestion));
	int ouri;
	for (ouri=0;ouri<100;ouri++){
		*(listeSuggestion+ouri*sizeof(char))=calloc(50,sizeof(char));
	}
	int x=-3;
	int tailleListeSuggestion=0;
	lettreActu=fgetc(fichier);
	while ( lettreActu != EOF ){
		while(lettreActu!=')' && lettreActu!=';' && lettreActu!=':' && lettreActu!='\n' && 
			lettreActu !=' ' && lettreActu!='(' && lettreActu != '"' && lettreActu!=',' &&
			lettreActu!='.'	&& lettreActu!='!' && lettreActu!='?' && lettreActu!='	' && 
			lettreActu!='\'' && !isNumber(lettreActu) ){
			ascii=lettreActu;
			if (debutDeMot){
				if ( (ascii<91) && (ascii>64) ){
					majuscule=lettreActu;
					lettreActu=ascii+32;
					nomPropre=1;
				}
				debutDeMot=0;
			}
			motFichier[nb]=lettreActu;
			nb++ ;
			lettreActu=fgetc(fichier);
		}
		debutDeMot=1;
		motFichier[nb]='\0';
		if (nomPropre && !debutDePhrase){
			temp=motFichier[0];
			motCopie=motFichier;
			motCopie[0]=majuscule;
			printf("%s", motCopie);
			while(strcmp(reponse,"no") && strcmp(reponse,"yes")){
				printf("\n\nLe dernier mot affiché est-il un nom Propre ? yes/no\n");
				scanf("%s", reponse);
				printf("\n");
				if (!strcmp(reponse,"yes")){
					verification=0;
				}
				if(!strcmp(reponse,"no")){
					motFichier[0]=temp;
					nomPropre=0;
				}
			}
		}
		reponse[0]=' ';
		if (verification){
			correct=isCorrect(motFichier,Dictionnaire);
			if (correct){
				copie_mot(motCopie,motFichier);
				if (nomPropre){
					motCopie[0]=majuscule;
					debutDePhrase=0;
				}
				printf("%s",motCopie);
			}
			else{
				if (nomPropre){
					temp=motFichier[0];
					motFichier[0]=majuscule;
					printf("%s", motFichier);
					motFichier[0]=temp;
				}
				else {
					printf("%s", motFichier);
				}
				listeSuggestion=suggest(motFichier,Dictionnaire);
				if (listeSuggestion!=NULL){
					tailleListeSuggestion=listeSuggestion[0][0];
					while ( (x>tailleListeSuggestion)  || (x<-2)) {
						int ko;
						for (ko=1;ko<tailleListeSuggestion+1;ko++){
							printf("\n%d ", ko);
							printf("%s\n", listeSuggestion[ko]);
						}
						printf("\nChoisissez un mot dans la liste\n");
						printf("ou tapez 0 pour ajouter le mot au dicionnaire, -1 pour le supprimer du texte et -2 sinon\n");
						scanf("%i", &x);
						printf("\n");
					}
				if (x>0 && x<tailleListeSuggestion)
					copie_mot(motCopie,listeSuggestion[x]);
				else
					if (x==0){
						ajouter_mot(motFichier,Dictionnaire);
						copie_mot(motCopie,motFichier);
					}
					else if (x==-1)
							motCopie="";
						else if (x==-2)
							copie_mot(motCopie,motFichier);
				}
				x=-3;
				if (nomPropre){
					motCopie[0]=majuscule;
				}
			}
			if (debutDePhrase && lettreActu!=' '){
				debutDePhrase=0;
			}
		}
		fprintf(copie, "%s", motCopie);
		fputc(lettreActu,copie );
		printf("%c", lettreActu);
		verification=1;
		if (lettreActu=='.' || lettreActu=='!' || lettreActu=='?' || lettreActu=='	' || lettreActu=='\n'){
			debutDePhrase=1;
		}
		lettreActu=fgetc(fichier);
		nomPropre=0;
		majuscule='&';
		nb=0;
	 }
	free(motFichier);
	free(reponse);
	fclose(fichier);
	fclose(copie);
	free(listeSuggestion);
	copieFichier("copie_corrigee.txt",filename);
}

