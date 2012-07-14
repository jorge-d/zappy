#include "Network.hh"

#include <iostream>
int main()
{
  zappy::Network::initInstance("127.0.0.1", 1324);
  zappy::Network N = zappy::Network::getInstance();
  
  if (N.connect_())
    if (N.select_())
      {
	std::string s(N.getMsg().begin(), N.getMsg().end());
	std::cout << N.getMsg()[0] << std::endl;
	std::cout << N.getMsg()[1] << std::endl;
      }
    else
      std::cout << "pas de read";
  else
  std::cout << "pas de connect";
  //std::string t( v.begin(), v.end() );
}
