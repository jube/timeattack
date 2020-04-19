#include "CountdownScene.h"

#include <cassert>

#include <gf/Color.h>

#include "TimeAttack.h"
#include "Settings.h"

namespace ta {

  CountdownScene::CountdownScene(TimeAttack& game)
  : RaceScene(game)
  , m_car(game.atlas, game.state)
  , m_countdown(game.resources)
  , m_timer(game.resources, game.state.timer)
  , m_progress(game.resources, game.atlas, game.data, game.state)
  {
    addWorldEntity(m_countdown);
    addWorldEntity(m_car);

    addHudEntity(m_timer);
    addHudEntity(m_progress);
  }

  void CountdownScene::doProcessEvent(gf::Event& event) {

  }

  void CountdownScene::doUpdate(gf::Time time) {
    if (m_countdown.isFinished()) {
      m_countdown.reset();
      m_game.state.timer.resume();
      m_game.replaceScene(m_game.stage);
    }
  }

}

