// Header
// Header
// Header
// Header
// Header
// Header
// Header


#ifndef __CEGUIMANAGER_H__
# define __CEGUIMANAGER_H__

#include "CEGUIMain.h"
#include "NetworkManager.h"
#include "GraphicsManager.h"
#include "Tools.h"

//class           GraphicsManager;

class		CEGUIManager
{
protected:
  GraphicsManager *mGraphicsMgr;
  CEGUI::OgreRenderer* mRenderer;
  CEGUI::Window *mSheetMgr;

public:
  CEGUIManager(GraphicsManager *);
  ~CEGUIManager(void);

public:
  void  setLayout(const char*, bool show = true) const;
  void	subscribeEvent(const CEGUI::String& widget, const CEGUI::String& event, const CEGUI::Event::Subscriber& method) const;
  void  setupConnectLayout(NetworkManager *slot) const;
  void  setupTimeLayout(NetworkManager *slot) const;
  void  setupBagLayout(GraphicsManager *slot) const;
  void  setupMapLayout(GraphicsManager *slot) const;
  void  hide(const char *widget) const;
  void  show(const char *widget) const;
  void  showCursor(void) const;
  void  hideCursor(void) const;
  void  setText(const char *widget, std::string &text) const;
  CEGUI::Window *getWindow(const char *widget) const;
  void update(void) const;
  bool isVisible(const char *widget) const;


public:
  CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID) const;
  bool isMouseOverRoot(void) const;
  void mouseMove(const OIS::MouseEvent &arg) const;
  void mouseDown(OIS::MouseButtonID id) const;
  void mouseUp(OIS::MouseButtonID id) const;
  void keyUp(const OIS::KeyEvent &arg) const;
  void keyDown(const OIS::KeyEvent &arg) const;
};

#endif // #__CEGUIMANAGER_H__
