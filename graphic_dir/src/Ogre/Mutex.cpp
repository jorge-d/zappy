//
// Mutex.cpp for  in /home/catuss_a//plazza-2014-jimene_i
// 
// Made by axel catusse
// Login   <catuss_a@epitech.net>
// 
// Started on  Sun Apr 17 15:36:36 2011 axel catusse
// Last update Sun Apr 17 15:36:56 2011 axel catusse
//

#include "Mutex.hh"

Mutex::Mutex()
{
  pthread_mutex_init(&(this->_mutex), NULL);
}

Mutex::~Mutex()
{
  pthread_mutex_destroy(&(this->_mutex));
}

void		Mutex::lock()
{
  pthread_mutex_lock(&this->_mutex);
}

void		Mutex::unlock()
{
  pthread_mutex_unlock(&this->_mutex);
}

bool		Mutex::trylock()
{
  return (pthread_mutex_trylock(&this->_mutex));
}

pthread_mutex_t* Mutex::toPthread(void)
{
  return (&this->_mutex);
}

Mutex& Mutex::operator=(Mutex const& other)
{
  if (this != &other)
    {
      this->_mutex = other._mutex;
    }
  return (*this);
}

Mutex::Mutex(Mutex const& other)
{
  *this = other;
}
