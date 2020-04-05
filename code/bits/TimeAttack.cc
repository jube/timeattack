#include "TimeAttack.h"

namespace ta {

  TimeAttack::TimeAttack(gf::Path searchDirectory)
  : gf::SceneManager("Time Attack!", gf::vec(1280, 720))
  , resources({ searchDirectory })
  , atlas("spritesheet_vehicles.xml", resources)
  , data(resources)
  , intro(*this)
  , menu(*this)
  , carChoice(*this)
  , raceChoice(*this)
  , help(*this)
  , race(*this)
  , countdown(*this)
  , stage(*this)
  , finish(*this)
  {
    startIntro();
  }


  void TimeAttack::startIntro() {
    gf::Ref<gf::Scene> scenes[] = { gf::ref(intro), gf::ref(menu) };
    pushScenes(scenes);
  }

  void TimeAttack::startRace() {
    state.loadPhysics(data);
    gf::Ref<gf::Scene> scenes[] = { gf::ref(race), gf::ref(countdown) };
    replaceAllScenes(scenes, zoomBlur, gf::seconds(1));
  }

}
