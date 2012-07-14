#ifndef		THREAD_HH_
# define	THREAD_HH_

# include	<pthread.h>

template <class T>
class Thread
{
  enum status
    {
      NOT_STARTED = 0,
      STARTED,
      FINISHED
    };

public:
  Thread(T &obj) : _status(NOT_STARTED), _obj(obj)
  {
  }

  ~Thread()
  {
  }

  void		start()
  {
    this->_status = STARTED;
    pthread_create(&this->_thread, NULL, &Thread::_start, &(this->_obj));
  }

  void		*wait()
  {
    pthread_join(this->_thread, &this->_r_value);
    this->_status = FINISHED;
    return (this->_r_value);
  }

  int		status() const
  {
    return (this->_status);
  }

private:
  Thread(Thread const&);
  Thread& operator=(Thread const&);

  static void*		_start(void *param)
  {
    T* obj = reinterpret_cast<T*>(param);
    (*obj)();
    return NULL;
  }

private:
  int			_status;
  T&			 _obj;
  pthread_t		_thread;
  void			*_r_value;
};

#endif
