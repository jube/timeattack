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
    auto& race = data.races[currentRace];

    assert(currentStage < race.stages.size());
    auto& stage = race.stages[currentStage];

    physics.clear();
    car.body = nullptr;

    listener.reset();
    physics.world.SetContactListener(&listener);

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

    car.angle = getInitialAngle(stage.start);
    car.velocity = 0.0f;

    switch (race.ground) {
      case RaceGround::Sand:
        car.acceleration = 200.0f;
        car.maxVelocity = 600.0f;
        car.brakingFactor = 6.0f;
        break;
      case RaceGround::Dirt:
        car.acceleration = 300.0f;
        car.maxVelocity = 800.0f;
        car.brakingFactor = 6.0f;
        break;
      case RaceGround::Asphalt:
        car.acceleration = 500.0f;
        car.maxVelocity = 1200.0f;
        car.brakingFactor = 8.0f;
        break;
    }
  }

}
