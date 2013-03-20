#include <map>
#include "Mutex.h"

template<typename T1, typename T2>
class twomapT{
  public:
  twomapT(){};
  ~twomapT(){};
  void insert(T1 k, T2 v)
  {
    MutexLockGuard grard(lock_);
    k_v.erase(k);
    v_k.erase(v);
    k_v.insert(pair<T1, T2>(k, v));
    v_k.insert(pair<T2, T1>(v, k));
  }

  T2 value(T1 k)
  {
    T2 value;
    MutexLockGuard grard(lock_);
    value = k_v[k];
    return value;
  }

  T1 key(T2 v)
  {
    T1 key;
    MutexLockGuard grard(lock_);
    key = v_k[v];
    return key;
  }

  void delkey(T1 k)
  {
    MutexLockGuard grard(lock_);
    T2 value = k_v[k];
    k_v.erase(k);
    v_k.erase(value);
  }
  void delvalue(T2 v)
  {
    MutexLockGuard grard(lock_);
    T2 key = v_k[v];
    k_v.erase(key);
    v_k.erase(v);
  }

  private:
  map<T1, T2> k_v;
  map<T2, T1> v_k;
  MutexLock lock_;
};
