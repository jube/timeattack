#include "ResultScene.h"

#include "TimeAttack.h"

namespace ta {

  ResultScene::ResultScene(TimeAttack& game)
  : IntroScene(game)
  , m_result(game.resources, game.data, game.state)
  , m_continue(game.resources)
  , m_chrono(game.resources, game.data, game.state)
  {
    addHudEntity(m_result);
    addHudEntity(m_continue);
    addHudEntity(m_chrono);
  }

  void ResultScene::doProcessEvent(gf::Event& event) {
    switch (event.type) {
      case gf::EventType::MouseMoved:
        m_continue.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        break;

      case gf::EventType::MouseButtonPressed:
        m_continue.pointTo(m_game.computeWindowToGameCoordinates(event.mouseButton.coords, getHudView()));
        m_continue.triggerAction();
        break;

      default:
        break;
    }
  }

  void ResultScene::doHandleActions(gf::Window& window) {
    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (m_escapeAction.isActive()) {
      m_game.replaceScene(m_game.menu, m_game.fade, gf::milliseconds(200));
    }
  }

  void ResultScene::doUpdate(gf::Time time) {
    if (m_continue.hasPressedContinue()) {
      m_game.replaceScene(m_game.menu, m_game.fade, gf::milliseconds(200));
    }
  }

}
