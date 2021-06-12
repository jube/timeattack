#ifndef TA_SKIDMARK_ENTITY_H
#define TA_SKIDMARK_ENTITY_H

#include <deque>

#include <gf/Entity.h>
#include <gf/ResourceManager.h>

namespace ta {

  struct TimeAttackState;

  class SkidmarkEntity : public gf::Entity {
  public:
    SkidmarkEntity(gf::ResourceManager& resources, TimeAttackState& state);

    void reset();

    void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    const gf::Texture& m_texture;
    TimeAttackState& m_state;
    gf::Time m_timer;
    gf::Vector2f m_last;

    struct Mark {
      gf::Vector2f position;
      float angle;
    };

    std::deque<Mark> m_marks;
  };

}

#endif // TA_SKIDMARK_ENTITY_H
