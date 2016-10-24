#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "utilitaires.h"
#include "extracteur.h"

void listeur(int fd, struct header_posix_ustar ma_struct,char* archive){
	int lu=read(fd,&ma_struct,512);
	int size;
	printf("Liste des dossiers et fichiers dans l'archive \"%s\" :\n", archive);
	printf("-%s\n",ma_struct.name);
	while (lu!=0){
		size=convert_oct_to_dec(ma_struct.size);
		if (size!=0)
			lseek(fd,(size/512+1)*512,SEEK_CUR);
		lu=read(fd,&ma_struct,512);
		if (strlen(ma_struct.name)!=0)
			printf("-%s\n",ma_struct.name);
	}
}
