/*
  -----------------------------------------------------------------------------
  Filename:    OgreMain.h
  -----------------------------------------------------------------------------

  This source file is part of the
  ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
  //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
  / \_// (_| | | |  __/  \  /\  /| |   <| |
  \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
  |___/
  Tutorial Framework
  http://www.ogre3d.org/tikiwiki/
  -----------------------------------------------------------------------------
*/

#ifndef   	OGREMAIN_H_
# define   	OGREMAIN_H_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <GLX/OgreTimerImp.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

class OgreMain : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
  OgreMain(void);
  virtual ~OgreMain(void);

  virtual void go(void);

protected:
  virtual bool setup();
  virtual bool configure(void);
  virtual void createCamera(void);
  virtual void createFrameListener(void);
  virtual void createScene(void) = 0;
  virtual void destroyScene(void);
  virtual void createViewports(void);
  virtual void setupResources(void);
  virtual void initialize(void) = 0;

  virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;
  virtual bool keyPressed(const OIS::KeyEvent &arg ) = 0;
  virtual bool keyReleased(const OIS::KeyEvent &arg ) = 0;
  virtual bool mouseMoved(const OIS::MouseEvent &arg ) = 0;
  virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID) = 0;
  virtual bool mouseReleased(const OIS::MouseEvent &, OIS::MouseButtonID) = 0;

  //Adjust mouse clipping area
  virtual void windowResized(Ogre::RenderWindow* rw);
  //Unattach OIS before window shutdown (very important under Linux)
  virtual void windowClosed(Ogre::RenderWindow* rw);

  Ogre::Root *mRoot;
  Ogre::Camera* mCamera;
  Ogre::SceneManager* mSceneMgr;
  Ogre::RenderWindow* mWindow;
  Ogre::ResourceManager* mResourceMgr;
  Ogre::String mResourcesCfg;
  Ogre::String mPluginsCfg;
  Ogre::Timer *mTimer;

  // OgreBites
  OgreBites::SdkTrayManager* mTrayMgr;
  OgreBites::SdkCameraMan* mCameraMan;
  bool mShutDown;

  //OIS Input devices
  OIS::InputManager* mInputManager;
  OIS::Mouse*    mMouse;
  OIS::Keyboard* mKeyboard;
};

#endif 	    /* !OGREMAIN_H_ */
