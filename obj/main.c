#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

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

int main (int argc, char* argv[]){
	int opt;
	int fd;
	char* archive=argv[argc-1];
	fd=open(archive,O_RDONLY);
	if (fd==-1){
		fprintf(stderr, "%s\n", strerror(errno));
		exit(1);
	}
	if (optind+1==argc){
		listeur(fd, ma_struct,archive);
		close(fd);
		exit(0);
	}
	close(fd);
	while ((opt=getopt(argc, argv, "xlpz"))!=-1){
		switch(opt){
			case 'x':
				printf("extrait le contenu de %s\n",archive);
				break;
			case 'l':
				printf("listing détaillé de %s\n",archive);
				break;
			case 'p':
				printf("utilisation de %s threads \n",argv[2]);
				break;
			case 'z':
				printf("décompression de %s\n",archive);
				break;
			default:
				printf("erreur" );
				exit(EXIT_FAILURE);
		}
	}
	
	return(0);
}


