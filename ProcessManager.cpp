#include "ProcessManager.h"
int work_flag; 
ProcessManager::ProcessManager() { thrpool_ = new ThreadPool(20);
}

ProcessManager::~ProcessManager() {
}

int ProcessManager::process_logic(int argc, char** argv) {
  signal(SIGINT, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGTERM, sig_term);


  int opt = getopt(argc, argv, "uds");
  if ( -1 == opt) {
    printf("argv error\n");
    return -1;
  }
  int pid = 0;
  switch(opt){
    case 's':
      if(true != lock(LOCK_NOWAIT)) {
        printf("Process already running!\n");
        return 0;
      } 
      pid = fork();
      if(0 < pid){
        return 0;
      }
    case 'd':
      this->run();
      break;
    case 'u':
      if (true == lock(LOCK_NOWAIT))
      {   
        lock(UNLOCK);
        printf("No process!\n");
      } else {
        printf("Find process! stopping...\n");
        char buf[1024] = {0};
        snprintf(buf, 1024, "killall %s", argv[0]);
        system(buf);
      }  
      printf("stop\n");
      break;
    default:
      break;
  }


  return 0;
}

void ProcessManager::sig_term(int signo) {
  printf("get exit signal\n");
  work_flag = 0;
  //raise(SIGKILL);
  return;
}

int ProcessManager::run() {
  work_flag = 1;
  printf("run\n");
  thrpool_->start();
  Evloop* evloop = new Evloop();
  RecvTask* p = new RecvTask();

  thrpool_->push_task(evloop);
  thrpool_->push_task(p);
  thrpool_->push_task(p);

  while(0 != work_flag) {
    sleep(3);
  }
  thrpool_->kill();
  printf("exit\n");
  return 0;
}

bool ProcessManager::lock(int mode) {
  char szPid[32] = {0};
  snprintf(szPid, 32, "%ld", (long)getpid());
  if (0 == lockfd_) {
    lockfd_ = open("./.lock", O_RDWR|O_CREAT, 0640);
  }
  if (lockfd_ < 0) {
    //printf("open file error!\n");
    return false;
  }
  if (0 != flock(lockfd_, mode)) {
    //printf("lock file error!\n");
    return false;
  }
  if (UNLOCK == mode) {
    close(lockfd_);
  }
  else {
    ftruncate(lockfd_, 0); 
    write(lockfd_, szPid, strlen(szPid));
    //printf("Lock success![%d]\n", lockfd_);
  }
  return true;
}

