#include "excp.hh"

excp::excp(): _s("Execption")
{
}

excp::excp(const std::string& s): _s(s)
{
}

excp::~excp() throw()
{
}

const char* excp::what() const throw()
{
  return (this->_s.c_str());
}
