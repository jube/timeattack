#include "CarEntity.h"

#include <gf/Sprite.h>
#include <gf/RenderTarget.h>

#include "TimeAttackState.h"

namespace ta {

  CarEntity::CarEntity(const gf::TextureAtlas& atlas, TimeAttackState& state)
  : m_atlas(atlas)
  , m_state(state)
  {
  }

  void CarEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    assert(m_state.car.texture != nullptr);
    assert(m_state.car.body != nullptr);

    gf::Sprite sprite(m_atlas.getTexture(), m_atlas.getTextureRect(m_state.car.texture));
    sprite.setPosition(m_state.physics.computePhysicsToGameCoordinates(m_state.car.body->GetPosition()));
    sprite.setRotation(m_state.car.body->GetAngle() + gf::Pi2);
    sprite.setAnchor(gf::Anchor::Center);
    target.draw(sprite, states);
  }

}
