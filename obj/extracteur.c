#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include "utilitaires.h"
#include "extracteur.h"
#include <utime.h>
#include <assert.h>
#include "../lib/zlib/zlib.h"
#include <dlfcn.h>
#define CHUNK 131272




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
			if (ma_struct.typeflag[0]=='5'){
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
			if (ma_struct.typeflag[0]=='5'){
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
	struct timeval symtime[2];
	long timesym;
	do{
		lu=read(fd,&ma_struct.name,512);
		longueur=strlen(ma_struct.name);
		if (longueur!=0){
			if (ma_struct.typeflag[0]=='0'){
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
			else{
				if(ma_struct.typeflag[0]=='2'){
					strcpy(name,"");
					if (strlen(ma_struct.prefix)){
						strcat(name,ma_struct.prefix);
						strcat(name,"/");
					}
					strcat(name,ma_struct.name);
					symlink(ma_struct.linkname,name);
					timesym=long_convert_oct_to_dec(ma_struct.mtime);
					symtime[0].tv_sec=timesym;
					symtime[0].tv_usec=0;
					symtime[1].tv_sec=timesym;
					symtime[1].tv_usec=0;
					lutimes(name, symtime);
				}
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
			if (typeflag[0]=='0')
				printf("-");
			else
			{
			if(typeflag[0]=='2'){
					printf("l");
					isLinkname=1;
				}
			else
			{
			if(typeflag[0]=='5')
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


int decompress(FILE *source, FILE *dest){
	dlopen("libz.so", RTLD_NOW);
	int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;
    do{
    	strm.avail_in = fread(in, 512, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;
        do{
        	strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR); 
            switch (ret) {
	            case Z_NEED_DICT:
	            	printf("dico\n");
	                ret = Z_DATA_ERROR;  
	            case Z_DATA_ERROR:
	            	printf("dataerror\n");
	            case Z_MEM_ERROR:
	                (void)inflateEnd(&strm);
	                printf("retour milieu\n");
	                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 512, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                printf("errfin\n");
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
    } while (ret != Z_STREAM_END);
    (void)inflateEnd(&strm);
    printf("fin\n");
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}


void isCorrupted(int fd, struct header_posix_ustar ma_struct){
	int actualSum;
	int size;
	//read(fd,&ma_struct,512);
	while (read(fd,&ma_struct,512),atoi(ma_struct.checksum)!=0){
		actualSum=0;
		actualSum=
					sommeAscii(ma_struct.name,100) +
					sommeAscii(ma_struct.mode,8) +
					sommeAscii(ma_struct.uid,8) +
					sommeAscii(ma_struct.gid,8) +
					sommeAscii(ma_struct.size,12) +
					sommeAscii(ma_struct.mtime,12) +
					sommeAscii(ma_struct.typeflag,1) +
					sommeAscii(ma_struct.linkname,100) +
					sommeAscii(ma_struct.magic,6) +
					sommeAscii(ma_struct.version,2) +
					sommeAscii(ma_struct.uname,32) +
					sommeAscii(ma_struct.gname, 32) +
					sommeAscii(ma_struct.devmajor,8) +
					sommeAscii(ma_struct.devminor,8) +
					sommeAscii(ma_struct.prefix,155) +
					sommeAscii(ma_struct.pad,12) +
					8*32;
		if (actualSum!=(int)strtol(ma_struct.checksum,NULL,8)){
			exit(-1);
		}
		size=convert_oct_to_dec(ma_struct.size);
		if (size%512==0)
			lseek(fd,(size/512)*512,SEEK_CUR);
		else 
			lseek(fd,(size/512+1)*512,SEEK_CUR);
	}
}