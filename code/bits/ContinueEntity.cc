#include "ContinueEntity.h"

#include <utility>

#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

namespace ta {

  ContinueEntity::ContinueEntity(gf::ResourceManager& resources)
  : m_font(resources.getFont("TovariSans.otf"))
  , m_continueWidget("Continue", m_font)
  , m_pressed(false)
  {
    m_continueWidget.setCallback([this]() { m_pressed = true; });
    m_container.addWidget(m_continueWidget);
  }

  void ContinueEntity::pointTo(gf::Vector2f coords) {
    m_container.pointTo(coords);
  }

  void ContinueEntity::triggerAction() {
    m_container.triggerAction();
  }

  bool ContinueEntity::hasPressedContinue() {
    return std::exchange(m_pressed, false);
  }

  void ContinueEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned characterSize = coords.getRelativeCharacterSize(0.1f);
    auto position = coords.getRelativePoint({ 0.5f, 0.9f });

    m_continueWidget.setCharacterSize(characterSize);
    m_continueWidget.setAnchor(gf::Anchor::Center);
    m_continueWidget.setPosition(position);
    m_continueWidget.setDefaultTextColor(gf::Color::White);
    m_continueWidget.setDefaultTextOutlineColor(gf::Color::Black);
    m_continueWidget.setSelectedTextColor(gf::Color::Green);
    m_continueWidget.setSelectedTextOutlineColor(gf::Color::Black);
    m_continueWidget.setTextOutlineThickness(characterSize * 0.05f);
    target.draw(m_continueWidget, states);
  }


}


