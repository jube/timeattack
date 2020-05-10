#include "RaceScene.h"

#include "Settings.h"
#include "TimeAttack.h"

namespace ta {

  RaceScene::RaceScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_fullscreenAction("Fullscreen")
  , m_escapeAction("Escape")
  , m_stage(game.data, game.state)
  {
    setClearColor(gf::Color::Black);

    m_fullscreenAction.addKeycodeKeyControl(gf::Keycode::F);
    addAction(m_fullscreenAction);

    m_escapeAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_escapeAction);

    setWorldViewSize(ViewSize * 1.1f);
    setWorldViewCenter(ViewSize / 2);

    addWorldEntity(m_stage);
  }

  void RaceScene::doHandleActions(gf::Window& window) {
    handleActionsCommon(window);
  }

  void RaceScene::handleActionsCommon(gf::Window& window) {
    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (m_escapeAction.isActive()) {
      pause();
      m_game.replaceAllScenes(m_game.result, m_game.fade, gf::milliseconds(200));
    }
  }

}
