#ifndef _PROCESSMAMAGER_H_
#define _PROCESSMAMAGER_H_
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <sys/file.h>

#include "ThreadPool.h"
#include "task.h"
#include "RecvTask.h"
#include "Evloop.h"
#include "Buf.h"
enum {
  LOCK_WAIT   = LOCK_EX,            /**<阻塞锁*/
  LOCK_NOWAIT = LOCK_EX | LOCK_NB,  /**<非阻塞锁*/
  UNLOCK      = LOCK_UN             /**<解锁*/
};

class ProcessManager
{
  public:
    ProcessManager();
    ~ProcessManager();
    int process_logic(int argc, char** argv);
    int run();
    static void sig_term(int signo);
  private:
    bool lock(int mode);
    ThreadPool* thrpool_;
    int lockfd_;
};
#endif
