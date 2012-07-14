#ifndef _EXCP_H_
# define _EXCP_H_

#include <iostream>

class excp : public std::exception
{
public:
  excp();
  excp(const std::string& s);
  virtual ~excp() throw();
  virtual const char* what() const throw();
private:
  std::string	_s;
};

#endif
