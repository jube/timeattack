#ifndef TA_CREDIT_SCENE_H
#define TA_CREDIT_SCENE_H

#include <gf/Scene.h>

#include "BackEntity.h"
#include "CreditEntity.h"
#include "IntroScene.h"

namespace ta {

  struct TimeAttack;

  class CreditScene : public IntroScene {
  public:
    CreditScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    CreditEntity m_credit;
    BackEntity m_back;
  };

}

#endif // TA_CREDIT_SCENE_H
