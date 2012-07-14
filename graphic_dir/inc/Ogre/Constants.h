// Header
// Header
// Header
// Header
// Header
// Header
// Header
// Header

#ifndef __CONSTANTS_H_
# define __CONSTANTS_H_

#include "OgreMain.h"

#define PLAYERNODENAME "RobotNode"

namespace Constants
{
  enum QueryFlags
    {
      GROUND_MASK = 1 << 0,
      PLAYER_MASK = 1 << 1
    };

  enum Mode
    {
      CEGUI,
      CAMERA,
      CAMERA_DRAG,
      CAMERA_FOLOW
    };

  enum Visible
    {
      CONNECT,
      BAG,
      MAP,
      NONE
    };

  enum Selected
    {
      PLAYER,
      GROUND,
      EMPTY
    };

  static const unsigned int SquareSize = 100;
  static const unsigned int PenguinSize = 23;
  static const Ogre::Real timeUnit = 7;
  static const Ogre::Real Scale = 0.15f;
  static const int nbElem = 7;
  static const int Gap = 7;
}

#endif
