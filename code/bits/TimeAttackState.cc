#include "TimeAttackState.h"

#include "StageLimit.h"
#include "TimeAttackData.h"

#include <gf/Log.h>

namespace ta {

  PhysicsListener::PhysicsListener()
  : m_collision(false)
  {
  }

  void PhysicsListener::reset() {
    m_collision = false;
  }

  bool PhysicsListener::hadCollision() {
    return m_collision;
  }

  void PhysicsListener::BeginContact(b2Contact* contact) {
    gf::Log::debug("Contact!\n");
    m_collision = true;
  }

  void TimeAttackState::loadPhysics(const TimeAttackData& data) {
    assert(currentRace < data.races.size());
    assert(currentStage < data.races[currentRace].stages.size());

    physics.clear();
    car.body = nullptr;

    listener.reset();
    physics.world.SetContactListener(&listener);

    auto& stage = data.races[currentRace].stages[currentStage];

    {
      auto body = physics.createSimpleBody({ 0.0f, 0.0f }, 0.0f, gfb2d::BodyType::Static);
      physics.createPolylineFixture(body, stage.line);
    }

    {
      auto body = physics.createSimpleBody(getInitialPosition(stage.start), getInitialAngle(stage.start));
      body->SetLinearDamping(0.9f);
      physics.createRectangleFixture(body, gf::vec(120.f, 40.0f));
      car.body = body;
    }

    car.velocity = 0.0f;
    car.angle = getInitialAngle(stage.start);
  }

}
