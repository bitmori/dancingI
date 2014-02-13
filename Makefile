CFLAGS= -mmacosx-version-min=10.8
LDFLAGS= -framework GLUT -framework OpenGL -framework Cocoa 

BINARIES=main

all: $(BINARIES)

clean: 
	-rm *.o $(BINARIES)

$(BINARIES) : $(BINARIES).o 
	g++ $(LDFLAGS) $^ -o $(BINARIES) 

$(BINARIES).o: $(BINARIES).cpp 
	g++ -c $(CFLAGS) $(BINARIES).cpp

depend:
	makedepend *.cpp