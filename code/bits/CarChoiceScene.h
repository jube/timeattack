#ifndef TA_CAR_CHOICE_SCENE_H
#define TA_CAR_CHOICE_SCENE_H

#include <gf/ResourceManager.h>
#include <gf/Scene.h>

#include "BackEntity.h"
#include "CarChoiceEntity.h"

namespace ta {

  struct TimeAttack;

  class CarChoiceScene : public gf::Scene {
  public:
    CarChoiceScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    TimeAttack& m_game;

    gf::Action m_escapeAction;

    CarChoiceEntity m_choice;
    BackEntity m_back;
  };

}

#endif // TA_CAR_CHOICE_SCENE_H
