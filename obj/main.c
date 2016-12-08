#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "extracteur.h"
#include "utilitaires.h"
#include <sys/stat.h>


int main (int argc, char* argv[]){
	int opt;
	int fd;
	char* archive=argv[argc-1];

	struct stat st_buf;
	int status;
	status = stat(archive, &st_buf);

	if ( (status != 0) | (S_ISDIR(st_buf.st_mode) ) ){
		printf("Veuillez passez une archive tar en paramètre \n");
		exit(1);
	}
	fd=open(archive,O_RDONLY);
	if (fd==-1 ){
		printf("%s\n", strerror(errno));
		exit(1);
	}
	if (optind+1==argc){
		listeur(fd, ma_struct);
		close(fd);
		exit(0);
	}
	int fdx;
	int fdt;
	while ((opt=getopt(argc, argv, "xlpz"))!=-1){
		switch(opt){
			case 'x':
				//printf("extrait le contenu de %s\n",archive);
				extractDossier(fd, ma_struct);
				fdx=open(archive,O_RDONLY);
				extractFichier(fdx,ma_struct);
				close(fdx);
				fdt=open(archive,O_RDONLY);
				dateDossier(fdt,ma_struct);
				close(fdt);
				break;
			case 'l':
				//printf("listing détaillé de %s\n",archive);
				listeur_detail(fd, ma_struct);
				break;
			case 'p':
				//printf("utilisation de %s threads \n",argv[2]);
				break;
			case 'z':
				//printf("décompression de %s\n",archive);
				break;
			default:
				printf("erreur" );
				exit(EXIT_FAILURE);
		}
	}
	close(fd);	
	return(0);
}


