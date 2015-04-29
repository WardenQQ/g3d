D_BIN = bin
D_OBJ = obj

SRCS = $(filter-out test_%.c main.c, $(wildcard *.c))
OBJS = $(patsubst %.c, $(D_OBJ)/%.o, $(SRCS))
TEST_SRCS = $(wildcard test_*.c)
TEST_OBJS = $(patsubst %.c, $(D_OBJ)/%.o, $(TEST_SRCS))
TESTS = $(patsubst %.c, $(D_BIN)/%, $(TEST_SRCS))
EXEC = $(D_BIN)/extrusion

CC = gcc

CFLAGS = -O0 -g -I/usr/X11R6/include -IGL -Wall
LDFLAGS = -L/usr/X11R6/lib -lglut -lGL -lGLU -lm

print-%: ; @echo $*=$($*)

all: $(EXEC) $(TESTS)

$(D_OBJ)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(D_BIN)/test_%: $(D_OBJ)/test_%.o $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC): $(D_OBJ)/main.o $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)


clean:
	rm $(EXEC) $(OBJS) $(TESTS) $(TEST_OBJS) main.o
