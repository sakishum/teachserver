#ifndef _GLOBAL_DATA_H_
#define _GLOBAL_DATA_H_
#include <stdio.h>
#include "AtomicT.h"
#include "QueueT.h"
#include "PoolT.h"
#include "Buf.h"
class Single {
    public:
        ~Single();
        static class Single* instance();
        QueueT<Buf*> sockqueue;
        PoolT<Buf> bufpool;

    private:
        Single();
        static class Single* p_;
};
#define SINGLE Single::instance()
#endif
