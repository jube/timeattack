#include "CountdownScene.h"

#include <cassert>

#include <gf/Color.h>

#include "TimeAttack.h"
#include "Settings.h"

namespace ta {

  CountdownScene::CountdownScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_car(game.atlas, game.state)
  , m_countdown(game.resources)
  , m_timer(game.resources, game.state.timer)
  , m_progress(game.resources, game.atlas, game.data, game.state)
  {
    setClearColor(gf::Color::fromRgba32(0x27, 0xAE, 0x60));

    setWorldViewSize(ViewSize);
    setWorldViewCenter(ViewSize / 2);

    addWorldEntity(m_countdown);
    addWorldEntity(m_car);

    addHudEntity(m_timer);
    addHudEntity(m_progress);
  }

  void CountdownScene::doProcessEvent(gf::Event& event) {

  }

  void CountdownScene::doHandleActions(gf::Window& window) {

  }

  void CountdownScene::doUpdate(gf::Time time) {
    if (m_countdown.isFinished()) {
      m_countdown.reset();
      m_game.state.timer.resume();
      m_game.replaceScene(m_game.stage);
    }
  }

}

