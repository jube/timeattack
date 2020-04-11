#ifndef COUNTDOWN_SCENE_H
#define COUNTDOWN_SCENE_H

#include <gf/Scene.h>

#include "CarEntity.h"
#include "CountdownEntity.h"
#include "TimerEntity.h"

namespace ta {
  struct TimeAttack;

  class CountdownScene : public gf::Scene {
  public:
    CountdownScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    TimeAttack& m_game;

    CarEntity m_car;
    CountdownEntity m_countdown;
    TimerEntity m_timer;
  };

}

#endif // COUNTDOWN_SCENE_H
