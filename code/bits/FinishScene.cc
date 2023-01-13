#include "FinishScene.h"

#include <cassert>

#include "TimeAttack.h"

#include <gf/Log.h>

namespace ta {

  namespace {

    constexpr
    gf::Time getAdditionalTimeFromDifficulty(RaceDifficulty difficulty, RaceGround ground) {
      switch (ground) {
        case RaceGround::Sand:
        case RaceGround::Dirt:
          switch (difficulty) {
            case RaceDifficulty::Easy:
              return gf::seconds(25);
            case RaceDifficulty::Medium:
              return gf::seconds(20);
            case RaceDifficulty::Hard:
              return gf::seconds(15);
            case RaceDifficulty::Challenging:
              return gf::seconds(10);
          }
          break;
        case RaceGround::Asphalt:
          switch (difficulty) {
            case RaceDifficulty::Easy:
              return gf::seconds(20);
            case RaceDifficulty::Medium:
              return gf::seconds(15);
            case RaceDifficulty::Hard:
              return gf::seconds(10);
            case RaceDifficulty::Challenging:
              return gf::seconds(5);
          }
          break;
      }

      return gf::seconds(5);
    }

  }

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

  void FinishScene::doProcessEvent([[maybe_unused]] gf::Event& event) {
  }

  void FinishScene::doHandleActions([[maybe_unused]] gf::Window& window) {
  }

  void FinishScene::doUpdate([[maybe_unused]] gf::Time time) {
    if (!isActive()) {
      return;
    }

    ++m_game.state.currentStage;

    if (m_game.state.currentStage < m_game.data.races[m_game.state.currentRace].stages.size()) {
      gf::Log::debug("Next!\n");
      auto& race = m_game.data.races[m_game.state.currentRace];
      m_game.state.timer.addTime(getAdditionalTimeFromDifficulty(race.difficulty, race.ground));
      m_game.startRace();
    } else {
      gf::Log::debug("The end!\n");
      m_game.replaceScene(m_game.result, m_game.zoomBlur, gf::seconds(1));
    }
  }

}
