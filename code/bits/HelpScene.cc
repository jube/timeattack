#include "HelpScene.h"

#include <gf/Log.h>
#include <gf/Unused.h>

#include "Settings.h"
#include "TimeAttack.h"

namespace ta {

  HelpScene::HelpScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_escapeAction("Escape")
  , m_help(game.resources)
  , m_back(game.resources)
  {
    setClearColor(gf::Color::White);

    m_escapeAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_escapeAction);

    addHudEntity(m_help);
    addHudEntity(m_back);
  }

  void HelpScene::doProcessEvent(gf::Event& event) {
    switch (event.type) {
      case gf::EventType::MouseMoved:
        m_back.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        break;

      case gf::EventType::MouseButtonPressed:
        m_back.pointTo(m_game.computeWindowToGameCoordinates(event.mouseButton.coords, getHudView()));
        m_back.triggerAction();
        break;

      default:
        break;
    }
  }

  void HelpScene::doHandleActions(gf::Window& window) {
    if (m_escapeAction.isActive()) {
      m_game.replaceScene(m_game.menu, m_game.fade, gf::milliseconds(200));
    }
  }

  void HelpScene::doUpdate(gf::Time time) {
    gf::unused(time);

    if (m_back.hasPressedBack()) {
      m_game.replaceScene(m_game.menu, m_game.fade, gf::milliseconds(200));
    }
  }

}
