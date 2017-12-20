CXX       = g++
CXXFLAGS  = -ansi -pedantic -Wno-write-strings -Wno-long-long
CXXFLAGS += -D HAVE_ZLIB #ENABLES ZLIB
INC       = -I./nifticlib-2.0.0/niftilib -I./nifticlib-2.0.0/znzlib
SRC       = ./nifticlib-2.0.0/znzlib/znzlib.c
SRC      += ./nifticlib-2.0.0/niftilib/nifti1_io.c
LIB       = -lz -lm

all:
	rm -rf readNifti;
	$(CXX) $(CXXFLAGS) $(INC) $(SRC) -o readNifti readNifti.cpp $(LIB)
	
clean:
	rm -rf readNifti;
	
