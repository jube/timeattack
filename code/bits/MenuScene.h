#ifndef TA_MENU_SCENE_H
#define TA_MENU_SCENE_H

#include <gf/ResourceManager.h>
#include <gf/Scene.h>

#include "MenuEntity.h"
#include "TrafficEntity.h"

namespace ta {

  struct TimeAttack;

  class MenuScene : public gf::Scene {
  public:
    MenuScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    TimeAttack& m_game;

    gf::Action m_escapeAction;

    TrafficEntity m_traffic;
    MenuChoice m_choice;
    MenuEntity m_menu;
  };

}

#endif // TA_MENU_SCENE_H
