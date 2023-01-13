#include "IntroScene.h"

#include "Settings.h"
#include "TimeAttack.h"

namespace ta {

  IntroScene::IntroScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_fullscreenAction("Fullscreen")
  , m_escapeAction("Escape")
  , m_checkered(game.resources)
  {
    setClearColor(gf::Color::White);

    m_fullscreenAction.addKeycodeKeyControl(gf::Keycode::F);
    addAction(m_fullscreenAction);

    m_escapeAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_escapeAction);

    setWorldViewSize(IntroView.getSize());
    setWorldViewCenter(IntroView.getCenter());

  }

  void IntroScene::doRender(gf::RenderTarget& target, const gf::RenderStates &states) {
    target.setView(getHudView());
    m_checkered.render(target, states);

    renderWorldEntities(target, states);
    renderHudEntities(target, states);
  }

}
