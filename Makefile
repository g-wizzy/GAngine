CC=g++
CFLAGS = -I$(IDIR) -Wall -lSDL2 -std=c++17
IDIR=include

SDIR=src
ODIR=obj

OUTDIR=out

_DEPS = gangine.h helper.h input.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o gangine.o helper.o input.o
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
