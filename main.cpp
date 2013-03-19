#include <stdio.h>
#include "ThreadPool.h"
#include "AtomicT.h"
#include "PoolT.h"
#include "Buf.h"

#include "ProcessManager.h"

int main(int argc, char* argv[]){
#if 1
    ProcessManager* x = new ProcessManager();
    x->process_logic(argc, argv);
    delete x;
#endif
#if 0
    ThreadPool p(10);
    p.start();
    //for(int i = 0; i < 10; i++){
    while(1){
        task1* x = new task1();
        p.push_task(x);
    }
    sleep(1);
    p.stop();
#endif
#if 0
    PoolT<Buf> xxx;
    Buf* p= xxx.malloc();
    xxx.free(p);
#endif
    return 0;
}
