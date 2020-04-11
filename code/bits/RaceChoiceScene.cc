#include "RaceChoiceScene.h"

#include <gf/Log.h>
#include <gf/Unused.h>

#include "Settings.h"
#include "TimeAttack.h"

namespace ta {

  RaceChoiceScene::RaceChoiceScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_escapeAction("Escape")
  , m_choice(game.resources, game.data)
  , m_back(game.resources)
  {
    setClearColor(gf::Color::White);

    m_escapeAction.addKeycodeKeyControl(gf::Keycode::Escape);
    addAction(m_escapeAction);

    addHudEntity(m_choice);
    addHudEntity(m_back);
  }

  void RaceChoiceScene::doProcessEvent(gf::Event& event) {
    switch (event.type) {
      case gf::EventType::MouseMoved:
        m_back.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        m_choice.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        break;

      case gf::EventType::MouseButtonPressed:
        m_back.pointTo(m_game.computeWindowToGameCoordinates(event.mouseButton.coords, getHudView()));
        m_back.triggerAction();
        m_choice.pointTo(m_game.computeWindowToGameCoordinates(event.mouseCursor.coords, getHudView()));
        m_choice.triggerAction();
        break;

      default:
        break;
    }
  }

  void RaceChoiceScene::doHandleActions(gf::Window& window) {
    if (m_escapeAction.isActive()) {
      m_game.replaceScene(m_game.carChoice, m_game.fade, gf::milliseconds(200));
    }
  }

  void RaceChoiceScene::doUpdate(gf::Time time) {
    gf::unused(time);

    if (m_back.hasPressedBack()) {
      m_game.replaceScene(m_game.carChoice, m_game.fade, gf::milliseconds(200));
    }

    std::size_t choice = m_choice.retrieveChosenRace();

    if (choice != std::size_t(-1)) {
      m_game.setupRace(choice);
      m_game.startRace();
    }
  }

}
