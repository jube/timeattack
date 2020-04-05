#ifndef TA_TIME_ATTACK_STATE_H
#define TA_TIME_ATTACK_STATE_H

#include <cstddef>

#include <gfb2d/PhysicsModel.h>

#include "Settings.h"

namespace ta {
  struct TimeAttackData;

  class PhysicsListener : public b2ContactListener {
  public:
    PhysicsListener();

    void reset();
    bool hadCollision();

    void BeginContact(b2Contact* contact) override;
  private:
    bool m_collision;
  };

  struct CarState {
    const char *texture = nullptr;
    b2Body *body = nullptr;
    float angle;
    float velocity;
  };

  struct TimeAttackState {
    TimeAttackState()
    : currentRace(0)
    , currentStage(0)
    , physics(PhysicsScale, { 0.0f, 0.0f })
    {
    }

    void loadPhysics(const TimeAttackData& data);

    std::size_t currentRace;
    std::size_t currentStage;
    gfb2d::PhysicsModel physics;
    PhysicsListener listener;
    CarState car;
  };

}

#endif // TA_TIME_ATTACK_STATE_H
