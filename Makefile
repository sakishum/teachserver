CPP=g++ 
CC=gcc
CFLAGS=-Wall -Werror -g
LINKS	= -lpthread -lrt -lev -lglog -lmysqlcppconn

OBJS	= ThreadPool.o \
		  ProcessManager.o \
		  Single.o \
		  Sock.o \
		  Evloop.o \
		  RecvTask.o \
		  database.o \
		  main.o

EXE=server.out

VPATH		 = .

INC=-I.\

LIB=-L.\

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
	rm -rf logs
	rm -f .lock
