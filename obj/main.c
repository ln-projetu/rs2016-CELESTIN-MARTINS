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
	char* archive=argv[argc-1];

	struct stat st_buf;
	int status;
	status = stat(archive, &st_buf);

	if ( (status != 0) | (S_ISDIR(st_buf.st_mode) ) ){
		printf("Veuillez passez une archive tar en paramètre existante\n");
		exit(1);
	}
	

	if (optind+1==argc){
		int fds;
		fds=open(archive,O_RDONLY);
		if (fds==-1 ){
			printf("%s\n", strerror(errno));
			exit(1);
		}
		isCorrupted(fds, ma_struct);
		close(fds);
		int fd;
		fd=open(archive,O_RDONLY);
		listeur(fd, ma_struct);
		close(fd);
		exit(0);
	}

	
	while ((opt=getopt(argc, argv, "xlp:z"))!=-1){
		switch(opt){
			case 'x': ;
				int fd;
				fd=open(archive,O_RDONLY);
				listeur(fd, ma_struct);
				close(fd);

				int fdd;
				fdd=open(archive,O_RDONLY);
				extractDossier(fdd, ma_struct);
				close(fdd);
				
				int fdx;
				fdx=open(archive,O_RDONLY);
				extractFichier(fdx,ma_struct);
				close(fdx);

				int fdt;
				fdt=open(archive,O_RDONLY);
				dateDossier(fdt,ma_struct);
				close(fdt);
				break;
			case 'l': ;
				int fds;
				fds=open(archive,O_RDONLY);
				isCorrupted(fds, ma_struct);
				int fdi;
				fdi=open(archive,O_RDONLY);
				listeur_detail(fdi, ma_struct);
				break;
			case 'p':
				//printf("utilisation de %s threads \n",argv[2]);
				break;
			case 'z': ;
				int tai=(int)strlen(archive)-2;
				char *decompresse=malloc(tai*sizeof(char));
				memcpy( decompresse, &archive[0], tai );
				decompresse[tai-1]='\0';

				simpleDecompress(archive,decompresse);

				int i;
				for (i=0; i<(int)strlen(decompresse)+1;i++){
					archive[i]=decompresse[i];
				}
				free(decompresse);	
							
				break;
			default:
				printf("erreur" );
				exit(EXIT_FAILURE);
		}
	}
	return(0);
}
