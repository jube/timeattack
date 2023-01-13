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

  void CountdownScene::doUpdate([[maybe_unused]] gf::Time time) {
    if (m_countdown.isFinished()) {
      m_game.replaceScene(m_game.stage);
    }
  }

  void CountdownScene::onActivityChange(bool active) {
    if (!active) {
      return;
    }

    m_countdown.reset();
  }
}

