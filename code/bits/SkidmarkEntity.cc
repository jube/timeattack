#include "SkidmarkEntity.h"

#include <gf/Sprite.h>
#include <gf/SpriteBatch.h>
#include <gf/RenderTarget.h>

#include "TimeAttackState.h"

namespace ta {

  namespace {

    constexpr std::size_t MarkCount = 25;
    constexpr gf::Time SkidmarkGenerationTime = gf::milliseconds(100);
    constexpr float SkidmarkDistance = 10.0f;

  }

  SkidmarkEntity::SkidmarkEntity(gf::ResourceManager& resources, TimeAttackState& state)
  : gf::Entity(1)
  , m_texture(resources.getTexture("skidmark.png"))
  , m_state(state)
  {
  }

  void SkidmarkEntity::reset() {
    m_marks.clear();
  }

  void SkidmarkEntity::update(gf::Time time) {
    assert(m_state.car.body != nullptr);

    m_timer += time;

    if (m_timer > SkidmarkGenerationTime) {
      gf::Vector2f position = m_state.physics.computePhysicsToGameCoordinates(m_state.car.body->GetPosition());

      if (gf::squareDistance(position, m_last) > SkidmarkDistance) {
        m_last = position;

        Mark mark;
        mark.position = m_last;
        mark.angle = m_state.car.body->GetAngle() + gf::Pi2;
        m_marks.push_back(mark);
      }

      m_timer -= SkidmarkGenerationTime;
    }

    while (m_marks.size() > MarkCount) {
      m_marks.pop_front();
    }
  }

  void SkidmarkEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::SpriteBatch batch(target);

    for (auto& mark : m_marks) {
      gf::Sprite sprite(m_texture);
      sprite.setPosition(mark.position);
      sprite.setRotation(mark.angle);
      sprite.setAnchor(gf::Anchor::Center);
      batch.draw(sprite, states);
    }

    batch.end();
  }

}
