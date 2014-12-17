
EXE=splatman
GPP=g++
OBJ=main.o application.o board.o player.o ghost.o actor.o graphics.o
CFLAGS=-Wall -g
LIBS=-lglfw -lGL -lGLU -lpng

all: $(OBJ)
	$(GPP) $(OBJ) -o $(EXE) $(CFLAGS) $(LIBS)

.cc.o:
	$(GPP) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXE)
