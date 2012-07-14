// Header
// Header
// Header
// Header
// Header
// Header
// Header
// Header

#include "OgreMain.h"

//-------------------------------------------------------------------------------------
OgreMain::OgreMain(void)
  : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourceMgr(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mTimer(0),
    mTrayMgr(0),
    mCameraMan(0),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0)
{
}

//-------------------------------------------------------------------------------------
OgreMain::~OgreMain(void)
{
  if (mTrayMgr)
    delete mTrayMgr;
  if (mCameraMan)
    delete mCameraMan;
  if (mTimer)
    delete mTimer;
  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
  windowClosed(mWindow);
  delete mRoot;
}

//-------------------------------------------------------------------------------------
bool OgreMain::configure(void)
{
  if (mRoot->showConfigDialog())
    {
      mWindow = mRoot->initialise(true, "Zappy interface");
      return true;
    }
  return false;
}

//-------------------------------------------------------------------------------------
void OgreMain::createCamera(void)
{
  mCamera = mSceneMgr->createCamera("PlayerCam");
  mCamera->setPosition(Ogre::Vector3(0,80,80));
  mCamera->lookAt(Ogre::Vector3(250, -1, 300));
  mCamera->setNearClipDistance(5);
  mCamera->setFarClipDistance(10000);
  mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

//-------------------------------------------------------------------------------------
void OgreMain::createFrameListener(void)
{
  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
  std::ostringstream windowHndStr;
  OIS::ParamList pl;
  size_t windowHnd = 0;

  mWindow->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  mInputManager = OIS::InputManager::createInputSystem(pl);
  mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
  mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
  mMouse->setEventCallback(this);
  mKeyboard->setEventCallback(this);
  windowResized(mWindow);
  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
  mTrayMgr = new OgreBites::SdkTrayManager("FPS", mWindow, mMouse, this);
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  mTrayMgr->toggleAdvancedFrameStats();
  mTrayMgr->hideCursor();
  mRoot->addFrameListener(this);
}

//-------------------------------------------------------------------------------------
void OgreMain::destroyScene(void)
{
}

//-------------------------------------------------------------------------------------
void OgreMain::createViewports(void)
{
  Ogre::Viewport* vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
  mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//-------------------------------------------------------------------------------------
void OgreMain::setupResources(void)
{
  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  Ogre::String secName, typeName, archName;
  while(seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;
      for(i = settings->begin(); i != settings->end(); ++i)
        {
          typeName = i->first;
          archName = i->second;
          Ogre::ResourceGroupManager::getSingleton().
            addResourceLocation(archName, typeName, secName);
        }
    }
}

//-------------------------------------------------------------------------------------
void OgreMain::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "datafiles/conf/resources_d.cfg";
    mPluginsCfg = "datafiles/conf/plugins_d.cfg";
#else
    mResourcesCfg = "datafiles/conf/resources.cfg";
    mPluginsCfg = "datafiles/conf/plugins.cfg";
#endif
    if (!setup())
        return;
    mRoot->startRendering();
    // clean up
    destroyScene();
}

//-------------------------------------------------------------------------------------
bool OgreMain::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);
    mTimer = new Ogre::Timer();
    setupResources();
    if (!configure())
      return false;
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_EXTERIOR_CLOSE, "ZappySceneMgr");
    createCamera();
    createViewports();
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(8);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    createScene();
    createFrameListener();
    return true;
};

//Adjust mouse clipping area
void OgreMain::windowResized(Ogre::RenderWindow* rw)
{
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);

  const OIS::MouseState &ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

//Unattach OIS before window shutdown(very important under Linux)
void OgreMain::windowClosed(Ogre::RenderWindow* rw)
{
  //Only close for window that created OIS(the main window in these demos)
  if (rw == mWindow)
    if (mInputManager)
      {
        mInputManager->destroyInputObject(mMouse);
        mInputManager->destroyInputObject(mKeyboard);
        OIS::InputManager::destroyInputSystem(mInputManager);
        mInputManager = 0;
      }
}
