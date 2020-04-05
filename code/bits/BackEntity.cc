#include "BackEntity.h"

#include <utility>

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

namespace ta {

  BackEntity::BackEntity(gf::ResourceManager& resources)
  : m_font(resources.getFont("TovariSans.otf"))
  , m_backWidget("Back", m_font)
  , m_pressed(false)
  {
    m_backWidget.setCallback([this]() { m_pressed = true; });
    m_container.addWidget(m_backWidget);
  }

  void BackEntity::pointTo(gf::Vector2f coords) {
    m_container.pointTo(coords);
  }

  void BackEntity::triggerAction() {
    m_container.triggerAction();
  }

  bool BackEntity::hasPressedBack() {
    return std::exchange(m_pressed, false);
  }

  void BackEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned characterSize = coords.getRelativeCharacterSize(0.1f);
    auto position = coords.getRelativePoint({ 0.5f, 0.9f });

    m_backWidget.setCharacterSize(characterSize);
    m_backWidget.setAnchor(gf::Anchor::Center);
    m_backWidget.setPosition(position);
    m_backWidget.setDefaultTextColor(gf::Color::White);
    m_backWidget.setDefaultTextOutlineColor(gf::Color::Black);
    m_backWidget.setSelectedTextColor(gf::Color::Red);
    m_backWidget.setSelectedTextOutlineColor(gf::Color::Black);
    m_backWidget.setTextOutlineThickness(characterSize * 0.05f);
    target.draw(m_backWidget, states);
  }


}


