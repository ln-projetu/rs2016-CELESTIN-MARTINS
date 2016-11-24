#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(/*int argc, char *argv[]*/){
	char *fichier=malloc(30*sizeof(char));
	printf("Entrez un nom de fichier\n");
	scanf("%s",fichier);
	printf("\n");
	char *langue=malloc(10*sizeof(char));
	printf("Choose a language\n" );
	printf("tapez:\n");
	printf("- fr pour le francais\n");
	printf("- en for English\n ");
	scanf ("%s",langue);
	char *dictionnaire=malloc(50*sizeof(char));
	int defaut=1;
	if (!strcmp(langue,"fr")){
		//printf("dans le fr\n");
		dictionnaire="Dictionnaire_Francais.txt";
		defaut=0;
	}
	if (!strcmp(langue,"en")){
		dictionnaire="wordsEn.txt";
		defaut=0;
	}
	if (defaut){
		printf("No language associate with this number\n" );
	}
	//suggest(fichier, "dictionnaire_francais_accents.txt");
	checkFile(fichier,dictionnaire);
	//isCorrect(fichier,"dictionnaire_francais_accents.txt");
	free(fichier);
	return 0;
}
