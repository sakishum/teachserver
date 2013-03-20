#include "SendTask.h"
SendTask::SendTask() {
}

SendTask::~SendTask() {
}

int SendTask::work() {
    while(true){
        Buf* p = NULL;
        if (0 != SINGLE->sendqueue.dequeue(p, 3)) {
            continue;
        }
        int fd = SINGLE->mapidfd.value(p->getid());
        send_v(fd, p->ptr(), p->size());

        SINGLE->bufpool.free(p);
    }
    return 0;
}
