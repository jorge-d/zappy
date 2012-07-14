// Header
// Header
// Header
// Header
// Header
// Header
// Header

#ifndef __GRAPHICSMANAGER_H_
# define __GRAPHICSMANAGER_H_

#include <utility>

#include "OgreMain.h"
#include "CEGUIMain.h"
#include "CEGUIManager.h"
#include "NetworkManager.h"
#include "Constants.h"
#include "PlayersManager.h"
#include "BoxesManager.h"
#include "Grid.hh"

class   CEGUIManager;

class GraphicsManager : public OgreMain
{
public:
  GraphicsManager(void);
  virtual ~GraphicsManager(void);

protected:
  CEGUIManager *mCEGUIMgr;
  NetworkManager *mNetworkMgr;
  Ogre::RaySceneQuery* mRayScnQuery;
  Ogre::Plane plan;
  Constants::Mode    mode_;
  std::pair<Ogre::SceneNode *, zappy::Player *> selectedPlayer;
  std::pair<int, int> selectedMap;
  zappy::Grid & mGrid;
  PlayersManager mPlayersMgr;
  BoxesManager mBoxesMgr;
  Constants::Selected selected;
  bool wasConnected;

protected:
  virtual void createScene(void);
  virtual void initialize(void);
  virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

  // OIS::KeyListener
  virtual bool keyPressed(const OIS::KeyEvent &);
  virtual bool keyReleased(const OIS::KeyEvent &);

  // OIS::MouseListener
  virtual bool mouseMoved(const OIS::MouseEvent &);
  virtual bool mousePressed(const OIS::MouseEvent &, OIS::MouseButtonID);
  virtual bool mouseReleased(const OIS::MouseEvent &, OIS::MouseButtonID);

public:
  void hide(const char *widget) const;
  void show(const char *widget) const;
  bool hideBag(const CEGUI::EventArgs&);
  bool hideMapScr(const CEGUI::EventArgs&);
  bool followPlayer(const CEGUI::EventArgs&);
  void createRealScene(void);
  unsigned int getPlayerId(void) const;
  const unsigned int *getCurrentRessource(void) const;
  unsigned int getPlayerLevel(void) const;
  std::string getCurrentName(void) const;

private:
  bool selectObject(const OIS::MouseEvent &arg);
  bool selectMap(const Ogre::Ray &ray);
  bool selectPlayer(const Ogre::Ray &ray);
  void clearAll(void);
};

#endif // #ifndef __GRAPHICSMANAGER_H_
