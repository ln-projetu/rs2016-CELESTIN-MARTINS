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
#include <utime.h>



void listeur(int fd, struct header_posix_ustar ma_struct){
	int lu;
	int size;
	do{
		size=convert_oct_to_dec(ma_struct.size);
		if (size!=0){
			if (size%512==0)
				lseek(fd,(size/512)*512,SEEK_CUR);
			else 
				lseek(fd,(size/512+1)*512,SEEK_CUR);
		}
		lu=read(fd,&ma_struct,512);
		if (strlen(ma_struct.name)!=0)
			printf("%s\n",ma_struct.name);
	}while (lu!=0);
}

void extractDossier(int fd, struct header_posix_ustar ma_struct){
	int lu;
	int size;
	int longueur;
	mode_t mode;
	char *name=malloc(512*sizeof(char));

	do{
		
		lu=read(fd,&ma_struct.name,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			if (ma_struct.name[longueur-1]=='/'){
				mode=strtol(ma_struct.mode,NULL,8);
				strcpy(name,"");
				if (strlen(ma_struct.prefix)){
					strcat(name,ma_struct.prefix);
					strcat(name,"/");
				}
				strcat(name,ma_struct.name);

				umask(0000);
	
				mkdir(name, mode);
				size=convert_oct_to_dec(ma_struct.size);

				
				if (size!=0){
					if (size%512==0)
						lseek(fd,(size/512)*512,SEEK_CUR);
					else 
						lseek(fd,(size/512+1)*512,SEEK_CUR);
				}
				
				

			}
		}
	}while(lu!=0);
	free (name);
}

void dateDossier(int fd, struct header_posix_ustar ma_struct){
	int lu;
	int size;
	int longueur;
	char *name=malloc(512*sizeof(char));
	struct utimbuf chtime;
	time_t dtime;
	do{
		
		lu=read(fd,&ma_struct.name,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			if (!strcmp(ma_struct.typeflag,"5")){
				strcpy(name,"");
				if (strlen(ma_struct.prefix)){
					strcat(name,ma_struct.prefix);
					strcat(name,"/");
				}
				strcat(name,ma_struct.name);
				size=convert_oct_to_dec(ma_struct.size);
				dtime=long_convert_oct_to_dec(ma_struct.mtime);
				chtime.actime= dtime;
				chtime.modtime= dtime;
				utime(name, &chtime);
				if (size!=0){
					if (size%512==0)
						lseek(fd,(size/512)*512,SEEK_CUR);
					else 
						lseek(fd,(size/512+1)*512,SEEK_CUR);
				}
			}
		}
	}while (lu!=0);
	free(name);

}


void extractFichier(int fd, struct header_posix_ustar ma_struct){
	int lu;
	int size;
	int longueur;
	mode_t mode;
	char *name= malloc(256*sizeof(char));
	struct utimbuf chtime;
	do{
		lu=read(fd,&ma_struct.name,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			if (!strcmp(ma_struct.typeflag,"0")){
				size=convert_oct_to_dec(ma_struct.size);
				mode=strtol(ma_struct.mode,NULL,8);
				strcpy(name,"");
				if (strlen(ma_struct.prefix)){
					strcat(name,ma_struct.prefix);
					strcat(name,"/");
				}
				strcat(name,ma_struct.name);
				ecrireFichier(fd,name,size,mode);
				chtime.actime= (time_t) long_convert_oct_to_dec(ma_struct.mtime);
				chtime.modtime= (time_t) long_convert_oct_to_dec(ma_struct.mtime);
				utime(name, &chtime);
			}
		}
	}while(lu!=0);
	free(name);
}

void ecrireFichier(int fd, char* nomFichier, int size ,mode_t mode){
	umask(0000);
	int fdw=open(nomFichier,O_WRONLY | O_CREAT, mode );
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
	if (size%512==0)
		lseek(fd,(size/512)*512-size,SEEK_CUR);
	else
		lseek(fd,(size/512+1)*512-size,SEEK_CUR);
}


void listeur_detail(int fd, struct header_posix_ustar ma_struct){
	int lu;
	int size;
	int longueur;
	int taille_dec;
	char *typeflag;
	int isLinkname;
	char *name=malloc(256*sizeof(char));
	do{
		size=convert_oct_to_dec(ma_struct.size);
		if (size%512==0)
			lseek(fd,(size/512)*512,SEEK_CUR);
		else 
			lseek(fd,(size/512+1)*512,SEEK_CUR);
		lu=read(fd,&ma_struct,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			isLinkname=0;
			typeflag=ma_struct.typeflag;
			if (!strcmp(typeflag,"0"))
				printf("-");
			else
			{
			if(!strcmp(typeflag,"2")){
					printf("l");
					isLinkname=1;
				}
			else
			{
			if(!strcmp(typeflag,"5"))
					printf("d");
			}
			}
			convert_permission(ma_struct.mode);
			printf("%li/%li", strtol(ma_struct.uid,NULL,8), strtol(ma_struct.gid,NULL,8));
			taille_dec=convert_oct_to_dec(ma_struct.size);
			printf(" %d ", taille_dec);
			date(ma_struct.mtime);
			strcpy(name,"");
			if (strlen(ma_struct.prefix)){
				strcat(name,ma_struct.prefix);
				strcat(name,"/");
			}
			strcat(name,ma_struct.name);
			printf(" %s",name);
			if (isLinkname){
				printf(" -> %s\n", ma_struct.linkname);
			}
			printf("\n");
		}
	}while (lu!=0);
}