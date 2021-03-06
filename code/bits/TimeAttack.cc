#include "TimeAttack.h"

#include <gf/Paths.h>

namespace ta {

  namespace {

    constexpr
    gf::Time getInitialTimeFromDifficulty(RaceDifficulty difficulty, RaceGround ground) {
      switch (ground) {
        case RaceGround::Sand:
          switch (difficulty) {
            case RaceDifficulty::Easy:
              return gf::seconds(45);
            case RaceDifficulty::Medium:
              return gf::seconds(50);
            case RaceDifficulty::Hard:
              return gf::seconds(55);
            case RaceDifficulty::Challenging:
              return gf::seconds(60);
          }
          break;
        case RaceGround::Dirt:
        case RaceGround::Asphalt:
          switch (difficulty) {
            case RaceDifficulty::Easy:
              return gf::seconds(30);
            case RaceDifficulty::Medium:
              return gf::seconds(40);
            case RaceDifficulty::Hard:
              return gf::seconds(50);
            case RaceDifficulty::Challenging:
              return gf::seconds(60);
          }
          break;
      }


      return gf::seconds(5);
    }

  }

  TimeAttack::TimeAttack(gf::Path searchDirectory)
  : gf::SceneManager("Time Attack!", gf::vec(1280, 720))
  , resources({ searchDirectory, gf::Paths::getBasePath() / "assets" })
  , atlas("spritesheet_vehicles.xml", resources)
  , data(resources)
  , menu(*this)
  , carChoice(*this)
  , raceChoice(*this)
  , help(*this)
  , credit(*this)
  , countdown(*this)
  , stage(*this)
  , finish(*this)
  , result(*this)
  , pause(*this)
  {
    startIntro();
  }


  void TimeAttack::startIntro() {
    pushScene(menu);
  }

  void TimeAttack::setupRace(std::size_t raceIndex) {
    state.currentRace = raceIndex;
    state.currentStage = 0;
    state.timer.reset(getInitialTimeFromDifficulty(data.races[state.currentRace].difficulty, data.races[state.currentRace].ground));
    state.chrono.startRace();
  }

  void TimeAttack::startRace() {
    state.loadPhysics(data);
    replaceScene(countdown, zoomBlur, gf::seconds(1));
    state.chrono.startStage();
  }

}
