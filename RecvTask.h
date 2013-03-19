#ifndef EPOLLTENTASK_H_
#define EPOLLTENTASK_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "task.h"
#include "Sock.h"
#include "Single.h"
#include "Buf.h"
class RecvTask: public task{
    public:
        RecvTask();
        ~RecvTask();
        virtual int work();
};
#endif
