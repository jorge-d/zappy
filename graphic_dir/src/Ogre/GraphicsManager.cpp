// Header
// Header
// Header
// Header
// Header
// Header
// Header
// Header

#include "GraphicsManager.h"
#include "NetworkManager.h"
#include "CEGUIManager.h"
#include "Constants.h"
#include "PlayersManager.h"
#include "Tools.h"
#include <OgreResourceManager.h>

//-------------------------------------------------------------------------------------
GraphicsManager::GraphicsManager(void)
  : mCEGUIMgr(NULL), mNetworkMgr(NULL),
    mRayScnQuery(NULL), mode_(Constants::CEGUI),
    selectedMap(std::make_pair(-1, -1)),
    mGrid(zappy::Grid::getInstance()),
    wasConnected(false)
{
}

//-------------------------------------------------------------------------------------
GraphicsManager::~GraphicsManager(void)
{

}

//-------------------------------------------------------------------------------------
void
GraphicsManager::initialize(void)
{
  this->mPlayersMgr.initialize(&this->mGrid.getPlayers(), this->mSceneMgr, this->mGrid.getTime());
  this->mBoxesMgr.initialize(&this->mGrid.getBoxes(), this->mSceneMgr);
}

//-------------------------------------------------------------------------------------
void
GraphicsManager::createScene(void)
{
  mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());
  this->mCEGUIMgr = new CEGUIManager(this);
  this->mNetworkMgr = new NetworkManager(this);

  this->mCEGUIMgr->setLayout("Connect.layout");
  this->mCEGUIMgr->setLayout("Time.layout", false);
  this->mCEGUIMgr->setLayout("Bag.layout", false);
  this->mCEGUIMgr->setLayout("Map.layout", false);

  this->mCEGUIMgr->setupConnectLayout(this->mNetworkMgr);
  this->mCEGUIMgr->setupTimeLayout(this->mNetworkMgr);
  this->mCEGUIMgr->setupBagLayout(this);
  this->mCEGUIMgr->setupMapLayout(this);
  this->mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");
}

//-------------------------------------------------------------------------------------
void
GraphicsManager::clearAll(void)
{
  this->mPlayersMgr.clear();
  this->mBoxesMgr.clear();
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  Ogre::Vector3 camPos = mCamera->getPosition();

  if(mWindow->isClosed() || mShutDown)
    return false;
  mKeyboard->capture();
  mMouse->capture();

  mTrayMgr->frameRenderingQueued(evt);
  if (this->mode_ != Constants::CEGUI)
    mCameraMan->frameRenderingQueued(evt);
  if (this->mNetworkMgr->isConnected())
    {
      this->mPlayersMgr.update(evt);
      this->mCEGUIMgr->update();
      if (this->mTimer->getMilliseconds() >= 400)
        {
          this->mNetworkMgr->update();
          this->mTimer->reset();
        }
      this->wasConnected = true;
    }
  if (camPos.y <= 0)
    mCamera->setPosition(camPos.x, 1.0f, camPos.z);
  return true;
}

