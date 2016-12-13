IDIR =../include
CC=gcc
CFLAGS=-Wall -Wextra -g -I$(IDIR) -L$(LDIR)

ODIR=obj
LDIR=../lib/zlib

LIBS=-lz -ldl

_DEPS = utilitaires.h extracteur.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.c utilitaires.c extracteur.c
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

ptar: $(OBJ)
	gcc -g -o $@ $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	
