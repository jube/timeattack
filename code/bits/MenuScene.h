#ifndef TA_MENU_SCENE_H
#define TA_MENU_SCENE_H

#include <gf/ResourceManager.h>
#include <gf/Scene.h>

#include "IntroScene.h"
#include "MenuEntity.h"
#include "TrafficEntity.h"

namespace ta {

  struct TimeAttack;

  class MenuScene : public IntroScene {
  public:
    MenuScene(TimeAttack& game);

  private:
    void doProcessEvent(gf::Event& event) override;
    void doHandleActions(gf::Window& window) override;
    void doUpdate(gf::Time time) override;

  private:
    TrafficEntity m_traffic;
    MenuChoice m_choice;
    MenuEntity m_menu;
  };

}

#endif // TA_MENU_SCENE_H
