#ifndef RECVTASK_H_
#define RECVTASK_H_
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
#include "HandleMessage.h"
class RecvTask: public task{
    public:
        RecvTask();
        ~RecvTask();
        virtual int work();
};
#endif
