// Header
// Header
// Header
// Header
// Header
// Header
// Header

#include <string>
#include <iostream>
#include "CEGUIManager.h"
#include "GraphicsManager.h"

CEGUIManager::CEGUIManager(GraphicsManager *gm)
{
  this->mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
  this->mGraphicsMgr = gm;
  // Load Ressources
  CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
  CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
  CEGUI::SchemeManager::getSingleton().create("OgreTray.scheme");

  // Set mouse cursor
  CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

  // Set default Sheet
  this->mSheetMgr = CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"Root");
  CEGUI::System::getSingleton().setGUISheet(mSheetMgr);
}

//-------------------------------------------------------------------------------------
CEGUIManager::~CEGUIManager(void)
{
}

//-------------------------------------------------------------------------------------
CEGUI::Window *
CEGUIManager::getWindow(const char *widget) const
{
  CEGUI::WindowManager &winMgr = CEGUI::WindowManager::getSingleton();
  if (winMgr.isWindowPresent(widget))
    return winMgr.getWindow(widget);
  return NULL;
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::setLayout(const char* layout, bool vis) const
{
  CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window *window = winMgr.loadWindowLayout(layout);

  window->setVisible(vis);
  this->mSheetMgr->addChildWindow(window);
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::subscribeEvent(const CEGUI::String& widget,
                                  const CEGUI::String& event,
                                  const CEGUI::Event::Subscriber& method) const
{
  CEGUI::Window* window;

  if ((window = this->getWindow(widget.c_str())) != NULL)
    window->subscribeEvent(event, method);
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::setupConnectLayout(NetworkManager *slot) const
{
  this->subscribeEvent("Connect/Button", CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&NetworkManager::connect, slot));
  this->subscribeEvent("Connect/ContainerGrp/Port", CEGUI::Editbox::EventTextAccepted,
                       CEGUI::Event::Subscriber(&NetworkManager::connect, slot));
  this->subscribeEvent("Connect/ContainerGrp/Ip", CEGUI::Editbox::EventTextAccepted,
                       CEGUI::Event::Subscriber(&NetworkManager::connect, slot));

  CEGUI::Editbox *Box = dynamic_cast<CEGUI::Editbox*>(this->getWindow("Connect/ContainerGrp/Ip"));
  if (Box != NULL)
    Box->setValidationString("[0-9.]{0,16}");
  Box = dynamic_cast<CEGUI::Editbox*>(this->getWindow("Connect/ContainerGrp/Port"));
  if (Box != NULL)
    Box->setValidationString("[0-9]{0,5}");
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::setupTimeLayout(NetworkManager *slot) const
{
  this->getWindow("Time")->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0 ,0)));
  this->subscribeEvent("Time/Button", CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&NetworkManager::updateTime, slot));
  this->subscribeEvent("Time/Container/Time", CEGUI::Editbox::EventTextAccepted,
                       CEGUI::Event::Subscriber(&NetworkManager::updateTime, slot));
  CEGUI::Editbox *Box = dynamic_cast<CEGUI::Editbox*>(this->getWindow("Time/Container/Time"));
  if (Box != NULL)
    Box->setValidationString("[0-9.]{0,4}");
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::setupBagLayout(GraphicsManager *slot) const
{
  this->subscribeEvent("Bag/Container/BtnFollow", CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&GraphicsManager::followPlayer, slot));

  this->subscribeEvent("Bag/Container/BtnClose", CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&GraphicsManager::hideBag, slot));
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::setupMapLayout(GraphicsManager *slot) const
{
  this->subscribeEvent("Map/Container/BtnClose", CEGUI::PushButton::EventClicked,
                       CEGUI::Event::Subscriber(&GraphicsManager::hideMapScr, slot));
}


