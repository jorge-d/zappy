#include "Team.hh"

namespace zappy
{
  Team::Team(unsigned int i, std::string const &s) : _id(i), _name(s)
  {
    ;
  }

  Team::~Team()
  {
    ;
  }

  std::string const & Team::getTeamName() const
  {
    return (_name);
  }

  unsigned int Team::getTeamId() const
  {
    return (_id);
  }

}
