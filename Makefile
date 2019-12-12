CC = /usr/bin/g++
#OPENGL LIBS FOR LINUX
#GLLIB :=  -lGL -lGLEW -lGLU -lglut -w
#OPENGL LIBS FOR MAC
GLLIB := -framework OpenGL -framework GLUT -w

#COMPILER FLAGS
CCFLAGS :=
#include directories
#should include gl.h glut.h etc...
INCDIR := -I/usr/include
LDLIBS := $(GLLIB)

TARGET = a.out
OBJS = main.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC)  $^ $(CCFLAGS) $(LDLIBS)  -o $@ -w

%.o : %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $(INCDIR) $< -w

clean:
	rm -rf $(OBJS) $(TARGET)
