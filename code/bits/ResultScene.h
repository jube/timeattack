#ifndef TA_RESULT_SCENE_H
#define TA_RESULT_SCENE_H

#include <gf/Scene.h>

#include "ChronoEntity.h"
#include "ContinueEntity.h"
#include "IntroScene.h"
#include "ResultEntity.h"

namespace ta {

  struct TimeAttack;

  class ResultScene : public IntroScene {
  public:
    ResultScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    ResultEntity m_result;
    ContinueEntity m_continue;
    ChronoEntity m_chrono;
  };

}


#endif // TA_RESULT_SCENE_H
