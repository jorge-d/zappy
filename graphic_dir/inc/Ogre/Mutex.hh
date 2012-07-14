//
// Mutex.hh for  in /home/catuss_a//plazza-2014-jimene_i
// 
// Made by axel catusse
// Login   <catuss_a@epitech.net>
// 
// Started on  Sun Apr 17 15:36:06 2011 axel catusse
// Last update Sun Apr 17 15:36:07 2011 axel catusse
//

#ifndef		MUTEX_HH_
# define	MUTEX_HH_

# include <pthread.h>

class Mutex
{
public:
  Mutex();
  ~Mutex(void);

  Mutex& operator=(Mutex const&);
  Mutex(Mutex const&);
public:
  void lock(void);
  void unlock(void);
  bool trylock(void);
  pthread_mutex_t* toPthread(void);

private:
  pthread_mutex_t	_mutex;
};

#endif		// !IMUTEX_HH_
