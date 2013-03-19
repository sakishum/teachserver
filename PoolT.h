/**
 * @author  liuyuncheng
 * @version  1.0
 * @{
 */
#ifndef _POOLT_H_
#define _POOLT_H_
#include <queue>
#include <iostream>
#include <time.h>
#include <pthread.h>

#include "Mutex.h"
using namespace std;

/**
 * @class   PoolT
 * @brief   memory pool
 */
template<typename TYPE>
class PoolT {
public:
    /**
     * @brief   constructor
     */
    PoolT(int n = 1000) {
        this->size_ = n;
        for (int i = 0; i < this->size_; i++) {
            TYPE* p = new TYPE;
            this->queue_.push(p);
        }
    }
    /**
     * @brief   destructor
     */
    ~PoolT() {
        for (int i = 0; i < this->size_; i++) {
            TYPE* p = this->queue_.front();
            this->queue_.pop();
            delete p;
        }
    }

    TYPE* malloc() {
        MutexLockGuard guard(lock_);
        TYPE* p = queue_.front();
        queue_.pop();
        return p;
    }

    int free(TYPE* i) {
        MutexLockGuard guard(lock_);
        queue_.push(i);
        return 0;
    }

    size_t size() {
        return size;
    }

private:
    queue<TYPE*> queue_;
    MutexLock lock_;
    int size_;
};
/**
 * @}
 */
#endif
