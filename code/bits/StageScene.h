#ifndef TA_STAGE_SCENE_H
#define TA_STAGE_SCENE_H

#include <gf/Scene.h>

#include <gfb2d/PhysicsDebugger.h>

#include "CarEntity.h"
#include "CarModel.h"
#include "MouseTracker.h"
#include "MouseParticlesEntity.h"
#include "ProgressEntity.h"
#include "RaceScene.h"
#include "SkidmarkEntity.h"
#include "TimerEntity.h"

namespace ta {

  struct TimeAttack;

  class StageScene : public RaceScene {
  public:
    StageScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;
    void onActivityChange(bool active) override;

  private:
    MouseTracker m_tracker;
    gf::Action m_pauseAction;
    gf::Action m_debugAction;


    CarEntity m_carEntity;
    CarModel m_carModel;
    TimerEntity m_timer;
    ProgressEntity m_progress;
    MouseParticlesEntity m_particles;
    SkidmarkEntity m_skidmarks;

    gfb2d::PhysicsDebugger m_debug;
  };

}


#endif // TA_STAGE_SCENE_H
