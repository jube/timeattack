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
    setClearColor(gf::Color::fromRgba32(0x27, 0xAE, 0x60));

    m_fullscreenAction.addKeycodeKeyControl(gf::Keycode::F);
    addAction(m_fullscreenAction);

    m_escapeAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_escapeAction);

    setWorldViewSize(ViewSize);
    setWorldViewCenter(ViewSize / 2);

    addWorldEntity(m_stage);
  }

  void RaceScene::doHandleActions(gf::Window& window) {
    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }

    if (m_escapeAction.isActive()) {
      m_game.popAllScenes();
      m_game.startIntro();
    }
  }
}
