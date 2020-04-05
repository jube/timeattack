#include "CarModel.h"

#include "TimeAttackState.h"

#include <gf/Log.h>

namespace ta {

  CarModel::CarModel(TimeAttackState& state)
  : m_state(state)
  , m_attract(false)
  {
  }

  void CarModel::createAttractionFrom(gf::Vector2f position) {
    m_attractionOrigin = position;
    m_attract = true;
  }

  void CarModel::disableAttraction() {
    m_attract = false;
  }

  void CarModel::update(gf::Time time) {
    static constexpr float Acceleration = 300.0f;
    static constexpr float MaxVelocity = 800.0f;
    static constexpr float BrakingFactor = 6.0f;
    static constexpr float StopDistance = 5.0f;

    if (m_attract) {
      gf::Vector2f position = m_state.physics.computePhysicsToGameCoordinates(m_state.car.body->GetPosition());
      gf::Vector2f force = m_attractionOrigin - position;

      float length = gf::euclideanLength(force);

      if (length > StopDistance) {
        m_state.car.angle = gf::angle(force);
      } else {
        length = 0;
      }

      float velocityAcceleration = m_state.car.velocity + Acceleration * time.asSeconds();

      if (velocityAcceleration > MaxVelocity) {
        velocityAcceleration = MaxVelocity;
      }

      float velocityBreak = std::sqrt(2.0f * length * (BrakingFactor * Acceleration));

      m_state.car.velocity = std::min(velocityAcceleration, velocityBreak);
    } else {
      m_state.car.velocity -= BrakingFactor * Acceleration * time.asSeconds();

      if (m_state.car.velocity < 0) {
        m_state.car.velocity = 0;
      }
    }

    m_state.physics.setBodyAngleAndVelocity(m_state.car.body, m_state.car.angle, m_state.car.velocity);
  }

}

