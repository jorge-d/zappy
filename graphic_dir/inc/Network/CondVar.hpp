/*
** main.c for my_ftp in /home/moreau_c/
** 
** Made by christopher moreau
** Login   <moreau_c@epitech.net>
** 
** Started on  Mon Mar  7 13:27:03 2011 christopher moreau
** Last update Sun Mar 13 18:21:21 2011 christopher moreau
*/

#ifndef		CONDVAR_HH_
# define	CONDVAR_HH_

# include <pthread.h>

# include "Mutex.hh"

class CondVar
{
public:
  CondVar(Mutex &m) : _m(m)
  {
    pthread_cond_init(&this->_cond, NULL);
  }

  ~CondVar()
  {
    pthread_cond_destroy(&this->_cond);
  }

  void signal(void)
  {
    pthread_cond_signal(&this->_cond);
  }

  void wait(void)
  {
    pthread_cond_wait(&this->_cond, this->_m.toPthread());
  }

  void broadcast()
  {
    pthread_cond_broadcast(&this->_cond);
  }

private:
  CondVar(CondVar const&);
  CondVar &operator=(CondVar const&);

private:
  pthread_cond_t	_cond;
  Mutex			_m;
};

#endif		// !CONDVAR_HH_
