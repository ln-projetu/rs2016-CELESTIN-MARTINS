#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

int main (int argc, char* argv[]){
    int opt;
    int i=1;
    int option=0;
    int fd;
    while ((opt=getopt(argc, argv, "xlpz:"))!=-1){
        switch(opt){
            case 'x':
                option=1;
                i++;
                printf("extrait le contenu de %s\n",argv[i]);
                break;
            case 'l':
                if (option==0) i++;
                option=1;
                printf("listing détaillé de %s\n",argv[i]);
                break;
            case 'p':
                if (option==0)i++;
                option=1;
                printf("utilisation de %s threads \n",argv[i]);
                i++;
                break;
            case 'z':
                if (option==0) i++;
                option=1;
                printf("décompression de %s\n",argv[i]);
                break;
            default:
                printf("dans default" );
                fd=open(argv[i],O_RDONLY);
                listeur(fd, ma_struct,argv[i]);
                close(fd);
                exit(0);
        }
    }
    return(0);
}