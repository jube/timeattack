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

      float velocityAcceleration = m_state.car.velocity + m_state.car.acceleration * time.asSeconds();

      if (velocityAcceleration > m_state.car.maxVelocity) {
        velocityAcceleration = m_state.car.maxVelocity;
      }

      float velocityBreak = std::sqrt(2.0f * length * (m_state.car.brakingFactor * m_state.car.acceleration));

      m_state.car.velocity = std::min(velocityAcceleration, velocityBreak);
    } else {
      m_state.car.velocity -= m_state.car.brakingFactor * m_state.car.acceleration * time.asSeconds();

      if (m_state.car.velocity < 0) {
        m_state.car.velocity = 0;
      }
    }

    m_state.physics.setBodyAngleAndVelocity(m_state.car.body, m_state.car.angle, m_state.car.velocity);
  }

}

