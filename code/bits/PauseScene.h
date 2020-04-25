#ifndef TA_PAUSE_SCENE_H
#define TA_PAUSE_SCENE_H

#include <gf/Scene.h>

#include "ContinueEntity.h"
#include "PauseEntity.h"

namespace ta {

  struct TimeAttack;

  class PauseScene : public gf::Scene {
  public:
    PauseScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doUpdate(gf::Time time) override;

  private:
    TimeAttack& m_game;
    ContinueEntity m_continue;
    PauseEntity m_pause;
  };

}

#endif // TA_PAUSE_SCENE_H
