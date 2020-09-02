CC=g++
CFLAGS = -I$(IDIR) -Wall
IDIR=include

SDIR=src
ODIR=obj

OUTDIR=out

_DEPS = dummy.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o dummy.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/GAngine: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) #$(LIBS)

.PHONY: clean

run:
	@ $(OUTDIR)/GAngine

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
