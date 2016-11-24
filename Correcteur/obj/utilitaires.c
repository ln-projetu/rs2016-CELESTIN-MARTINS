#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utilitaires.h"

void ajouter_mot(char mot[], char* dictionnaire)
{
    char* nomFichier = "Dictionnaire.txt";
    FILE* fichier = NULL;
    fichier = fopen(nomFichier,"a");
    if (fichier != NULL)
    {
        fprintf(fichier,"\n%s",mot);
        fclose(fichier);
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier %s\n",nomFichier);
    }
}


void copieFichier(char *original, char*copie){
    FILE *originalF=NULL;
    FILE *copieF=NULL;
    originalF=fopen(original,"r");
    copieF=fopen(copie,"w");
    char lettreActu=NULL;
    lettreActu=fgetc(originalF);
    while(lettreActu!=EOF){
        fputc(lettreActu,copieF);
        lettreActu=fgetc(originalF);
    }
}


int isNumber(char caractere){
    int ascii;
    ascii=caractere;
    int Number=0;
    if (ascii>47 && ascii<58){
        Number=1;
    }
    return Number;
}

void copie_mot(char *dest, char *src){
    int taille;
    taille=strlen(src);
    int boucle;
    for (boucle=0;boucle<taille;boucle++){
        dest[boucle]=src[boucle];
    }
    dest[taille]='\0';
}