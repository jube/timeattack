#include "MouseParticlesEntity.h"

#include <gf/Color.h>
#include <gf/Particles.h>
#include <gf/RenderTarget.h>

namespace ta {

  namespace {

    constexpr gf::Time GenerationTime = gf::microseconds(200);

  }

  MouseParticlesEntity::MouseParticlesEntity(gf::Random& random)
  : gf::Entity(10)
  , m_random(random)
  , m_next(gf::Time::zero())
  , m_active(false)
  {
  }

  void MouseParticlesEntity::reset() {
    m_particles.clear();
  }

  void MouseParticlesEntity::setActive(bool active) {
    m_active = active;
  }

  void MouseParticlesEntity::setCursorPosition(gf::Vector2f position) {
    m_position = position;
  }

  void MouseParticlesEntity::update(gf::Time time) {
    float dt = time.asSeconds();

    // remove old particles

    m_particles.erase(std::remove_if(m_particles.begin(), m_particles.end(), [](auto& particle) { return particle.lifetime < gf::Time::zero(); }), m_particles.end());

    // update particles

    for (auto& particle : m_particles) {
      particle.lifetime -= time;
      particle.position += dt * particle.velocity;
    }

    if (!m_active) {
      return;
    }

    // add new particles

    m_next += time;

    while (m_next > gf::Time::zero()) {
      m_next -= GenerationTime;

      Particle particle;
      particle.position = m_random.computePosition(gf::CircF(m_position, 10.0f));
      particle.velocity = gf::unit(m_random.computeAngle()) * m_random.computeUniformFloat(10.0f, 100.0f);
      particle.lifetime = gf::milliseconds(500);

      m_particles.push_back(particle);
    }
  }

  void MouseParticlesEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::PointParticles particles;

    for (auto& particle : m_particles) {
      particles.addPoint(particle.position, gf::Color::White);
    }

    target.draw(particles, states);
  }

}
