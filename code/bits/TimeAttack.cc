#include "TimeAttack.h"

namespace ta {

  TimeAttack::TimeAttack(gf::Path searchDirectory)
  : gf::SceneManager("Time Attack!", gf::vec(1280, 720))
  , resources({ searchDirectory })
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
    state.timer.reset(gf::seconds(60.0f));
    state.chrono.startRace();
  }

  void TimeAttack::startRace() {
    state.loadPhysics(data);
    replaceScene(countdown, zoomBlur, gf::seconds(1));
    state.chrono.startStage();
  }

}
