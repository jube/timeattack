#include "CheckeredEntity.h"

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Sprite.h>

namespace ta {

  CheckeredEntity::CheckeredEntity(gf::ResourceManager& resources)
  : m_checkered(resources.getTexture("checkered.png"))
  {
    m_checkered.setSmooth();
  }

  void CheckeredEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    gf::Vector2f position = coords.getCenter();

    float height = coords.getRelativeSize({ 0.0f, 0.512f }).height;
    float scale = height / m_checkered.getSize().height;

    gf::Sprite checkered(m_checkered);
    checkered.setColor(gf::Color::Opaque(0.25f));
    checkered.setPosition(position);
    checkered.setScale(scale);
    checkered.setAnchor(gf::Anchor::Center);
    target.draw(checkered, states);
  }

}
