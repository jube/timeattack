#ifndef TA_FINISH_SCENE_H
#define TA_FINISH_SCENE_H

#include <gf/Scene.h>

#include "StageEntity.h"
#include "CarEntity.h"

namespace ta {

  struct TimeAttack;

  class FinishScene : public gf::Scene {
  public:
    FinishScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    TimeAttack& m_game;
    StageEntity m_stage;
  };

}


#endif // TA_FINISH_SCENE_H
