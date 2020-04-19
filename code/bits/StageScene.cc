#include "StageScene.h"

#include <gf/Easings.h>

#include "Settings.h"
#include "TimeAttack.h"

#include <gf/Log.h>

namespace ta {

  StageScene::StageScene(TimeAttack& game)
  : RaceScene(game)
  , m_debugAction("Debug")
  , m_carEntity(game.atlas, game.state)
  , m_carModel(game.state)
  , m_timer(game.resources, game.state.timer)
  , m_progress(game.resources, game.atlas, game.data, game.state)
  , m_debug(game.state.physics)
  {
    m_debugAction.addKeycodeKeyControl(gf::Keycode::F11);
    addAction(m_debugAction);

    addModel(m_carModel);
    addModel(m_game.state.physics);
    addModel(game.state.timer);

    addWorldEntity(m_carEntity);
    addWorldEntity(m_debug);

    addHudEntity(m_timer);
    addHudEntity(m_progress);

    m_debug.setDebug(false);
  }

  void StageScene::doProcessEvent(gf::Event& event) {
    m_tracker.processEvent(event);
  }

  void StageScene::doHandleActions(gf::Window& window) {
    handleActionsCommon(window);

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
    if (!isActive()) {
      return;
    }

    if (m_game.state.listener.hadCollision()) {
      m_game.state.loadPhysics(m_game.data);
      m_tracker.reset();
    }

    gf::Vector2f position = m_game.state.physics.computePhysicsToGameCoordinates(m_game.state.car.body->GetPosition());
    gf::Vector2f target = getTarget(m_game.data.races[m_game.state.currentRace].stages[m_game.state.currentStage].finish);

    if (gf::squareDistance(position, target) < gf::square(TargetDistance)) {
      gf::Log::debug("Target!\n");
      m_game.state.timer.pause();
      m_tracker.reset();
      m_game.replaceAllScenes(m_game.finish);
    }

    if (m_game.state.timer.isFinished()) {
      gf::Log::debug("Out of time!\n");
      m_game.replaceScene(m_game.result, m_game.checkerboard, gf::seconds(2), gf::Ease::smoother);
    }

  }


}