//-------------------------------------------------------------------------------------
bool GraphicsManager::keyPressed(const OIS::KeyEvent &arg)
{
  if (this->mode_ == Constants::CAMERA_FOLOW && arg.key == OIS::KC_Q)
    {
      this->mode_ = Constants::CAMERA;
      this->mCEGUIMgr->showCursor();
      this->mCameraMan->setStyle(OgreBites::CS_FREELOOK);
    }
  if (this->mode_ == Constants::CEGUI)
    this->mCEGUIMgr->keyDown(arg);
  else
    this->mCameraMan->injectKeyDown(arg);
  if (arg.key == OIS::KC_SYSRQ)
    this->mWindow->writeContentsToTimestampedFile("ScreenShot", ".jpg");
  if (arg.key == OIS::KC_ESCAPE)
    mShutDown = true;
  return true;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::keyReleased(const OIS::KeyEvent &arg)
{
  if (this->mode_ == Constants::CEGUI)
    this->mCEGUIMgr->keyUp(arg);
  else
    this->mCameraMan->injectKeyUp(arg);
  return true;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::selectMap(const Ogre::Ray &ray)
{
  std::pair<bool, Ogre::Real> intersect = ray.intersects(this->plan);

  if (intersect.first)
    {
      Ogre::Vector3 point;

      point = ray.getPoint(intersect.second);
      if (point.x >= 0 && point.x <= this->mGrid.getX() * Constants::SquareSize &&
          point.z >= 0 && point.z <= this->mGrid.getY() * Constants::SquareSize)
        {

	  unsigned int x = point.x / Constants::SquareSize;
	  unsigned int y = point.z / Constants::SquareSize;
	  this->mNetworkMgr->updateBox(x, y);
          this->mCEGUIMgr->show("Map");
          this->selectedMap.first = x;
          this->selectedMap.second = y;
          this->selected = Constants::GROUND;
          return true;
        }
    }
  return false;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::selectPlayer(const Ogre::Ray &ray)
{
  if (this->selectedPlayer.first)
    this->selectedPlayer.first->showBoundingBox(false);
  this->mRayScnQuery->setRay(ray);
  this->mRayScnQuery->setSortByDistance(true);
  this->mRayScnQuery->setQueryMask(Constants::PLAYER_MASK);
  Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
  Ogre::RaySceneQueryResult::iterator iter = result.begin();
  if (iter != result.end() && iter->movable)
    {
      if (iter->movable->getName().substr(0, 3) == "Pla")
        {
          this->mCEGUIMgr->show("Bag");
          this->selectedPlayer.first = iter->movable->getParentSceneNode();
          this->selectedPlayer.first->showBoundingBox(true);
          unsigned int id = this->getPlayerId();
          this->selectedPlayer.second = this->mGrid.getPlayer(id);
          this->selected = Constants::PLAYER;
          this->mNetworkMgr->updateBag(id);
          return true;
        }
    }
  return false;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::selectObject(const OIS::MouseEvent &arg)
{
  CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
  Ogre::Ray mouseRay = mCamera->
    getCameraToViewportRay(mousePos.d_x / float(arg.state.width),
                           mousePos.d_y / float(arg.state.height));

  this->selected = Constants::EMPTY;
  if (!this->selectPlayer(mouseRay))
    return this->selectMap(mouseRay);
  return true;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::mouseMoved(const OIS::MouseEvent &arg)
{
  this->mCEGUIMgr->mouseMove(arg);
  if (this->mode_ == Constants::CAMERA_DRAG ||
      this->mode_ == Constants::CAMERA_FOLOW)
    mCameraMan->injectMouseMove(arg);
  return true;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  this->mCEGUIMgr->mouseDown(id);
  if (id == OIS::MB_Right || this->mode_ == Constants::CAMERA_FOLOW)
    {
      if (this->mode_ != Constants::CAMERA_FOLOW)
        {
          this->mCEGUIMgr->hideCursor();
          this->mode_ = Constants::CAMERA_DRAG;
        }
      mCameraMan->injectMouseDown(arg, id);
    }
  else if (id == OIS::MB_Left)
    {
      if (this->mNetworkMgr->isConnected() &&
          this->mCEGUIMgr->isMouseOverRoot())
        {
          this->selectObject(arg);
          this->mode_ = Constants::CAMERA;
        }
      else
        {
          this->mode_ = Constants::CEGUI;
        }
    }
  return true;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  this->mCEGUIMgr->mouseUp(id);
  if (this->mode_ == Constants::CAMERA_DRAG && id == OIS::MB_Right)
    {
      this->mCEGUIMgr->showCursor();
      this->mode_ = Constants::CAMERA;
    }
  if (this->mode_ != Constants::CEGUI)
    mCameraMan->injectMouseUp(arg, id);
  return true;
}

//-------------------------------------------------------------------------------------
void
GraphicsManager::hide(const char *widget) const
{
  this->mCEGUIMgr->hide(widget);
}

//-------------------------------------------------------------------------------------
void
GraphicsManager::createRealScene(void)
{
  this->initialize();
  this->mode_ = Constants::CAMERA;
  this->mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");
  this->mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
  this->mCEGUIMgr->show("Time");
  int columns = this->mGrid.getX();
  int rows = this->mGrid.getY();

  //  World plane
  this->plan = Ogre::Plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().
    createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan,
                columns * Constants::SquareSize, rows * Constants::SquareSize, 1, 1,
                true, 1, 2, 2, Ogre::Vector3::UNIT_Z);
  Ogre::Entity *ent = mSceneMgr->createEntity("EntGround", "ground");
  Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->
    createChildSceneNode(Ogre::Vector3((Constants::SquareSize * columns) / 2 ,
                                       0,
                                       (Constants::SquareSize * rows) / 2),
                         Ogre::Quaternion::IDENTITY);
  node->attachObject(ent);
  ent->setMaterialName("Examples/GrassFloor");
  ent->setQueryFlags(Constants::GROUND_MASK);
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::hideBag(const CEGUI::EventArgs&)
{
  this->hide("Bag");
  this->mode_ = Constants::CAMERA;
  this->mNetworkMgr->unset(Constants::PLAYER);
  return true;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::hideMapScr(const CEGUI::EventArgs&)
{
  this->hide("Map");
  this->mode_ = Constants::CAMERA;
  this->mNetworkMgr->unset(Constants::GROUND);
  return true;
}

//-------------------------------------------------------------------------------------
bool
GraphicsManager::followPlayer(const CEGUI::EventArgs&)
{
  this->mode_ = Constants::CAMERA_FOLOW;
  this->mCameraMan->setStyle(OgreBites::CS_ORBIT);
  this->mCameraMan->setTarget(this->selectedPlayer.first);
  this->hide("Bag");
  return true;
}

//-------------------------------------------------------------------------------------
unsigned int
GraphicsManager::getPlayerId(void) const
{
  const Ogre::String &name = this->selectedPlayer.first->getName();
  return StringToNumber<std::string, unsigned int>(name.substr(strlen(PLAYERNODENAME), name.length()));
}

//-------------------------------------------------------------------------------------
const unsigned int *
GraphicsManager::getCurrentRessource(void) const
{
  if (this->selected == Constants::PLAYER)
    return this->selectedPlayer.second->getAllBag();
  else if (this->selected == Constants::GROUND)
    return this->mGrid.getBox(this->selectedMap.first,
                              this->selectedMap.second).getElements();
  return NULL;
}

//-------------------------------------------------------------------------------------
unsigned int
GraphicsManager::getPlayerLevel(void) const
{
  if (this->selectedPlayer.first)
    return this->selectedPlayer.second->getLevel();
  return 0;
}

//-------------------------------------------------------------------------------------
std::string
GraphicsManager::getCurrentName(void) const
{
  if (this->selected == Constants::PLAYER)
    {
      std::string name;

      name = this->selectedPlayer.second->getTeamNbr() + " - " +
        NumberToString<unsigned int>(this->selectedPlayer.second->getId());
      return name;
    }
  else if (this->selected == Constants::GROUND)
    return NumberToString<int>(this->selectedMap.first) + " - " +
      NumberToString<int>(this->selectedMap.second);
  return 0;
}
