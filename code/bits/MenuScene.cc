#include "MenuScene.h"

#include <gf/Log.h>
#include <gf/Unused.h>

#include "Settings.h"
#include "TimeAttack.h"

namespace ta {

  MenuScene::MenuScene(TimeAttack& game)
  : IntroScene(game)
  , m_traffic(game.atlas, game.random)
  , m_choice(MenuChoice::None)
  , m_menu(game.resources, m_choice)
  {
    addWorldEntity(m_traffic);
    addHudEntity(m_menu);
  }

  void MenuScene::doProcessEvent(gf::Event& event) {
    switch (event.type) {
      case gf::EventType::MouseMoved:
        m_menu.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        break;

      case gf::EventType::MouseButtonPressed:
        m_menu.pointTo(m_game.computeWindowToGameCoordinates(event.mouseButton.coords, getHudView()));
        m_menu.triggerAction();
        break;

      default:
        break;
    }
  }

  void MenuScene::doHandleActions(gf::Window& window) {
    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (m_escapeAction.isActive()) {
      m_game.popAllScenes();
    }
  }

  void MenuScene::doUpdate(gf::Time time) {
    gf::unused(time);

    switch (m_choice) {
      case MenuChoice::None:
        break;
      case MenuChoice::Start:
        m_game.replaceScene(m_game.carChoice, m_game.fade, gf::milliseconds(200));
        break;
      case MenuChoice::Help:
        m_game.replaceScene(m_game.help, m_game.fade, gf::milliseconds(200));
        break;
      case MenuChoice::Credits:
        break;
      case MenuChoice::Quit:
        m_game.popAllScenes();
        break;
    }

    m_choice = MenuChoice::None;
  }

}
