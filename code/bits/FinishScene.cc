#include "FinishScene.h"

#include "TimeAttack.h"

#include <gf/Log.h>

namespace ta {

  FinishScene::FinishScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_stage(game.data, game.state, StageEntity::Previous)
  , m_timer(game.resources, game.state.timer)
  {
    setClearColor(gf::Color::fromRgba32(0x27, 0xAE, 0x60));

    setWorldViewSize(ViewSize);
    setWorldViewCenter(ViewSize / 2);

    addWorldEntity(m_stage);

    addHudEntity(m_timer);
  }

  void FinishScene::doProcessEvent(gf::Event& event) {
  }

  void FinishScene::doHandleActions(gf::Window& window) {
  }

  void FinishScene::doUpdate(gf::Time time) {
    if (!isActive()) {
      return;
    }

    ++m_game.state.currentStage;

    if (m_game.state.currentStage < m_game.data.races[m_game.state.currentRace].stages.size()) {
      gf::Log::debug("Next!\n");
      m_game.state.timer.addTime(gf::seconds(5.0f));
      m_game.startRace();
    } else {
      gf::Log::debug("The end!\n");
      m_game.replaceScene(m_game.result, m_game.zoomBlur, gf::seconds(1));
    }
  }

}
