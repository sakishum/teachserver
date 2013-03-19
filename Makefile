CPP=g++ 
CC=gcc
CFLAGS=-Wall -Werror -g
LINKS	= -lpthread -lrt -lev -lglog

OBJS	= ThreadPool.o \
		  ProcessManager.o \
		  Single.o \
		  Sock.o \
		  Evloop.o \
		  RecvTask.o \
		  main.o

EXE=a.out

BASE_DIR = .
BASE_INC = $(BASE_DIR)
BASE_SRC = $(BASE_DIR)
VPATH		 = $(BASE_DIR)

INC=-I.\
	-I$(BASE_INC) \
	-I$(BASE_SRC) \
#-I$(ACE_ROOT)

LIB=-L.\
#-L$(ACE_ROOT)/lib


all:clean $(EXE)

$(EXE):$(OBJS)
		 $(CPP) $(CFLAGS) $(LIB) $(OBJS) -o $@ $(LINKS)

%.o:%.cpp
		 $(CPP) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.c
		 $(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS) 
	rm -rf $(EXE) 
	rm -rf core*
