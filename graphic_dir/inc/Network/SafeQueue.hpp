/*
** main.c for my_ftp in /home/moreau_c/
** 
** Made by christopher moreau
** Login   <moreau_c@epitech.net>
** 
** Started on  Mon Mar  7 13:27:03 2011 christopher moreau
// Last update Sat Apr 16 16:04:23 2011 isabel jimenez
*/

#ifndef		SAFEQUEUE_HPP_
# define	SAFEQUEUE_HPP_

# include <queue>
# include "scopedLock.hh"
# include "Mutex.hh"
# include "CondVar.hpp"

template <class T>
class SafeQueue
{
public:
  SafeQueue() : _isFinished(false), _c(this->_mutex) {};
  ~SafeQueue() {};

public:
  void push(T value)
  {
    if (!this->_isFinished)
      {
	this->_queue.push(value);
	this->_c.broadcast();
      }
  };

  bool tryPop(T *value)
  {
    if (this->_queue.empty())
      {
	this->_c.wait();
	this->_mutex.unlock();
	return (false);
      }
    else
      {
	*value = this->_queue.front();
	this->_queue.pop();
	if (!(this->_queue.empty()))
	  {
	    this->_mutex.unlock();
	    this->_c.broadcast();
	  }
	else
	  this->_mutex.unlock();
      }
    return (true);
  };

  T pop()
  {
    while (this->_queue.empty())
      {
	this->_mutex.lock();
	this->_c.wait();
	this->_mutex.unlock();
      }
    T value = this->_queue.front();
    this->_queue.pop();
    if (!(this->_queue.empty()))
      {
	this->_mutex.unlock();
	this->_c.broadcast();
      }
    else
      this->_mutex.unlock();
    return (value);
  };

  bool isFinished(void)
  {
    scopedLock s(&this->_mutex);

    if (this->_queue.empty())
      return (this->_isFinished);
    return (false);
  };

  void setFinished(void)
  {
    scopedLock s(&this->_mutex);

    this->_isFinished = true;
  };

  bool isEmpty(void) const
  {
    return (this->_queue.empty());
  };

private:
  SafeQueue(SafeQueue const&);
  SafeQueue &operator=(SafeQueue const&);

private:
  bool			_isFinished;
  Mutex			_mutex;
  std::queue<T>		_queue;
  CondVar		_c;
};

#endif		// !SAFEQUEUE_HPP_
