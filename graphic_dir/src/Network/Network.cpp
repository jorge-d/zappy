#include <cstring>
#include <unistd.h>
#include "Network.hh"

namespace zappy
{

  Network *Network::instance = NULL;
  Network::Network(std::string const &adr, int p, Convert &c) :
    _ip(adr), _port(p), _fd(0), _len(0),
    _msg_Tosend(""),
    ss(new std::stringstream(std::stringstream::in | std::stringstream::out)),
    _converter(c),
    _grid(Grid::getInstance()),
    _connected(false)
  {
    ;
  }

  Network::~Network()
  {
    ;
  }

  void Network::operator() ()
  {
    loop();
  }

  Network & Network::getInstance()
  {
    return (*instance);
  }


  Network * Network::getInstancePtr()
  {
    return (instance);
  }

  void Network::initInstance(std::string const &ad, int p, Convert &c)
  {
    if (instance == NULL)
      instance= new Network(ad, p, c);
  }

  void Network::loop()
  {
    while (_connected)
      {
	if (select_())
	  {
	    if (!writeMsg())
	      readMsg();
	    else
	      std::cout << _msg_Tosend << std::endl;
 	    while (isMsgAvailable())
	      {
		_converter.setMap(getMsg());
	      }
	  }
      }
  }

  bool Network::gettingMap() const
  {
    return _converter.getEndMap();
  }

  void Network::setToSend(const std::string &msg)
  {
    _msg_Tosend = msg;
  }

  bool Network::connect_()
  {
    struct protoent	*pe;
    struct sockaddr_in	sin;
    int yes;

    yes = 1;
    pe = NULL;
    memset(&sin, 0, sizeof(sin));
    if ((pe = getprotobyname(PROTO_TCP)) == (void*)-1)
      return (false);
    if ((_fd = socket(AF_INET,  SOCK_STREAM, pe->p_proto)) == -1)
      return (false);
    if (setsockopt(_fd, SOL_SOCKET,
		   SO_REUSEADDR, &yes, sizeof(int)) == -1)
      {
	(void)close(_fd);
	_port = 0;
	_ip.clear();
	return (false);
      }
    sin.sin_family = AF_INET;
    sin.sin_port = htons(_port);
    sin.sin_addr.s_addr = inet_addr(_ip.c_str());
    _len = sizeof(sin);
    if ((connect(_fd, (struct sockaddr*)&sin,
		 (socklen_t)_len)) == -1)
      {
	(void)close(_fd);
	_port = 0;
	_ip.clear();
	return (false);
      }
    _connected = true;
    return (true);
  }

  bool Network::isConnected()
  {
    return _connected;
  }

  bool  Network::select_()
  {
    struct timeval	tv;

    tv.tv_sec = 0;
    tv.tv_usec = 500;
    FD_ZERO(&r);
    FD_ZERO(&w);
    if (_fd != -1 && _msg_Tosend.empty())
      FD_SET(_fd, &r);
    else if (_fd != -1 && !_msg_Tosend.empty())
      FD_SET(_fd, &w);
    if (select(_fd+1, &r, &w, NULL, &tv) > 0)
      return true;
    return (false);
  }

  bool Network::isMsgAvailable()
  {
    std::string tmp;

    if (_received)
      _msg_received.clear();
    getline(*ss, tmp, '\n');
    _msg_received += tmp;
    _received =  ss->rdstate() != std::ios::eofbit;
    return (_msg_received.empty() == false && _received);
  }

  void Network::setParameters(int p, std::string const &s)
  {
    _port = p;
    _ip = s;
  }

  std::string &Network::getMsg()
  {
    return _msg_received;
  }

  bool Network::readMsg()
  {
    char buffer[1024];
    int rr = 0;

    if (FD_ISSET(_fd , &r))
      {
	if ((rr = read(_fd, buffer, 1024)) != -1)
	  {
	    if (rr == 0)
	      {
		_connected = false;
		return false;
	      }
	    ss->clear();
	    buffer[rr] = 0;
	    *ss << buffer << std::flush;
	    return (true);
	  }
      }
    return false;
  }

  bool Network::writeMsg()
  {
    if (FD_ISSET(_fd , &w))
      {
	if ((write(_fd, _msg_Tosend.c_str(), _msg_Tosend.length())) != -1)
	  {
	    _msg_Tosend.clear();
	    return (true);
	  }
      }
    return false;
  }
}