//-------------------------------------------------------------------------------------
void
CEGUIManager::hide(const char *widget) const
{
  CEGUI::Window* window;

  if ((window = this->getWindow(widget)) != NULL)
    window->hide();
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::show(const char *widget) const
{
  CEGUI::Window* window;

  if ((window = this->getWindow(widget)) != NULL)
    window->show();
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::showCursor(void) const
{
  CEGUI::MouseCursor::getSingleton().show();
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::hideCursor(void) const
{
  CEGUI::MouseCursor::getSingleton().hide();
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::setText(const char *widget, std::string &text) const
{
  CEGUI::Window* window;

  if ((window = this->getWindow(widget)) != NULL)
    window->setText(text);
}

//-------------------------------------------------------------------------------------
CEGUI::MouseButton
CEGUIManager::convertButton(OIS::MouseButtonID buttonID) const
{
  switch (buttonID)
    {
    case OIS::MB_Left:
      return CEGUI::LeftButton;
      break;
    case OIS::MB_Right:
      return CEGUI::RightButton;
      break;
    case OIS::MB_Middle:
      return CEGUI::MiddleButton;
      break;
    default:
      return CEGUI::LeftButton;
      break;
    }
}

//-------------------------------------------------------------------------------------
bool
CEGUIManager::isMouseOverRoot(void) const
{
  CEGUI::Window* window = CEGUI::WindowManager::getSingleton().getWindow("Root");
  if (CEGUI::System::getSingleton().getWindowContainingMouse() == window)
    return true;
  return false;
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::mouseMove(const OIS::MouseEvent &arg) const
{
  CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::mouseDown(OIS::MouseButtonID id) const
{
  CEGUI::System::getSingleton().injectMouseButtonDown(this->convertButton(id));
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::mouseUp(OIS::MouseButtonID id) const
{
  CEGUI::System::getSingleton().injectMouseButtonUp(this->convertButton(id));
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::keyUp(const OIS::KeyEvent &arg) const
{
  CEGUI::System::getSingleton().injectKeyUp(arg.key);
}

//-------------------------------------------------------------------------------------
void
CEGUIManager::keyDown(const OIS::KeyEvent &arg) const
{
  CEGUI::System &sys = CEGUI::System::getSingleton();
  sys.injectKeyDown(arg.key);
  sys.injectChar(arg.text);
}

//-------------------------------------------------------------------------------------
bool
CEGUIManager::isVisible(const char *widget) const
{
  CEGUI::Window *win;

  win = this->getWindow(widget);
  if (win && win->isVisible())
    return true;
  return false;
}


//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//--------------------------Truc degueu, a changer...----------------------------------
//-------------------------------------------------------------------------------------
void
CEGUIManager::update(void) const
{
  Constants::Visible w = Constants::NONE;

  if (this->isVisible("Bag"))
    w = Constants::BAG;
  else if (this->isVisible("Map"))
    w = Constants::MAP;
  if (w == Constants::BAG ||
      w == Constants::MAP)
    {
      const unsigned int *bag = this->mGraphicsMgr->getCurrentRessource();
      std::string name = this->mGraphicsMgr->getCurrentName();
      if (bag != NULL)
        {
          std::map<zappy::Elements, std::string> values;

          values[zappy::LINEMATE] = (NumberToString(bag[zappy::LINEMATE]));
          values[zappy::DERAUMERE] = (NumberToString(bag[zappy::DERAUMERE]));
          values[zappy::SIBUR] = (NumberToString(bag[zappy::SIBUR]));
          values[zappy::MENDIANE] = (NumberToString(bag[zappy::MENDIANE]));
          values[zappy::PHIRAS] = (NumberToString(bag[zappy::PHIRAS]));
          values[zappy::THYSTAME] = (NumberToString(bag[zappy::THYSTAME]));
          values[zappy::FOOD] = (NumberToString(bag[zappy::FOOD]));
          if (w == Constants::BAG)
            {
              this->setText("Bag/Container/Grp", name);
              this->setText("Bag/Container/Grp/L", values[zappy::LINEMATE]);
              this->setText("Bag/Container/Grp/D", values[zappy::DERAUMERE]);
              this->setText("Bag/Container/Grp/S", values[zappy::SIBUR]);
              this->setText("Bag/Container/Grp/M", values[zappy::MENDIANE]);
              this->setText("Bag/Container/Grp/P", values[zappy::PHIRAS]);
              this->setText("Bag/Container/Grp/T", values[zappy::THYSTAME]);
              this->setText("Bag/Container/Grp/F", values[zappy::FOOD]);
              std::string level = NumberToString<unsigned int>(this->mGraphicsMgr->getPlayerLevel());
	      //              std::cout << "Level = " << level << std::endl;
              this->setText("Bag/Container/Grp/Lvl", level);
            }
          else
            {
              this->setText("Map/Container/Grp", name);
              this->setText("Map/Container/Grp/L", values[zappy::LINEMATE]);
              this->setText("Map/Container/Grp/D", values[zappy::DERAUMERE]);
              this->setText("Map/Container/Grp/S", values[zappy::SIBUR]);
              this->setText("Map/Container/Grp/M", values[zappy::MENDIANE]);
              this->setText("Map/Container/Grp/P", values[zappy::PHIRAS]);
              this->setText("Map/Container/Grp/T", values[zappy::THYSTAME]);
              this->setText("Map/Container/Grp/F", values[zappy::FOOD]);
            }
        }
    }
}
