#ifndef TA_INTRO_SCENE_H
#define TA_INTRO_SCENE_H

#include <gf/ResourceManager.h>
#include <gf/Scene.h>

#include "CheckeredEntity.h"

namespace ta {

  struct TimeAttack;

  class IntroScene : public gf::Scene {
  public:
    IntroScene(TimeAttack& game);

  private:
    void doHandleActions(gf::Window& window) override;

  private:
    TimeAttack& m_game;

    gf::Action m_fullscreenAction;

    CheckeredEntity m_checkered;
  };

}

#endif // TA_INTRO_SCENE_H
