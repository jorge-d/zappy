/*
** main.c for my_ftp in /home/moreau_c
** 
** Made by christopher moreau
** Login   <moreau_c@epitech.net>
** 
** Started on  Mon Mar  7 13:27:03 2011 christopher moreau
** Last update Sun Mar 13 18:21:21 2011 christopher moreau
*/

#include <pthread.h>

#include "scopedLock.hh"

scopedLock::scopedLock(Mutex *mutex) : _mutex(mutex)
{
  this->_mutex->lock();
}

scopedLock::~scopedLock(void)
{
  this->_mutex->unlock();
}
