CPP=g++
LD=g++
SPECIALFLAGS=-O3 -std=c++11 -stdlib=libc++
#SPECIALFLAGS=-g -O0
ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS = $(SPECIALFLAGS) -I.
LFLAGS = -L. 

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

SRC=dana.cpp DateTime.cpp IRcamera.cpp

all: $(SRC:.cpp=.o)
	$(LD) $(SRC:.cpp=.o) $(RLXX) -lMinuit -o dana

dana.o: dana.cpp IRcamera.h DateTime.h
	$(CPP) $(RCXX) -c dana.cpp

IRcamera.o: IRcamera.cpp IRcamera.h
	$(CPP) $(RCXX) -c IRcamera.cpp

DateTime.o: DateTime.cpp DateTime.h dataDateTime.h
	$(CPP) $(RCXX) -c DateTime.cpp

clean:
	rm -f *~ *.o
	rm -f dana
