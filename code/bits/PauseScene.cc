#include "PauseScene.h"

#include "TimeAttack.h"

namespace ta {

  PauseScene::PauseScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_continue(game.resources)
  , m_pause(game.resources)
  {
    addHudEntity(m_continue);
    addHudEntity(m_pause);
  }

  void PauseScene::doProcessEvent(gf::Event& event) {
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

  void PauseScene::doUpdate(gf::Time time) {
    if (m_continue.hasPressedContinue()) {
      m_game.popScene();
    }
  }

}
