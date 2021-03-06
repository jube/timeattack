#ifndef TA_RACE_SCENE_H
#define TA_RACE_SCENE_H

#include <gf/Scene.h>

#include "MouseTracker.h"
#include "StageEntity.h"

namespace ta {
  struct TimeAttack;

  class RaceScene : public gf::Scene {
  public:
    RaceScene(TimeAttack& game);

  private:
    void doHandleActions(gf::Window& window) override;

  protected:
    void handleActionsCommon(gf::Window& window);

  protected:
    TimeAttack& m_game;

  private:
    gf::Action m_fullscreenAction;
    gf::Action m_escapeAction;
    StageEntity m_stage;
  };

}

#endif // TA_RACE_SCENE_H
