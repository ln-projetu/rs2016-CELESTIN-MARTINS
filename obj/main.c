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


struct struct_interm{
	int lu;
	int size;
	int fd;
	struct header_posix_ustar ma_struct;
	char* name;
};

int main (int argc, char* argv[]){
	char* archive=argv[1];
	int fd=open(archive,O_RDONLY);
	listeur(fd, ma_struct,archive);
	close(fd);

	return(0);
}

