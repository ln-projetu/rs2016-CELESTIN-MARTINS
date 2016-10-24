IDIR =../include
CC=gcc
CFLAGS=-g -I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = utilitaires.h extracteur.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.c utilitaires.c extracteur.c
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -g -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 