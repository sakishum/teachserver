#ifndef EVLOOP_H_
#define EVLOOP_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <list>
#include <time.h>

#include <ev.h>

#include "Mutex.h"
#include "task.h"
#include "Single.h"
#include "Buf.h"
#include "Sock.h"
#include "AtomicT.h"
#define SERVADDR "127.0.0.1"
#define SERVPORT 8888
#define MAXFD 10240
#define TIMEOUT 10

typedef struct ev_io_info{
    struct ev_io* io;
    ev_tstamp lasttime;
}ev_in_info;

class Evloop: public task{
    public:
        Evloop();
        ~Evloop();
        virtual int work();
        static void accept_cb(struct ev_loop *loop, ev_io *w, int revents);
        static void recv_cb(struct ev_loop *loop, ev_io *w, int revents);
        static void time_cb(struct ev_loop *loop, struct ev_timer *timer, int revents);
        static void setnoblock(int fd);
        static void closefd(int fd);
        static struct ev_loop* loop;

        //用来记录每个fd的信息，ev_io*和上次收到数据的时间
        static struct ev_io_info ioarray[MAXFD];

        static int clientcount;

    private:
        int recvbuf(int fd);
        int startlisten();
        int listenfd_;
};
#endif
