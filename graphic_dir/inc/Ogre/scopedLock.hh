#ifndef SCOPEDLOCK_HH_
# define SCOPEDLOCK_HH_

# include "Mutex.hh"

class scopedLock
{
public:
  scopedLock(Mutex *mutex);
  ~scopedLock(void);
    
private:
  scopedLock(scopedLock &);
  scopedLock& operator=(scopedLock &);

private:
  Mutex    *_mutex;
};


#endif // !SCOPEDLOCK_HH_
