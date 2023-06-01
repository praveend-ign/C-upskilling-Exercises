#makefile with rules to compile the C source files
CC = gcc
CC_FLAGS = -g
LD_FLAGS = -L/usr/lib
TARGET = math_ds_prog
RM = rm -f

default: all

main.o: main.c
	$(CC) $(CC_FLAGS) -c $<

math.o: math.c
	$(CC) $(CC_FLAGS) -c $<

search.o: search.c
	$(CC) $(CC_FLAGS) -c $<

sort.o: sort.c
	$(CC) $(CC_FLAGS) -c $<

util.o: util.c
	$(CC) $(CC_FLAGS) -c $<

all: math.o util.o search.o sort.o main.o
	$(CC) $(CC_FLAGS) $(LD_FLAGS) -o $(TARGET) $?

clean:
	$(RM) *.o $(TARGET)

