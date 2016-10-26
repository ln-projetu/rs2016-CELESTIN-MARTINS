#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "utilitaires.h"
#include "extracteur.h"




void listeur(int fd, struct header_posix_ustar ma_struct,char* archive){
	int lu;
	int size;
	printf("Liste des dossiers et fichiers dans l'archive \"%s\" :\n", archive);
	do{
		size=convert_oct_to_dec(ma_struct.size);
		if (size!=0)
			lseek(fd,(size/512+1)*512,SEEK_CUR);
		lu=read(fd,&ma_struct,512);
		if (strlen(ma_struct.name)!=0)
			printf("-%s\n",ma_struct.name);
	}while (lu!=0);
}

void extractDossier(int fd, struct header_posix_ustar ma_struct){
	int lu;
	int size;
	int longueur;
	//FILE *fichier=malloc(sizeof(FILE));
	do{
		size=convert_oct_to_dec(ma_struct.size);
		if (size!=0)
			lseek(fd,(size/512+1)*512,SEEK_CUR);
		lu=read(fd,&ma_struct.name,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			if (ma_struct.name[longueur-1]=='/')
				mkdir(ma_struct.name,0777);
			/*else{
				execlp("touch","touch",ma_struct.name,NULL);
			}*/
		}
	}while(lu!=0);
}

void extractFichier(int fd, struct  header_posix_ustar ma_struct){
	int lu;
	int size;
	int longueur;
	//FILE *fichier=malloc(sizeof(FILE));
	do{
		size=convert_oct_to_dec(ma_struct.size);
		if (size!=0)
			lseek(fd,(size/512+1)*512,SEEK_CUR);
		lu=read(fd,&ma_struct.name,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			if (ma_struct.name[longueur-1]!='/')
				execlp("touch","touch",ma_struct.name,NULL);
		}
	}while(lu!=0);
}
