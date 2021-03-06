#ifndef TA_HELP_SCENE_H
#define TA_HELP_SCENE_H

#include <gf/Scene.h>

#include "BackEntity.h"
#include "HelpEntity.h"
#include "IntroScene.h"

namespace ta {

  struct TimeAttack;

  class HelpScene : public IntroScene {
  public:
    HelpScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    HelpEntity m_help;
    BackEntity m_back;
  };

}

#endif // TA_HELP_SCENE_H
