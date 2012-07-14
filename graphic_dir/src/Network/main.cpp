#include "Network.hh"
#include "Convert.hh"
#include <iostream>

int main(void)
{
  zappy::Convert *c = new zappy::Convert();
  int i;
  bool f = true;

  while (f)
    {
      std::cin >> i;
      zappy::Network::initInstance("127.0.0.1", i, *c);
      zappy::Network &p = zappy::Network::getInstance();
      p.setPort(i);
      if (!p.connect_())
	{
	  std::cerr << "Can't connect to the server" << std::endl;
	}
      else
	{
	  f = false;
	  p.loop();
	}
    }

  delete c;
  return 0;
}

