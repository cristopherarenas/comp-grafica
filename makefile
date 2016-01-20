OBJS = main.cpp
CC = g++
LIBS = -lGL -lglut -lGLU -lSOIL

all:
	$(CC) $(OBJS) -o proyecto $(LIBS)
	./proyecto

