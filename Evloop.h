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
#include <list>
#include <ev.h>

#include "Mutex.h"
#include "task.h"
#include "Single.h"
#include "Buf.h"
#include "Sock.h"
#include "AtomicT.h"
#define SERVADDR "127.0.0.1"
#define SERVPORT 8888
class Evloop: public task{
    public:
        Evloop();
        ~Evloop();
        virtual int work();
        static void accept_cb(struct ev_loop *loop, ev_io *w, int revents);
        static void recv_cb(struct ev_loop *loop, ev_io *w, int revents);

    private:
        int recvbuf(int fd);
        int startlisten();
        int listenfd_;
};
#endif
