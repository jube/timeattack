#include "CreditScene.h"

#include "Settings.h"
#include "TimeAttack.h"

namespace ta {

  CreditScene::CreditScene(TimeAttack& game)
  : IntroScene(game)
  , m_credit(game.resources)
  , m_back(game.resources)
  {
    addHudEntity(m_credit);
    addHudEntity(m_back);
  }

  void CreditScene::doProcessEvent(gf::Event& event) {
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

  void CreditScene::doHandleActions(gf::Window& window) {
    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (m_escapeAction.isActive()) {
      m_game.replaceScene(m_game.menu, m_game.fade, gf::milliseconds(200));
    }
  }

  void CreditScene::doUpdate([[maybe_unused]] gf::Time time) {
    if (m_back.hasPressedBack()) {
      m_game.replaceScene(m_game.menu, m_game.fade, gf::milliseconds(200));
    }
  }

}
