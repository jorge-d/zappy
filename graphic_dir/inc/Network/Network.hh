#ifndef _NET_H
# define _NET_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Convert.hh"
#include "Grid.hh"

# define PROTO_TCP  "TCP"

namespace zappy
{

  class Network
  {
    std::string  _ip;
    int _port;
    int _fd;
    int _len;
    static Network *instance;
    std::string _msg_Tosend;
    std::string _msg_received;
    std::stringstream *ss;
    Network(std::string const &, int, Convert &);
    fd_set r;
    fd_set w;
    Convert & _converter;
    Grid & _grid;
    bool _connected;
    bool _received;
  public:
    void operator()();
    void setToSend(const std::string &msg);
    void loop();
    bool connect_();
    bool gettingMap() const;
    bool isConnected();
    bool select_();
    void setParameters(int, std::string const &);
    std::string &getMsg();
    bool writeMsg();
    bool readMsg();
    bool isMsgAvailable();
    static void initInstance(std::string const &ad, int p, Convert &);
    static Network & getInstance();
    static Network * getInstancePtr();
    ~Network();
  };

}

#endif
