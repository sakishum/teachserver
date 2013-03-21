CPP=ccache g++ 
CC=ccache gcc
CFLAGS=-Wall -Werror -g
LINKS	= -lpthread -lrt -lev -lglog -lmysqlcppconn -llua5.2 -lgtest

OBJS	= twomapT_unittest.o \
		  libev_unittest.o \
		  gtest_main.o

EXE=test

VPATH		 = .

INC=-I.\
	-I./../ \
	-I$(HOME)/Downloads/gtest-1.6.0/include

LIB=-L.\
	-L$(HOME)/Downloads/gtest-1.6.0/lib/.libs

all:clean $(EXE)

$(EXE):$(OBJS)
		 $(CPP) $(CFLAGS) $(LIB) $(OBJS) -o $@ $(LINKS)

%.o:%.cc
		 $(CPP) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.c
		 $(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS) 
	rm -rf $(EXE) 
	rm -rf core*
	rm -rf logs
	rm -f .lock
