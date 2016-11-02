#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
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
	do{
		size=convert_oct_to_dec(ma_struct.size);
		if (size!=0)
			lseek(fd,(size/512+1)*512,SEEK_CUR);
		lu=read(fd,&ma_struct.name,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			if (ma_struct.name[longueur-1]=='/')
				mkdir(ma_struct.name,0777);
		}
	}while(lu!=0);
}

void extractFichier(int fd, struct  header_posix_ustar ma_struct){
	int lu;
	int size;
	int longueur;
	int pid;
	int status;
	do{
		lu=read(fd,&ma_struct.name,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			if (ma_struct.name[longueur-1]!='/'){
				if ((pid=fork())==0)
					execlp("touch","touch",ma_struct.name,NULL);
				else{
					waitpid(pid,&status,0);
					size=convert_oct_to_dec(ma_struct.size);
					ecrireFichier(fd,ma_struct.name,size);
				}
			}
		}
	}while(lu!=0);
}

void ecrireFichier(int fd, char* nomFichier, int size){
	int fdw=open(nomFichier,O_WRONLY);
	ssize_t numBytes;
	int partition=size/256;
	int reste=size%256;
	char *buffer[256];
	int i;
	for (i = 0; i < partition; ++i)
	{
		numBytes=read(fd,buffer,256);
		write(fdw,buffer,numBytes);
	}
	numBytes=read(fd,buffer,reste);
	write(fdw,buffer,numBytes);
	close(fdw);
	lseek(fd,(size/512+1)*512-size,SEEK_CUR);
}