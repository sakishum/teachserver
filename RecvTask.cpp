#include "RecvTask.h"
RecvTask::RecvTask() {
}

RecvTask::~RecvTask() {
}

int RecvTask::work() {
    while(true){
        Buf* p = NULL;
        if (0 != SINGLE->sockqueue.dequeue(p, 3)) {
            continue;
        }
        printf("get msg: %s\n", (char*)p->ptr());

        p->reset();
        SINGLE->bufpool.free(p);
    }
    return 0;
}
