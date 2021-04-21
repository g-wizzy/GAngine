CC=g++
CFLAGS = -I$(IDIR) -Wall -std=c++17
LDFLAGS = -lGLEW -lglfw -lGL

IDIR=include
SDIR=src
ODIR=obj

OUTDIR=out

_DEPS = gangine.h input.h entity.h entitymanager.h systems.h components.h systems/system.h systems/debugrender.h systems/speed.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o gangine.o input.o entitymanager.o systems/debugrender.o systems/speed.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.SECONDEXPANSION:

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) $$(@D)/.f
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/GAngine: $(OBJ)
	mkdir -p $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%/.f:
	mkdir -p $(dir $@)
	touch $@

.PRECIOUS: %/.f

.PHONY: clean

run:
	@ $(OUTDIR)/GAngine

clean:
	rm -f $(ODIR)/*.o $(ODIR)/**/*.o *~ core $(IDIR)/*~
