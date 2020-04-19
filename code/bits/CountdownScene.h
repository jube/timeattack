#ifndef COUNTDOWN_SCENE_H
#define COUNTDOWN_SCENE_H

#include <gf/Scene.h>

#include "CarEntity.h"
#include "CountdownEntity.h"
#include "ProgressEntity.h"
#include "RaceScene.h"
#include "TimerEntity.h"

namespace ta {
  struct TimeAttack;

  class CountdownScene : public RaceScene {
  public:
    CountdownScene(TimeAttack& game);

  private:
    void doUpdate(gf::Time time) override;
    void onActivityChange(bool active) override;

  private:
    CarEntity m_car;
    CountdownEntity m_countdown;
    TimerEntity m_timer;
    ProgressEntity m_progress;
  };

}

#endif // COUNTDOWN_SCENE_H
