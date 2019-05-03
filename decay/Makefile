#OBJ = DSSD2Tr_March TSCorrSiGe DSSDGeMerge separate_March BuildDecay DSSDGeCorr PLASTIC2Tr
#OBJ = online_DSSD WASABI2Tr
#OBJ = enthe 
#sourcefile = main.cpp enthe.cpp enthe.h 

EXE = decay
sourcefile = main.cpp decay.h decay.cpp
OBJ = $(subst,.cpp,.o,$(filter %.cpp,$(sourcefile)))

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -Wall -O2 -I$(TARTSYS)/include -I$(ROOTSYS)/include -L$(TARTSYS)/lib -lXMLParser -lSpectrum
#-lanacore

GXX = g++ 
#-std=c++0x

all:$(EXE)

$(EXE):main.o decay.o
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -o $(EXE) main.o decay.o
	

main.o: main.cpp decay.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -c main.cpp

decay.o: decay.cpp decay.h
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) -c decay.cpp
clean:
	rm -f *~ *.o $(EXE)
