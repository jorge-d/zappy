#ifndef _TEAM_H
# define _TEAM_H

#include <string>

namespace zappy
{
  class Team
  {
    unsigned int _id;
    std::string _name;

  public:
    Team(unsigned int, std::string const &);
    ~Team();
    std::string const & getTeamName() const;
    unsigned int getTeamId() const;
  };
}

#endif
