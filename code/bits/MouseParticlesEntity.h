#ifndef TA_MOUSE_PARTICLES_ENTITY_H
#define TA_MOUSE_PARTICLES_ENTITY_H

#include <vector>

#include <gf/Entity.h>
#include <gf/Random.h>
#include <gf/Time.h>
#include <gf/Vector.h>

namespace ta {

  class MouseParticlesEntity : public gf::Entity {
  public:
    MouseParticlesEntity(gf::Random& random);

    void reset();
    void setActive(bool active);
    void setCursorPosition(gf::Vector2f position);

    void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Random& m_random;
    gf::Vector2f m_position;
    gf::Time m_next;
    bool m_active;

    struct Particle {
      gf::Vector2f position;
      gf::Vector2f velocity;
      gf::Time lifetime;
    };

    std::vector<Particle> m_particles;
  };

}


#endif // TA_MOUSE_PARTICLES_ENTITY_H
