#ifndef TA_RACE_CHOICE_SCENE_H
#define TA_RACE_CHOICE_SCENE_H

#include <gf/ResourceManager.h>
#include <gf/Scene.h>

#include "BackEntity.h"
#include "CarChoiceEntity.h"

namespace ta {

  struct TimeAttack;

  class RaceChoiceScene : public gf::Scene {
  public:
    RaceChoiceScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    TimeAttack& m_game;

    gf::Action m_escapeAction;

    BackEntity m_back;
  };

}

#endif // TA_RACE_CHOICE_SCENE_H
