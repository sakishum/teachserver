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

        int fd = p->getfd();
        if ( 0 == fd){
            fd = SINGLE->map_id_fd.value(p->getid());
        }

        if (0 == fd) {
            printf("big error!\n");
        }

        MSG_HEAD* pp = (MSG_HEAD*)p->ptr();
        if ( pp->cType > 9999 ) {
            struct sGetAllStudentInfo* xxx = (struct sGetAllStudentInfo*)pp->cData();
            printf("id %d pic %s  --  len:=%d\n", xxx->iStudentId, xxx->sPicName, pp->cLen);

        }

        //int len = send(fd, p->ptr(), p->size(), 0);

        int written_bytes;
        int bytes_left = p->size();
        char* ptr = (char*)p->ptr();

        while (bytes_left > 0)
        {
            written_bytes = send (fd, ptr, bytes_left, 0);
            if (errno == EINTR)
            {
                if (written_bytes < 0) written_bytes = 0;
                continue;
            }
            else if (errno == EAGAIN)
            {
                if (written_bytes < 0) written_bytes = 0;
                sleep (1);
                continue;
            }
            else break;

            bytes_left -= written_bytes;
            ptr += written_bytes;
        }

        printf("send success[%d];\n", fd);
        cout << "len = " << p->size ();

        p->reset();
        SINGLE->bufpool.free(p);
    }
    return 0;
}
