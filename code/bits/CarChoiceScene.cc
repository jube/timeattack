#include "CarChoiceScene.h"

#include <gf/Log.h>
#include <gf/Unused.h>

#include "Settings.h"
#include "TimeAttack.h"

namespace ta {

  CarChoiceScene::CarChoiceScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_escapeAction("Escape")
  , m_choice(game.resources, game.atlas)
  , m_back(game.resources)
  {
    setClearColor(gf::Color::White);

    m_escapeAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_escapeAction);

    addHudEntity(m_choice);
    addHudEntity(m_back);
  }

  void CarChoiceScene::doProcessEvent(gf::Event& event) {
    switch (event.type) {
      case gf::EventType::MouseMoved:
        m_back.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        m_choice.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        break;

      case gf::EventType::MouseButtonPressed:
        m_back.pointTo(m_game.computeWindowToGameCoordinates(event.mouseButton.coords, getHudView()));
        m_back.triggerAction();
        m_choice.pointTo(m_game.computeWindowToGameCoordinates(event.mouseButton.coords, getHudView()));
        m_choice.triggerAction();
        break;

      default:
        break;
    }
  }

  void CarChoiceScene::doHandleActions(gf::Window& window) {
    if (m_escapeAction.isActive()) {
      m_game.replaceScene(m_game.menu, m_game.fade, gf::milliseconds(200));
    }
  }

  void CarChoiceScene::doUpdate(gf::Time time) {
    gf::unused(time);

    if (m_back.hasPressedBack()) {
      m_game.replaceScene(m_game.menu, m_game.fade, gf::milliseconds(200));
    }

    const char *choice = m_choice.retriveChosenCar();

    if (choice != nullptr) {
      m_game.state.car.texture = choice;
//       m_game.replaceScene(m_game.raceChoice);

      m_game.state.currentRace = 0; // TODO
      m_game.state.currentStage = 0;
      m_game.startRace();
    }
  }

}