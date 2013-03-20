CPP=ccache g++ 
CC=ccache gcc
CFLAGS=-Wall -Werror -g
LINKS	= -lpthread -lrt -lev -lglog -lmysqlcppconn -llua5.2

OBJS	= ThreadPool.o \
		  ProcessManager.o \
		  Single.o \
		  Sock.o \
		  Evloop.o \
		  RecvTask.o \
		  SendTask.o \
		  database.o \
		  Config.o \
		  main.o

EXE=server

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
