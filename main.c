#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

struct header_posix_ustar {
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char checksum[8];
	char typeflag[1];
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
	char pad[12];
}ma_struct;

struct struct_interm{
	int lu;
	int size;
	int fd;
	struct header_posix_ustar ma_struct;
	char* name;
};

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

void listeur(int fd, struct header_posix_ustar ma_struct,char* archive){
	int lu=read(fd,&ma_struct,512);
	int size;
	printf("Liste des dossiers et fichiers dans l'archive \"%s\" :\n", archive);
	printf("-%s\n",ma_struct.name);
	while (lu!=0){
		size=convert_oct_to_dec(ma_struct.size);
		if (size!=0)
			lseek(fd,size+512,SEEK_CUR);
		lu=read(fd,&ma_struct,512);
		if (strlen(ma_struct.name)!=0)
			printf("-%s\n",ma_struct.name);
	}
}




int main (int argc, char* argv[]){
	char* archive=argv[1];
	int fd=open(archive,O_RDONLY);
	listeur(fd, ma_struct,archive);
	close(fd);

	return(0);
}

