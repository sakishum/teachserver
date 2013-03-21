#ifndef TWOMAP_H_
#define TWOMAP_H_
#include <map>
#include "Mutex.h"

using namespace std;
template<typename T1, typename T2>
class twomapT{
  public:
  twomapT(){};
  ~twomapT(){};
  void insert(T1 k, T2 v) {
    MutexLockGuard grard(lock_);
    kv_.erase(k);
    vk_.erase(v);
    kv_.insert(pair<T1, T2>(k, v));
    vk_.insert(pair<T2, T1>(v, k));
  }

  T2 value(T1 k) {
    T2 value;
    MutexLockGuard grard(lock_);
    value = kv_[k];
    return value;
  }

  T1 key(T2 v) {
    T1 key;
    MutexLockGuard grard(lock_);
    key = vk_[v];
    return key;
  }
void delkey(T1 k) {
    MutexLockGuard grard(lock_);
    T2 value = kv_[k];
    kv_.erase(k);
    vk_.erase(value);
  }
  void delvalue(T2 v) {
    MutexLockGuard grard(lock_);
    T2 key = vk_[v];
    kv_.erase(key);
    vk_.erase(v);
  }

  private:
  map<T1, T2> kv_;
  map<T2, T1> vk_;
  MutexLock lock_;
};
#endif
