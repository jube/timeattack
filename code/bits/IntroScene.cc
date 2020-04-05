#include "IntroScene.h"

#include <gf/Log.h>
#include <gf/Unused.h>

#include "Settings.h"
#include "TimeAttack.h"

namespace ta {

  IntroScene::IntroScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_fullscreenAction("Fullscreen")
  , m_checkered(game.resources)
  {
    setClearColor(gf::Color::White);

    m_fullscreenAction.addKeycodeKeyControl(gf::Keycode::F);
    addAction(m_fullscreenAction);

    addHudEntity(m_checkered);
  }

  void IntroScene::doHandleActions(gf::Window& window) {
    if (m_fullscreenAction.isActive()) {
      window.toggleFullscreen();
    }
  }

}
