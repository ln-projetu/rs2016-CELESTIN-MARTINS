#ifndef CORRECTEUR_ORTHOGRAPHIQUE_H
#define CORRECTEUR_ORTHOGRAPHIQUE_H
#define TAILLE_MAX 50


int isCorrect(char *word, char *Dictionnaire);

char** suggest(char *wrongWord, char *Dictionnaire);

void checkFile(char *filename, char *Dictionnaire);

#endif

