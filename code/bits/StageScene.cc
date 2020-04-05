#include "StageScene.h"

#include "Settings.h"
#include "TimeAttack.h"

#include <gf/Log.h>

namespace ta {

  StageScene::StageScene(TimeAttack& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , m_debugAction("Debug")
  , m_carEntity(game.atlas, game.state)
  , m_carModel(game.state)
  , m_debug(game.state.physics)
  {
    setClearColor(gf::Color::fromRgba32(0x27, 0xAE, 0x60));

    m_debugAction.addKeycodeKeyControl(gf::Keycode::F11);
    addAction(m_debugAction);

    setWorldViewSize(ViewSize);
    setWorldViewCenter(ViewSize / 2);

    addModel(m_carModel);
    addModel(m_game.state.physics);

    addWorldEntity(m_carEntity);
    addWorldEntity(m_debug);

    m_debug.setDebug(false);
  }

  void StageScene::doProcessEvent(gf::Event& event) {
    m_tracker.processEvent(event);
  }

  void StageScene::doHandleActions(gf::Window& window) {
    if (m_debugAction.isActive()) {
      m_debug.toggleDebug();
    }

    if (m_tracker.isActive()) {
      gf::Vector2f cursorPosition = m_game.computeWindowToGameCoordinates(m_tracker.getLastPosition(), getWorldView());
      m_carModel.createAttractionFrom(cursorPosition);
    } else {
      m_carModel.disableAttraction();
    }
  }

  void StageScene::doUpdate(gf::Time time) {
    if (m_game.state.listener.hadCollision()) {
      m_game.state.loadPhysics(m_game.data);
      m_tracker.reset();
    }

    gf::Vector2f position = m_game.state.physics.computePhysicsToGameCoordinates(m_game.state.car.body->GetPosition());
    gf::Vector2f target = getTarget(m_game.data.races[m_game.state.currentRace].stages[m_game.state.currentStage].finish);

    if (gf::squareDistance(position, target) < gf::square(TargetDistance)) {
      gf::Log::debug("Target!\n");
      m_tracker.reset();
      m_game.replaceAllScenes(m_game.finish);
    }
  }


}
