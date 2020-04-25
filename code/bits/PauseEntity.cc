#include "PauseEntity.h"

#include <gf/Color.h>
#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

namespace ta {

  PauseEntity::PauseEntity(gf::ResourceManager& resources)
  : m_font(resources.getFont("TovariSans.otf"))
  {
  }

  void PauseEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned characterSize = coords.getRelativeCharacterSize(0.12f);
    auto position = coords.getRelativePoint({ 0.5f, 0.5f });

    gf::Text pause("Pause", m_font, characterSize);
    pause.setColor(gf::Color::Yellow);
    pause.setOutlineColor(gf::Color::Black);
    pause.setOutlineThickness(characterSize * 0.05f);
    pause.setPosition(position);
    pause.setAnchor(gf::Anchor::Center);
    target.draw(pause, states);
  }


}
