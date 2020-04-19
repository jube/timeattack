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
    void doRender(gf::RenderTarget& target, const gf::RenderStates &states) override;

  protected:
    TimeAttack& m_game;

    gf::Action m_fullscreenAction;
    gf::Action m_escapeAction;

  private:
    CheckeredEntity m_checkered;
  };

}

#endif // TA_INTRO_SCENE_H
