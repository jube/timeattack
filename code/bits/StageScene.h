#ifndef TA_STAGE_SCENE_H
#define TA_STAGE_SCENE_H

#include <gf/Scene.h>

#include <gfb2d/PhysicsDebugger.h>

#include "CarEntity.h"
#include "CarModel.h"
#include "MouseTracker.h"
#include "ProgressEntity.h"
#include "TimerEntity.h"

namespace ta {

  struct TimeAttack;

  class StageScene : public gf::Scene {
  public:
    StageScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    TimeAttack& m_game;
    MouseTracker m_tracker;
    gf::Action m_debugAction;


    CarEntity m_carEntity;
    CarModel m_carModel;
    TimerEntity m_timer;
    ProgressEntity m_progress;

    gfb2d::PhysicsDebugger m_debug;
  };

}


#endif // TA_STAGE_SCENE_H
